#include "logger.h"
#include <QDateTime>
#include <QTextStream>

Logger* Logger::instance = nullptr;

Logger::Logger(QObject *parent) : QObject{parent} {
    instance = this;
}

void Logger::setDatabaseManager(DatabaseManager *db, int sessionId) {
    m_db = db;
    m_sessionId = sessionId;
}

void Logger::log(const QString &message) {
    // Просто испускаем сигнал. Qt сам перекинет его в нужный поток.
    emit newLogMessage(message);
}

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
    if (!Logger::instance) return;

    QString typeStr;
    switch (type) {
    case QtDebugMsg:    typeStr = "[DEBUG]"; break;
    case QtInfoMsg:     typeStr = "[INFO] "; break;
    case QtWarningMsg:  typeStr = "[WARN] "; break;
    case QtCriticalMsg: typeStr = "[CRIT] "; break;
    case QtFatalMsg:    typeStr = "[FATAL]"; break;
    }

    // Форматируем строку: время | тип | сообщение
    QString timestamp = QDateTime::currentDateTime().toString("hh:mm:ss");
    QString finalMsg = QString("%1 %2 %3").arg(timestamp, typeStr, msg);

    // Передаем отформатированное сообщение в экземпляр логгера
    Logger::instance->log(finalMsg);
}