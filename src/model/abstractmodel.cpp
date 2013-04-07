#include "abstractmodel.h"

AbstractModel::AbstractModel(QObject *parent) :
    QObject(parent)
{
    m_observerable = new Observable(this);
}
//------------------------------------------------------------------------------
Observable *AbstractModel::getObserverable()
{
    return this->m_observerable;
}
//------------------------------------------------------------------------------
