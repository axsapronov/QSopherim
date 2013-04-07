#include "observable.h"
#include "src/debug/debughelper.h"


Observable::Observable(QObject *parent) :
    QObject(parent)
{

}
//------------------------------------------------------------------------------
void Observable::addObserver(Observer *observer)
{
    m_observers.push_back(observer);
}
//------------------------------------------------------------------------------
void Observable::notifyUpdate()
{
    for (int i = 0; i < m_observers.size(); i++)
    {
        m_observers[i]->update();
    }
}
//------------------------------------------------------------------------------
