#ifndef BARBERWORKER_H
#define BARBERWORKER_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <QMutex>
#include <QWaitCondition>
#include <QStringList>

struct Haircut {
    QString name;
    int price;
};

class BarberWorker : public QThread
{
    Q_OBJECT
public:
    enum State { Idle, Working, Resting, Offline };

    explicit BarberWorker(int id, QObject *parent = nullptr);
    ~BarberWorker();

    void assignClient(qintptr socketDescriptor);
    void stop();
    State getCurrentState() const { return m_state; }

signals:
    void stateChanged(int barberId, QString newState);
    void clientFinished(int barberId);
    void earnedMoney(int amount);

protected:
    void run() override;

private:
    void loadData();
    void changeState(State newState);

    int m_id;
    State m_state;
    qintptr m_currentSocketDescriptor = -1;
    int m_clientsServed;

    QMutex m_mutex;
    QWaitCondition m_condition;
    bool m_stop;

    QStringList m_greetings;
    QStringList m_farewells;
    QList<Haircut> m_haircuts;
};

#endif
