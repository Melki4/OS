#include <QApplication>
#include "serverdialog.h"
#include "databasemanager.h"
#include "logger.h"

#ifdef Q_OS_WIN
#include <windows.h>
#endif



// Прототип функции (если она не в заголовочном файле)
void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CreateSemaphoreW(NULL, 10, 10, L"Global\\LabSemaphore");
    // 1. Инициализируем БД
    DatabaseManager dbManager;
    if (!dbManager.initDb()) {
        return -1; // Если БД не открылась, выходим
    }
    int currentSessionId = dbManager.startNewSession();

    // 2. Создаем логгер и связываем его с БД
    Logger logger;
    logger.setDatabaseManager(&dbManager, currentSessionId);

    // 3. Устанавливаем наш обработчик логов
    qInstallMessageHandler(myMessageOutput);

    // 4. Создаем главное окно
    ServerDialog w(&dbManager);

    // ВАЖНО: Добавлен &dbManager как третий аргумент (контекст).
    // Это заставит Qt выполнить лямбду строго в главном потоке!
    QObject::connect(&logger, &Logger::newLogMessage, &dbManager, [&dbManager, currentSessionId](const QString &msg){
        dbManager.saveLog(currentSessionId, msg);
    });

    // Соединяем логгер с интерфейсом (тут контекстом выступает &w, это безопасно)
    QObject::connect(&logger, &Logger::newLogMessage, &w, &ServerDialog::appendLog);

    w.show();

    // Теперь любой qDebug() будет попадать в логгер
    qInfo() << "Сервер запущен и готов к работе";

    int result = a.exec();

    // Завершаем сессию перед выходом
    dbManager.endSession(currentSessionId);

    return result;
}