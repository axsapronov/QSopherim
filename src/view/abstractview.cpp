#include "abstractview.h"
#include "src/debug/debughelper.h"

//------------------------------------------------------------------------------
AbstractView::AbstractView(AbstractModel *model)
{
    m_model = model;
    m_model->getObserverable()->addObserver(this);
}
//------------------------------------------------------------------------------
void AbstractView::update()
{
    myDebug() << "Temperature in Celsius: " <<  m_model->getC();
    myDebug() << "Temperature in Farenheit: " <<  m_model->getF();
    myDebug() << "Input temperature in Celsius: ";
}
//------------------------------------------------------------------------------
