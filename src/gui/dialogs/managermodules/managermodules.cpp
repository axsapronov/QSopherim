#include "managermodules.h"
#include "ui_managermodules.h"

#include "config.h"
#include "projectqmodulelist.h"
#include "debughelper.h"

#include <QStandardItemModel>

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
    delete m_listModule;
    delete modelBiblies;
    delete modelDictionaries;

    delete ui;
}
//------------------------------------------------------------------------------
void ManagerModules::init()
{
    m_listModule = new ProjectQModuleList;
    modelBiblies = new QStandardItemModel(0, 1, this);
    modelDictionaries = new QStandardItemModel(0, 0, this);
    createConnects();
}
//------------------------------------------------------------------------------
void ManagerModules::createConnects()
{
    // download manager
    connect(ui->pBGetListModules, SIGNAL(clicked()), SLOT(getListModulesForDownloads()));
    connect(ui->pBDonwloadModule, SIGNAL(clicked()), SLOT(downloadSelectedModules()));
    connect(ui->comBLanguage, SIGNAL(activated(QString)), SLOT(refreshListForDownload()));
    connect(ui->comBTypeModule, SIGNAL(activated(QString)), SLOT(refreshListForDownload()));

    // settings module
    connect(ui->pBHideModules, SIGNAL(clicked()), SLOT(hideSelectedModules()));
    connect(ui->pBShowModules, SIGNAL(clicked()), SLOT(showSelectedModules()));
    connect(ui->pBDeleteModules, SIGNAL(clicked()), SLOT(deleteSelectedModules()));
}
//------------------------------------------------------------------------------
void ManagerModules::downloadSelectedModules()
{

}
//------------------------------------------------------------------------------
void ManagerModules::refreshListForDownload()
{

}
//------------------------------------------------------------------------------
void ManagerModules::getListModulesForDownloads()
{

}
//------------------------------------------------------------------------------
void ManagerModules::showSelectedModules()
{
    QModelIndexList selectedList = ui->tableViewStateModules->selectionModel()->selectedRows();
    for( int i = 0; i<selectedList.count(); i++)
    {
        m_listModule->showModule(selectedList.at(i).data(0).toString());
    }
    updateList();
}
//------------------------------------------------------------------------------
void ManagerModules::hideSelectedModules()
{
    QModelIndexList selectedList = ui->tableViewStateModules->selectionModel()->selectedRows();
    for( int i = 0; i<selectedList.count(); i++)
    {
        m_listModule->hideModule(selectedList.at(i).data(0).toString());
    }
    updateList();
}
//------------------------------------------------------------------------------
void ManagerModules::deleteSelectedModules()
{
    QModelIndexList selectedList = ui->tableViewStateModules->selectionModel()->selectedRows();
    for( int i = 0; i<selectedList.count(); i++)
    {
        m_listModule->deleteModule(selectedList.at(i).data(0).toString());
        QString t_str = ui->tableViewStateModules->model()->data
                (
                    ui->tableViewStateModules->model()->index
                    (
                        selectedList.at(i).row(), 1
                        ), Qt::DisplayRole
                    ).toString();

        if (t_str == "bible")
        {
            m_countBiblies--;
        }
    }
    updateList();
}
//------------------------------------------------------------------------------
void ManagerModules::loadListModules()
{
    ProjectQModuleList* list = Config::configuration()->getListBibles();
    modelBiblies->clear();
    //    myDebug() << "yes";
    m_listModule->clearList();


    if (list->getSize() != 0)
    {
        // fill modules
        for (int i = 0; i < list->getSize(); i++)
            m_listModule->addModule(list->getModule(i));

        m_countBiblies = list->getSize();

        // fill dict
        list = Config::configuration()->getListDictionaries();
        for (int i = 0; i < list->getSize(); i++)
            m_listModule->addModule(list->getModule(i));

        updateList();
//        ui->tableViewStateModules->setModel(modelBiblies);
//        ui->tableViewStateModules->resizeColumnsToContents();
    }
}
//------------------------------------------------------------------------------
void ManagerModules::updateList()
{

    modelBiblies->clear();
    for(int i = 0; i < m_listModule->getSize(); i++)
    {
        modelBiblies->setItem(i, 0, new QStandardItem(m_listModule->getModule(i)->getModuleName()));
        if (i < m_countBiblies)
        {
            modelBiblies->setItem(i, 1, new QStandardItem("bible"));
        }
        else
        {
            modelBiblies->setItem(i, 1, new QStandardItem("dictionaries"));
        }
        // set hide show
        if (!Config::configuration()->getListHiddenModules()->contains(m_listModule->getModule(i)->getModuleName()))
        {
            modelBiblies->setItem(i, 2, new QStandardItem("show"));
        }
        else
        {
            modelBiblies->setItem(i, 2, new QStandardItem("hidden"));
        }
    }
    ui->tableViewStateModules->setModel(modelBiblies);
    ui->tableViewStateModules->resizeColumnsToContents();
    emit SIGNAL_RefreshModules();
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
