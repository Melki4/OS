#include "listenerworker.h"

ListenerWorker::ListenerWorker(QObject *parent) : QObject(parent) {}

void ListenerWorker::startListening(quint16 port) {
    if (!m_server) {
        m_server = new QTcpServer(this);
        connect(m_server, &QTcpServer::newConnection, this, &ListenerWorker::onNewConnection);
    }

    if (!m_server->listen(QHostAddress::Any, port)) {
        emit listenerError(m_server->errorString());
        return;
    }
    emit started();
}

void ListenerWorker::stopListening() {
    if (m_server && m_server->isListening()) {
        m_server->close();
    }
}

void ListenerWorker::onNewConnection() {
    while (m_server->hasPendingConnections()) {
        QTcpSocket *socket = m_server->nextPendingConnection();
        const qintptr descriptor = socket->socketDescriptor();
        socket->deleteLater();
        emit clientAccepted(descriptor);
    }
}
