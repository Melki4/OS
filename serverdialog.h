#ifndef SERVERDIALOG_H
#define SERVERDIALOG_H

#include <QDialog>
#include <QTcpServer>
#include <QQueue>
#include <QTimer>
#include "barberworker.h"

namespace Ui { class Dialog; }

class ServerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ServerDialog(QWidget *parent = nullptr);
    ~ServerDialog();

public slots:
    void appendLog(const QString &msg); // Для логгера

private slots:
    void onNewConnection();
    void assignClients();
    void onBarberFinished(int barberId);
    void onBarberStateChanged(int barberId, const QString &newState);
    void onMoneyEarned(int amount);
    void updateWorkdayProgress();
    void endWorkday();

private:
    Ui::Dialog *ui;
    QTcpServer *m_server;
    QQueue<qintptr> m_clientQueue;
    QList<BarberWorker*> m_barbers;
    QTimer *m_workdayTimer;

    int m_totalClients;
    int m_currentCash;
    int m_workdayPercent;
};

#endif // SERVERDIALOG_H