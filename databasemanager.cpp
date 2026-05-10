#include "databasemanager.h"

DatabaseManager::DatabaseManager(QObject *parent)
    : QObject{parent}
{}

DatabaseManager::~DatabaseManager() {
    if (db.isOpen()) db.close();
}

bool DatabaseManager::initDb()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./BarberShop.db");

    if (!db.open()) {
        qWarning() << "Ошибка открытия БД: " << db.lastError().text();
        return false;
    }

    QSqlQuery query;

    // Таблица сессий
    bool sessions = query.exec("CREATE TABLE IF NOT EXISTS Sessions ("
                               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                               "date_start DATETIME, "
                               "date_end DATETIME, "
                               "total_earned INTEGER DEFAULT 0)");

    bool logs = query.exec("CREATE TABLE IF NOT EXISTS Logs ("
                           "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                           "session_id INTEGER, "
                           "timestamp DATETIME, "
                           "log_text TEXT, "
                           "FOREIGN KEY(session_id) REFERENCES Sessions(id))");

    if (sessions && logs) {
        qInfo() << "База данных готова к работе.";
        return true;
    } else {
        qWarning() << "Ошибка создания таблиц:" << query.lastError().text();
        return false;
    }
}

void DatabaseManager::endSession(int sessionId) {
    QSqlQuery query;

    query.prepare("UPDATE Sessions SET date_end = :end WHERE id = :id");
    query.bindValue(":end", QDateTime::currentDateTime());
    query.bindValue(":id", sessionId);
    query.exec();
}

int DatabaseManager::startNewSession() {
    QSqlQuery query;

    query.prepare("INSERT INTO Sessions (date_start, total_earned) VALUES (:start, 0)");
    query.bindValue(":start", QDateTime::currentDateTime());

    if (query.exec()) {
        return query.lastInsertId().toInt();
    }

    return -1;
}

void DatabaseManager::saveLog(int sessionId, const QString &text) {
    QSqlQuery query;

    query.prepare("INSERT INTO Logs (session_id, timestamp, log_text) "
                  "VALUES (:sid, :ts, :txt)");
    query.bindValue(":sid", sessionId);
    query.bindValue(":ts", QDateTime::currentDateTime());
    query.bindValue(":txt", text);

    if (!query.exec()) {
        qWarning() << "Ошибка сохранения лога:" << query.lastError().text();
    }
}

void DatabaseManager::updateSessionEarnings(int sessionId, int addedAmount) {
    QSqlQuery query;

    query.prepare("UPDATE Sessions SET total_earned = total_earned + :amount WHERE id = :id");
    query.bindValue(":amount", addedAmount);
    query.bindValue(":id", sessionId);
    query.exec();
}

QList<SessionInfo> DatabaseManager::getPastSessions() {
    QList<SessionInfo> list;
    QSqlQuery query("SELECT id, date_start, total_earned FROM Sessions ORDER BY id DESC");

    while (query.next()) {
        SessionInfo info;
        info.id = query.value(0).toInt();
        info.date = query.value(1).toDateTime().toString("dd.MM.yyyy HH:mm");
        info.earned = query.value(2).toInt();
        list.append(info);
    }
    return list;
}

int DatabaseManager::getTotalEarnedMoney() {
    QSqlQuery query("SELECT SUM(total_earned) FROM Sessions");
    if (query.next()) {
        return query.value(0).toInt();
    }
    return 0;
}
