#include "barberworker.h"
#include <QDebug>

BarberWorker::BarberWorker(int id, QObject *parent)
    : QThread(parent), m_id(id), m_state(Offline), m_clientsServed(0), m_stop(false)
{
    loadData();
    changeState(Idle);
}

BarberWorker::~BarberWorker() { stop(); wait(); }

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
    m_greetings << "Приветствую! Я парикмахер %1. Присаживайтесь.";
    m_farewells << "С вас %1 рублей." << "До свидания, приходите еще!";
    m_haircuts.append({"Кроп", 1000});
    m_haircuts.append({"Фейд", 1200});
    m_haircuts.append({"Под ноль", 500});
}

void BarberWorker::changeState(State newState)
{
    m_state = newState;
    QString stateStr = (newState == Idle) ? "Ждет клиента" :
                           (newState == Working) ? "Стрижет" :
                           (newState == Resting) ? "Отдыхает" : "Ушел";
    emit stateChanged(m_id, stateStr);
}

void BarberWorker::run()
{
    while (true) {
        qintptr descriptor = -1;
        {
            QMutexLocker locker(&m_mutex);
            if (m_state != Resting) changeState(Idle);
            m_condition.wait(&m_mutex);
            if (m_stop) break;
            descriptor = m_currentSocketDescriptor;
            m_currentSocketDescriptor = -1;
        }

        if (descriptor == -1) continue;
        changeState(Working);
        if (descriptor == -1) continue;

        QTcpSocket socket;
        if (!socket.setSocketDescriptor(descriptor)) {
            continue;
        }

        qInfo() << "Парикмахер" << m_id << "начал обслуживание нового клиента.";
        int clientId = m_clientsServed + 1;
        socket.write((const char*)&clientId, sizeof(int));
        socket.waitForBytesWritten();

        QString bName = (m_id == 1) ? "[Парикмахер]" : "[Брат-мясник]";
        QByteArray bNameUtf8 = bName.toUtf8();
        socket.write(bNameUtf8.data(), bNameUtf8.size());
        socket.waitForBytesWritten();

        QString greetMsg = m_greetings[0].arg(m_id);
        socket.write(greetMsg.toUtf8());
        socket.waitForBytesWritten();

        if (socket.waitForReadyRead(5000)) socket.readAll();

        QString menu = "Выберите стрижку:\
                       1. Кроп (1000)\
                       2. Фейд (1200)\
                       3. Налысо (500)\
                       ";
                       socket.write(menu.toUtf8());
        socket.waitForBytesWritten();

        int choice = 0;
        if (socket.waitForReadyRead(30000)) socket.read((char*)&choice, sizeof(int));
        int price = (choice == 3) ? 500 : (choice == 2 ? 1200 : 1000);

        QStringList flavors = {"Начинаем стрижку...", "Так, получается хорошо...", "Готово! Отличный результат."};
        for (const QString& f : flavors) {
            socket.write(f.toUtf8());
            socket.waitForBytesWritten();
            QThread::sleep(1);
        }

        QString payMsg = m_farewells[0].arg(price);
        socket.write(payMsg.toUtf8());
        socket.waitForBytesWritten();

        int method = 0;
        if (socket.waitForReadyRead(30000)) socket.read((char*)&method, sizeof(int));

        socket.write(m_farewells[2].toUtf8());
        socket.waitForBytesWritten();

        socket.disconnectFromHost();
        if (socket.state() != QAbstractSocket::UnconnectedState) socket.waitForDisconnected();

        emit earnedMoney(price);
        m_clientsServed++;
        if (m_clientsServed % 4 == 0) { changeState(Resting); QThread::sleep(3);}
        emit clientFinished(m_id);
    }
}
