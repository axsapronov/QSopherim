#ifndef MANAGERMODULES_H
#define MANAGERMODULES_H

#include <QDialog>

namespace Ui {
class ManagerModules;
}

class ManagerModules : public QDialog
{
    Q_OBJECT

public:
    explicit ManagerModules(QWidget *parent = 0);
    ~ManagerModules();

private:
    Ui::ManagerModules *ui;

    /**
     \brief
     init function
     */
    void init();

    /**
     \brief
     Create connects function
     */
    void createConnects();
};

#endif // MANAGERMODULES_H
