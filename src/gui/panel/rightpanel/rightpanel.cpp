#include "rightpanel.h"
#include "ui_rightpanel.h"

RightPanel::RightPanel(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::RightPanel)
{
    ui->setupUi(this);
}
//------------------------------------------------------------------------------
RightPanel::~RightPanel()
{
    delete ui;
}
//------------------------------------------------------------------------------
void RightPanel::retranslate()
{
    ui->retranslateUi(this);
}
//------------------------------------------------------------------------------
