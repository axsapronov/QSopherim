#include "bottompanel.h"
#include "ui_bottompanel.h"

BottomPanel::BottomPanel(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::BottomPanel)
{
    ui->setupUi(this);
}
//------------------------------------------------------------------------------
BottomPanel::~BottomPanel()
{
    delete ui;
}
//------------------------------------------------------------------------------
void BottomPanel::retranslate()
{
    ui->retranslateUi(this);
}
//------------------------------------------------------------------------------
