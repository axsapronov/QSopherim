#include "fontdialog.h"
#include "ui_fontdialog.h"

#include "defines.h"
#include "debughelper.h"
#include "config.h"

FontDialog::FontDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FontDialog)
{
    ui->setupUi(this);
    setWindowTitle(QString(tr("Font dialog") + " | %1 - %2").arg(GL_PROG_NAME).arg(GL_PROG_VERSION_STR));
}
//------------------------------------------------------------------------------
FontDialog::~FontDialog()
{
    delete ui;
}
//------------------------------------------------------------------------------
void FontDialog::createConnects()
{

}
//------------------------------------------------------------------------------
void FontDialog::accept()
{
    //todo
    myDebug() << "accept";
    QWidget::hide();
}
//------------------------------------------------------------------------------
void FontDialog::reject()
{
    myDebug() << "reject";
    QWidget::hide();
}
//------------------------------------------------------------------------------
void FontDialog::setNameOption(const QString f_name)
{
    m_name = f_name;
}
//------------------------------------------------------------------------------
