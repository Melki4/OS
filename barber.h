#ifndef BARBER_H
#define BARBER_H

#include <QObject>

class Barber : public QObject
{
    Q_OBJECT
public:
    explicit Barber(QObject *parent = nullptr);

signals:
};

#endif // BARBER_H
