#include "abstractcontroller.h"

AbstractController::AbstractController(QObject *parent) :
    QObject(parent)
{

}
//------------------------------------------------------------------------------
AbstractController::AbstractController(AbstractModel *model)
{
    m_model = model;
}
//------------------------------------------------------------------------------
