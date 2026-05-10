#ifndef LISTENERWORKER_H
#define LISTENERWORKER_H

#include <QObject>
#include <QTcpServer>

class DescriptorServer : public QTcpServer {
    Q_OBJECT
public:
    using QTcpServer::QTcpServer;
signals:
    void descriptorAccepted(qintptr descriptor);
protected:
    void incomingConnection(qintptr socketDescriptor) override {
        emit descriptorAccepted(socketDescriptor);
    }
};

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

private:
    DescriptorServer *m_server = nullptr;
};

#endif
