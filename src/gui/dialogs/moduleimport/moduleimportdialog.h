#ifndef MODULEIMPORTDIALOG_H
#define MODULEIMPORTDIALOG_H

#include <QDialog>

namespace Ui {
class ModuleImportDialog;
}

class ModuleImportDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ModuleImportDialog(QWidget *parent = 0);
    ~ModuleImportDialog();
    
private:
    Ui::ModuleImportDialog *ui;
};

#endif // MODULEIMPORTDIALOG_H
