#ifndef MANAGERMODULES_H
#define MANAGERMODULES_H

#include <QDialog>
#include <QStandardItemModel>

#include "projectqmodulelist.h"

namespace Ui {
class ManagerModules;
}

class ManagerModules : public QDialog
{
    Q_OBJECT

public:
    explicit ManagerModules(QWidget *parent = 0);
    ~ManagerModules();



    void loadListModules();
private slots:
    /**
     * @brief downloadSelectedModules
     * In ui->tableview dowload modules select modules
     * and this function dowload.
     */
    void downloadSelectedModules();

    /**
     * @brief refreshListForDownload
     */
    void refreshListForDownload();

    /**
     * @brief getListModulesForDownloads
     * Get list modules from server
     */
    void getListModulesForDownloads();

    /**
     * @brief hideSelectedModules
     */
    void hideSelectedModules();

    /**
     * @brief deleteSelectedModules
     */
    void deleteSelectedModules();

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

    /**
     * @brief deleteModule
     * @param moduleName
     */
    void deleteModule(QString moduleName);

    QStandardItemModel *modelBiblies;
    QStandardItemModel *modelDictionaries;
    ProjectQModuleList* m_listModule;
    int m_countBiblies;

};

#endif // MANAGERMODULES_H
