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
    connect(ui->pBGetListModules, SIGNAL(clicked()), SLOT(getListModulesForDownloads()));
    connect(ui->pBDonwloadModule, SIGNAL(clicked()), SLOT(downloadSelectedModules()));
    connect(ui->comBLanguage, SIGNAL(activated(QString)), SLOT(refreshListForDownload()));
    connect(ui->comBTypeModule, SIGNAL(activated(QString)), SLOT(refreshListForDownload()));
    connect(ui->pBHideModules, SIGNAL(clicked()), SLOT(hideSelectedModules()));
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
void ManagerModules::hideSelectedModules()
{

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
    }
    ui->tableViewStateModules->setModel(modelBiblies);
    ui->tableViewStateModules->resizeColumnsToContents();
    emit SIGNAL_RefreshModules();
}
//------------------------------------------------------------------------------
void ManagerModules::loadListModules()
{
    ProjectQModuleList* list = Config::configuration()->getListBibles();
    modelBiblies->clear();

    if (list->getSize() != 0)
    {
        for (int i = 0; i < list->getSize(); i++)
            m_listModule->addModule(list->getModule(i));

        m_countBiblies = list->getSize();

        list = Config::configuration()->getListDictionaries();
        for (int i = 0; i < list->getSize(); i++)
            m_listModule->addModule(list->getModule(i));

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
        }
        ui->tableViewStateModules->setModel(modelBiblies);
        ui->tableViewStateModules->resizeColumnsToContents();
    }
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
