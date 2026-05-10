#ifndef SERVERDIALOG_H
#define SERVERDIALOG_H

#include <QDialog>
#include <QQueue>
#include <QTimer>
#include <QThread>
#include "barberworker.h"
#include "databasemanager.h"
#include "listenerworker.h"

namespace Ui { class Dialog; }

class ServerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ServerDialog(DatabaseManager *dbManager, QWidget *parent = nullptr);
    ~ServerDialog();

public slots:
    void appendLog(const QString &msg);

private slots:
    void onClientAccepted(qintptr descriptor);
    void assignClients();
    void onBarberFinished(int barberId);
    void onBarberStateChanged(int barberId, const QString &newState);
    void onMoneyEarned(int amount);
    void updateWorkdayProgress();
    void endWorkday();
    void loadSessionLogs();

private:
    void fillSessionsCombo();

    Ui::Dialog *ui;
    DatabaseManager *m_dbManager;
    QQueue<qintptr> m_clientQueue;
    QList<BarberWorker*> m_barbers;
    QTimer *m_workdayTimer;

    QThread *m_listenerThread;
    ListenerWorker *m_listenerWorker;

    int m_currentCash;
    int m_workdayPercent;
};

#endif
