#ifndef OBSERVER_H
#define OBSERVER_H

#include <QObject>

class Observer : public QObject
{
    Q_OBJECT
public:
    explicit Observer(QObject *parent = 0);
    virtual void update() = 0;

signals:

public slots:

};

#endif // OBSERVER_H
