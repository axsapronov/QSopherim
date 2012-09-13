#include "leftpanel2.h"
#include "ui_leftpanel2.h"

LeftPanel2::LeftPanel2(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::LeftPanel2)
{
    ui->setupUi(this);
}

LeftPanel2::~LeftPanel2()
{
    delete ui;
}
