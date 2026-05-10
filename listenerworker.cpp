#include "listenerworker.h"

ListenerWorker::ListenerWorker(QObject *parent) : QObject(parent) {}

void ListenerWorker::startListening(quint16 port) {
    if (!m_server) {
        m_server = new DescriptorServer(this);
        connect(m_server, &DescriptorServer::descriptorAccepted, this, &ListenerWorker::clientAccepted);
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
