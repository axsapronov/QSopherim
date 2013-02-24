#include "moduleimportdialog.h"
#include "ui_moduleimportdialog.h"

ModuleImportDialog::ModuleImportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModuleImportDialog)
{
    ui->setupUi(this);
}
//------------------------------------------------------------------------------
ModuleImportDialog::~ModuleImportDialog()
{
    delete ui;
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

