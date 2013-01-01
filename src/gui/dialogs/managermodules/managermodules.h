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
    void loadStrongList();

signals:
    void SIGNAL_RefreshModules();
    void SIGNAL_SetGreekStrong(QString);
    void SIGNAL_SetHebrewStrong(QString);

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
     * @brief hideSelectedModules
     */
    void showSelectedModules();

    /**
     * @brief deleteSelectedModules
     */
    void deleteSelectedModules();

    /**
     * @brief browseStrong
     */
    void sBrowseStrong();

    void sAddStrongToHebrew();
    void sAddStrongToGreek();

    void sSetHebrewStrong(QString f_strong);
    void sSetGreekStrong(QString f_strong);



private:
    Ui::ManagerModules *ui;

    QStandardItemModel *modelBiblies;
    QStandardItemModel *modelDictionaries;
    ProjectQModuleList* m_listModule;

    QStringList m_hebrewList;
    QStringList m_greekList;

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

    int m_countBiblies;

    /**
     * @brief updateList
     * update hide/show/delete list
     */
    void updateList();



    QString getFullPathToStrong(QString f_strong);
    void addStrongToConfFile(QString f_name, QString f_language);

};

#endif // MANAGERMODULES_H
