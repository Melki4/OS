#include "barberworker.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

BarberWorker::BarberWorker(int id, QObject *parent)
    : QThread(parent), m_id(id), m_state(Offline), m_stop(false), m_clientsServed(0)
{
    loadData();
    changeState(Idle);
}

BarberWorker::~BarberWorker()
{
    stop();
    wait();
}

void BarberWorker::assignClient(qintptr socketDescriptor)
{
    QMutexLocker locker(&m_mutex);
    m_currentSocketDescriptor = socketDescriptor;
    m_condition.wakeOne();
}

void BarberWorker::stop()
{
    QMutexLocker locker(&m_mutex);
    m_stop = true;
    m_condition.wakeOne();
}

void BarberWorker::loadData()
{
    // В реальном проекте здесь QDir::currentPath() или ресурсы qrc
    m_greetings << "Приветствую! Я парикмахер %1. Присаживайтесь."
                << "Здравствуйте, готовы к стрижке?";
    m_farewells << "С вас %1 рублей."
                << "Вот ваша сдача."
                << "До свидания, приходите еще!";
    m_haircuts.append({"Кроп", 1000});
    m_haircuts.append({"Фейд", 1200});
    m_haircuts.append({"Под ноль", 500});
}

void BarberWorker::changeState(State newState)
{
    m_state = newState;
    QString stateStr;
    switch(newState) {
    case Idle: stateStr = "Ждет клиента"; break;
    case Working: stateStr = "Стрижет"; break;
    case Resting: stateStr = "Отдыхает"; break;
    case Offline: stateStr = "Ушел"; break;
    }
    emit stateChanged(m_id, stateStr);
}

bool BarberWorker::waitForClientResponse(QTcpSocket &socket, QString &response)
{
    if (socket.waitForReadyRead(30000)) { // Ждем ответа 30 сек
        QTextStream in(&socket);
        response = in.readLine();
        return true;
    }
    return false;
}

void BarberWorker::run() {
    while (true) {
        qintptr descriptor;
        {
            QMutexLocker locker(&m_mutex);
            if (m_state != Resting) changeState(Idle);
            m_condition.wait(&m_mutex);
            if (m_stop) break;
            descriptor = m_currentSocketDescriptor;
        }

        changeState(Working);
        QTcpSocket socket;
        if (!socket.setSocketDescriptor(descriptor)) continue;

        qInfo() << "Парикмахер" << m_id << "начал обслуживание нового клиента.";

        // 0. Отправляем ID клиента (client.cpp: recv(Connection, (char*)&clientIndex...))
        int clientId = m_clientsServed + 1;
        socket.write((const char*)&clientId, sizeof(int));
        socket.waitForBytesWritten();

        // 1. Отправляем Имя парикмахера (client.cpp: recv(Connection, name, 256, 0))
        QString bName = (m_id == 1) ? "[Парикмахер]" : "[Брат-мясник]";
        QByteArray bNameUtf8 = bName.toUtf8();
        socket.write(bNameUtf8.data(), bNameUtf8.size());
        socket.waitForBytesWritten();

        // 2. Отправляем приветствие (client.cpp: bytes = recv(Connection, buffer, 1024, 0))
        QString greetMsg = m_greetings[0].arg(m_id);
        socket.write(greetMsg.toUtf8());
        socket.waitForBytesWritten();

        // 3. Ждем приветствие от клиента (client.cpp: send(Connection, utf8Greet.c_str()...))
        if (socket.waitForReadyRead(5000)) {
            socket.readAll(); // Просто читаем и игнорируем
        }

        // 4. Отправляем меню (client.cpp: bytes = recv(Connection, buffer, 1024, 0))
        QString menu = "Выберите стрижку:\n1. Кроп (1000)\n2. Фейд (1200)\n3. Налысо (500)\n";
        socket.write(menu.toUtf8());
        socket.waitForBytesWritten();

        // 5. Ждем выбор (client.cpp: send(Connection, (char*)&choice...))
        int choice = 0;
        if (socket.waitForReadyRead(30000)) {
            socket.read((char*)&choice, sizeof(int));
        }
        int price = (choice == 3) ? 500 : (choice == 2 ? 1200 : 1000);
        qInfo() << "Парикмахер" << m_id << "стрижет. Клиент выбрал вариант:" << choice;

        // 6. Отправляем 3 фразы процесса (client.cpp: for(int i=0; i<3; i++) recv(...))
        QStringList flavors = {"Начинаем стрижку...", "Так, получается хорошо...", "Готово! Отличный результат."};
        for (const QString& f : flavors) {
            socket.write(f.toUtf8());
            socket.waitForBytesWritten();
            QThread::sleep(1); // Имитация работы
        }

        // 7. Отправляем варианты оплаты (client.cpp: recv(Connection, buffer, 1024, 0))
        QString payMsg = m_farewells[0].arg(price);
        socket.write(payMsg.toUtf8());
        socket.waitForBytesWritten();

        // 8. Ждем метод оплаты (client.cpp: send(Connection, (char*)&method...))
        int method = 0;
        if (socket.waitForReadyRead(30000)) {
            socket.read((char*)&method, sizeof(int));
        }

        // 9. Отправляем прощание (client.cpp: recv(Connection, buffer, 1024, 0))
        socket.write(m_farewells[2].toUtf8());
        socket.waitForBytesWritten();

        // Завершение работы с клиентом
        socket.disconnectFromHost();
        if (socket.state() != QAbstractSocket::UnconnectedState) socket.waitForDisconnected();

        emit earnedMoney(price);
        m_clientsServed++;

        // Отдых после 4 клиентов
        if (m_clientsServed % 4 == 0) {
            changeState(Resting);
            qInfo() << "Парикмахер" << m_id << "устал и ушел на перекур.";
            QThread::sleep(3);
        }
        emit clientFinished(m_id);
    }
}