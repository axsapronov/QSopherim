#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include <QObject>
#include <QVector>

#include "src/observer/observer.h"

class Observable : public QObject
{
    Q_OBJECT
public:
    explicit Observable(QObject *parent = 0);

    void addObserver(Observer *observer);
    void notifyUpdate();

signals:

public slots:

private:
    QVector<Observer*> m_observers;

};

#endif // OBSERVABLE_H
