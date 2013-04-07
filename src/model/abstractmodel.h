#ifndef ABSTRACTMODEL_H
#define ABSTRACTMODEL_H

#include <QObject>
#include "src/observable/observable.h"

class AbstractModel : public QObject
{
    Q_OBJECT
public:
    explicit AbstractModel(QObject *parent = 0);
    Observable* getObserverable();

    float getF()
    {
        return _temperatureF;
    }
    float getC()
    {
        return (_temperatureF - 32.0) * 5.0 / 9.0;
    }
    void setF(float tempF)
    {
        _temperatureF = tempF;
        m_observerable->notifyUpdate();
    }
    void setC(float tempC)
    {
        _temperatureF = tempC * 9.0 / 5.0 + 32.0;
        m_observerable->notifyUpdate();
    }



signals:

public slots:

private:
    Observable* m_observerable;
    float _temperatureF;

};

#endif // ABSTRACTMODEL_H
