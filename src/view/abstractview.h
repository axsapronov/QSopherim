#ifndef ABSTRACTVIEW_H
#define ABSTRACTVIEW_H

#include <QObject>
#include "src/observer/observer.h"
#include "src/model/abstractmodel.h"

class AbstractView : public Observer
{
    Q_OBJECT
public:

    AbstractView(AbstractModel *model);
    virtual void update();

private:
    AbstractModel *m_model;
};

#endif // ABSTRACTVIEW_H
