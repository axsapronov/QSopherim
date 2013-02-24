#include "moduleimportdialog.h"
#include "ui_moduleimportdialog.h"


#include "config.h"
#include "defines.h"
#include "debughelper.h"

#include <QFileDialog>

ModuleImportDialog::ModuleImportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModuleImportDialog)
{
    ui->setupUi(this);
    initGUI();

    connect(ui->pBBrowse, SIGNAL(clicked()), SLOT(sBrowsePath()));
    connect(ui->pBAddModule, SIGNAL(clicked()), SLOT(sConvertModules()));
}
//------------------------------------------------------------------------------
ModuleImportDialog::~ModuleImportDialog()
{
    delete ui;
}
//------------------------------------------------------------------------------
void ModuleImportDialog::initGUI()
{
    setWindowTitle(QString(tr("Import modules") + " | %1 - %2").arg(GL_PROG_NAME).arg(GL_PROG_VERSION_STR));

    QStringList t_format;
    QStringList t_type;

    t_format << tr("BibleQuote");

    t_type << tr("Bible")
           << tr("Book")
           << tr("Dictionary");

    ui->comBFormat->addItems(t_format);
    ui->comBType->addItems(t_type);
}
//------------------------------------------------------------------------------
void ModuleImportDialog::sBrowsePath()
{
    QFileDialog::Options options = QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly;
    QString directory = QFileDialog::getExistingDirectory(this,
                                                          tr("Select dir for modules"),
                                                          Config::configuration()->getAppDir(),
                                                          options);
    if (!directory.isEmpty())
    {
        ui->LEPath->setText(directory);
    }
}
//------------------------------------------------------------------------------
void ModuleImportDialog::sConvertModules()
{
    if (!ui->LEPath->text().isEmpty())
    {
        if (ui->comBFormat->currentText() == tr("BibleQuote"))
        {
            if (ui->comBType->currentText() == tr("Bible")
                    || ui->comBType->currentText() == tr("Book")
                    )
            {
                Config::configuration()->setBibleDir(ui->LEPath->text());
                emit SIGNAL_UpdateModules();
            }

            if (ui->comBType->currentText() == tr("Dictionary"))
            {
                Config::configuration()->setDictDir(ui->LEPath->text());
                emit SIGNAL_UpdateModulesDict();
            }
        }


        //    if (ui->comBFormat->currentText() == tr("BibleQuote"))
        //    {

        //    }
    }
}
//------------------------------------------------------------------------------

