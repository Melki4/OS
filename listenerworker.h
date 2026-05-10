#ifndef LISTENERWORKER_H
#define LISTENERWORKER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class ListenerWorker : public QObject {
    Q_OBJECT
public:
    explicit ListenerWorker(QObject *parent = nullptr);

public slots:
    void startListening(quint16 port);
    void stopListening();

signals:
    void clientAccepted(qintptr descriptor);
    void listenerError(const QString &message);
    void started();

private slots:
    void onNewConnection();

private:
    QTcpServer *m_server = nullptr;
};

#endif