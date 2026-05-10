#include "serverdialog.h"
#include "ui_dialog.h"
#include <QMessageBox>
#include <QTextStream>

ServerDialog::ServerDialog(DatabaseManager *dbManager, QWidget *parent)
    : QDialog(parent), ui(new Ui::Dialog), m_dbManager(dbManager),
      m_listenerThread(new QThread(this)), m_listenerWorker(new ListenerWorker()),
      m_currentCash(0), m_workdayPercent(0)
{
    ui->setupUi(this);
    ui->text_cash_in_hand->setText("0");
    ui->clients_amount->setText("0");
    ui->day_progress->setValue(0);
    ui->pushButton->setText("Загрузить логи");

    connect(ui->pushButton, &QPushButton::clicked, this, &ServerDialog::loadSessionLogs);

    BarberWorker *b1 = new BarberWorker(1, this);
    connect(b1, &BarberWorker::stateChanged, this, &ServerDialog::onBarberStateChanged);
    connect(b1, &BarberWorker::clientFinished, this, &ServerDialog::onBarberFinished);
    connect(b1, &BarberWorker::earnedMoney, this, &ServerDialog::onMoneyEarned);
    m_barbers.append(b1);
    b1->start();

    m_listenerWorker->moveToThread(m_listenerThread);
    connect(m_listenerThread, &QThread::started, m_listenerWorker, [this]() { m_listenerWorker->startListening(1111); });
    connect(m_listenerWorker, &ListenerWorker::clientAccepted, this, &ServerDialog::onClientAccepted);
    connect(m_listenerWorker, &ListenerWorker::listenerError, this, [this](const QString &msg) {
        QMessageBox::critical(this, "Ошибка сервера", msg);
    });
    connect(m_listenerThread, &QThread::finished, m_listenerWorker, &QObject::deleteLater);
    m_listenerThread->start();

    m_workdayTimer = new QTimer(this);
    connect(m_workdayTimer, &QTimer::timeout, this, &ServerDialog::updateWorkdayProgress);
    m_workdayTimer->start(1000);

    fillSessionsCombo();
}

ServerDialog::~ServerDialog() {
    endWorkday();
    for (auto barber : m_barbers) { barber->stop(); barber->wait(); }
    delete ui;
}

void ServerDialog::onClientAccepted(qintptr descriptor) {
    m_clientQueue.enqueue(descriptor);

    if (m_clientQueue.size() > 2 && m_barbers.size() == 1) {
        BarberWorker *b2 = new BarberWorker(2, this);
        connect(b2, &BarberWorker::stateChanged, this, &ServerDialog::onBarberStateChanged);
        connect(b2, &BarberWorker::clientFinished, this, &ServerDialog::onBarberFinished);
        connect(b2, &BarberWorker::earnedMoney, this, &ServerDialog::onMoneyEarned);
        m_barbers.append(b2);
        b2->start();
        qInfo() << "В очереди больше 2 клиентов: подключен второй парикмахер";
    }
    ui->clients_amount->setText(QString::number(m_clientQueue.size()));
    assignClients();
}

void ServerDialog::assignClients() {
    for (auto barber : m_barbers) {
        if (m_clientQueue.isEmpty()) break;
        if (barber->getCurrentState() == BarberWorker::Idle) {
            qintptr descriptor = m_clientQueue.dequeue();
            barber->assignClient(descriptor);
        }
    }
    ui->clients_amount->setText(QString::number(m_clientQueue.size()));
}

void ServerDialog::onBarberFinished(int) { assignClients(); }

void ServerDialog::onBarberStateChanged(int barberId, const QString &newState) {
    if (barberId == 1) ui->text_barber_main->setText(newState);
    else ui->text_barber_brother->setText(newState);
}

void ServerDialog::onMoneyEarned(int amount) {
    m_currentCash += amount;
    ui->cash_in_hand->setText(QString::number(m_currentCash));
}

void ServerDialog::updateWorkdayProgress() {
    m_workdayPercent++;
    ui->day_progress->setValue(m_workdayPercent);
    if (m_workdayPercent >= 100) endWorkday();
}

void ServerDialog::endWorkday() {
    if (m_workdayEnded) return;
    m_workdayEnded = true;
    if (m_workdayTimer && m_workdayTimer->isActive()) m_workdayTimer->stop();

    if (m_listenerWorker) {
        QMetaObject::invokeMethod(m_listenerWorker, "stopListening", Qt::BlockingQueuedConnection);
    }
    if (m_listenerThread && m_listenerThread->isRunning()) {
        m_listenerThread->quit();
        m_listenerThread->wait();
    }

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
}

void ServerDialog::appendLog(const QString &msg) {
    ui->text_output->addItem(msg);
    ui->text_output->scrollToBottom();
}

void ServerDialog::fillSessionsCombo() {
    ui->combo_box_prev_sessions->clear();
    const QList<SessionInfo> sessions = m_dbManager->getPastSessions();
    for (const SessionInfo &s : sessions) {
        ui->combo_box_prev_sessions->addItem(QString("Сессия %1 (%2)").arg(s.id).arg(s.date), s.id);
    }
}

void ServerDialog::loadSessionLogs() {
    ui->text_logs_from_sessions->clear();
    int sessionId = ui->combo_box_prev_sessions->currentData().toInt();
    QSqlQuery q;
    q.prepare("SELECT timestamp, log_text FROM Logs WHERE session_id = :sid ORDER BY id");
    q.bindValue(":sid", sessionId);
    if (!q.exec()) return;

    while (q.next()) {
        ui->text_logs_from_sessions->addItem(
            QString("%1 | %2").arg(q.value(0).toDateTime().toString("hh:mm:ss"), q.value(1).toString()));
    }
}
