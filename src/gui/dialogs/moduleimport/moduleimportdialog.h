#ifndef MODULEIMPORTDIALOG_H
#define MODULEIMPORTDIALOG_H

#include <QDialog>
#include <QStringListModel>

namespace Ui {
class ModuleImportDialog;
}

class ModuleImportDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ModuleImportDialog(QWidget *parent = 0);
    ~ModuleImportDialog();

private slots:
    void sBrowsePath();
    void sConvertModules();

signals:
    void SIGNAL_UpdateModules();
    void SIGNAL_UpdateModulesDict();

private:
    Ui::ModuleImportDialog *ui;

    void initGUI();
};

#endif // MODULEIMPORTDIALOG_H
