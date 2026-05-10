#include "serverdialog.h"
#include "ui_dialog.h"
#include <QDebug>
#include <QMessageBox>

ServerDialog::ServerDialog(QWidget *parent) :

    QDialog(parent),
    ui(new Ui::Dialog), // Используем твой класс дизайна
    m_totalClients(0), m_currentCash(0), m_workdayPercent(0)
{
    ui->setupUi(this);

    // Установка картинок (как в твоем исходном коде)
    ui->barber_main->setPixmap(QPixmap("D:/Загрузки/77f02bcd-b1af-43ec-96dc-9d0dd707629b.png"));
    ui->barber_brother->setPixmap(QPixmap("D:/Загрузки/77f02bcd-b1af-43ec-96dc-9d0dd707629b (1).png"));

    // Инициализация логгера и БД (через main.cpp, тут только GUI)
    ui->text_cash_in_hand->setText("0");
    ui->text_clients_amount->setText("0");
    ui->day_progress->setValue(0);

    // Парикмахер 1
    BarberWorker *b1 = new BarberWorker(1, this);
    connect(b1, &BarberWorker::stateChanged, this, &ServerDialog::onBarberStateChanged);
    connect(b1, &BarberWorker::clientFinished, this, &ServerDialog::onBarberFinished);
    connect(b1, &BarberWorker::earnedMoney, this, &ServerDialog::onMoneyEarned);
    m_barbers.append(b1);
    b1->start();

    m_server = new QTcpServer(this);
    connect(m_server, &QTcpServer::newConnection, this, &ServerDialog::onNewConnection);
    m_server->listen(QHostAddress::Any, 1111);

    m_workdayTimer = new QTimer(this);
    connect(m_workdayTimer, &QTimer::timeout, this, &ServerDialog::updateWorkdayProgress);
    m_workdayTimer->start(1000);
}

ServerDialog::~ServerDialog() {
    for (auto barber : m_barbers) {
        barber->stop();
        barber->wait();
    }
    delete ui;
}

void ServerDialog::onNewConnection() {
    while (m_server->hasPendingConnections()) {
        QTcpSocket *s = m_server->nextPendingConnection();
        // qintptr desc = s->stealDescriptor(); // Если версия Qt позволяет, или:
        // m_clientQueue.enqueue(s->socketDescriptor());
        // s->disconnect(); // Отключаем сигналы, чтобы он не закрылся сам
        // s->setParent(nullptr);

        // Но лучше всего:
        m_clientQueue.enqueue(s->socketDescriptor());
        // Мы НЕ вызываем deleteLater здесь. Мы вызовем его в BarberWorker.
    }
    assignClients();
}

void ServerDialog::assignClients() {
    if (m_clientQueue.isEmpty()) return;

    for (auto barber : m_barbers) {
        if (m_clientQueue.isEmpty()) break;

        if (barber->getCurrentState() == BarberWorker::Idle) {
            qintptr descriptor = m_clientQueue.dequeue();
            barber->assignClient(descriptor);
        }
    }
}

void ServerDialog::onBarberFinished(int barberId) {
    // Парикмахер освободился, проверяем очередь
    assignClients();
}

void ServerDialog::onBarberStateChanged(int barberId, const QString &newState) {
    // Используем правильные имена полей статуса
    if (barberId == 1) ui->text_barber_main->setText(newState);
    else ui->text_barber_brother->setText(newState);
}

void ServerDialog::onMoneyEarned(int amount) {
    m_currentCash += amount;
    ui->text_cash_in_hand->setText(QString::number(m_currentCash));

    // Обновляем в базе через синглтон или указатель, если нужно
    // DatabaseManager::instance()->updateSessionEarnings(currentId, amount);
}

void ServerDialog::updateWorkdayProgress() {
    m_workdayPercent++;
    ui->day_progress->setValue(m_workdayPercent);

    if (m_workdayPercent >= 100) {
        endWorkday();
    }
}

void ServerDialog::endWorkday() {
    m_workdayTimer->stop();
    m_server->close(); // Перестаем принимать новые подключения
    qInfo() << "Рабочий день окончен. Вывешиваем табличку 'Закрыто'.";

    // Сбрасываем ожидающих в очереди
    while (!m_clientQueue.isEmpty()) {
        qintptr desc = m_clientQueue.dequeue();
        QTcpSocket s;
        if (s.setSocketDescriptor(desc)) {
            QTextStream out(&s);
            out.setEncoding(QStringConverter::Utf8);
            out << "Извините, мы закрыты!\n";
            out.flush();
            s.disconnectFromHost();
        }
    }

    QMessageBox::information(this, "Конец смены", "Рабочий день завершен!");
}

void ServerDialog::appendLog(const QString &msg) {
    // Вместо text_output используй имя своего ListWidget или TextEdit
    ui->text_output->addItem(msg);
    ui->text_output->scrollToBottom();
}