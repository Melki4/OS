#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QString>
#include "databasemanager.h"

class Logger : public QObject
{
    Q_OBJECT
public:
    explicit Logger(QObject *parent = nullptr);

    void setDatabaseManager(DatabaseManager *db, int sessionId);
    void log(const QString &message);
    static Logger* instance;

signals:
    void newLogMessage(const QString &msg);

private:
    DatabaseManager *m_db = nullptr;
    int m_sessionId = -1;
};

#endif // LOGGER_H
