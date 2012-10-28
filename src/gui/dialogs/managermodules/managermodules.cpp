#include "managermodules.h"
#include "ui_managermodules.h"

ManagerModules::ManagerModules(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManagerModules)
{
    ui->setupUi(this);
    init();
}
//------------------------------------------------------------------------------
ManagerModules::~ManagerModules()
{
    delete ui;
}
//------------------------------------------------------------------------------
void ManagerModules::init()
{
    createConnects();
}
//------------------------------------------------------------------------------
void ManagerModules::createConnects()
{

}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
