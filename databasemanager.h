#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>
#include <QVariant>

struct SessionInfo
{
    int id;
    QString date;
    int earned;
};

class DatabaseManager : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseManager(QObject *parent = nullptr);
    ~DatabaseManager();

    bool initDb();
    int startNewSession();
    void endSession(int sessionId);
    void updateSessionEarnings(int sessionId, int addedAmount);

    QList<SessionInfo> getPastSessions();
    int getTotalEarnedMoney();
private:
    QSqlDatabase db;
public slots: // Переносим сюда
    void saveLog(int sessionId, const QString &text);
signals:
};

#endif // DATABASEMANAGER_H
