#include "managermodules.h"
#include "ui_managermodules.h"

#include "config.h"
#include "projectqmodulelist.h"

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

}
//------------------------------------------------------------------------------
void ManagerModules::loadListModules()
{
    ProjectQModuleList* list = Config::configuration()->getListBibles();
    modelBiblies->clear();
    for (int i = 0; i < list->getSize(); i++)
    {
        modelBiblies->setItem(i, 0, new QStandardItem(list->getModule(i)->getModuleName()));
        modelBiblies->setItem(i, 1, new QStandardItem("bible"));
    }

    int t_count = list->getSize();
    list = Config::configuration()->getListDictionaries();

    for (int i = 0; i < list->getSize(); i++)
    {
        modelBiblies->setItem(i + t_count, 0, new QStandardItem(list->getModule(i)->getModuleName()));
        modelBiblies->setItem(i + t_count, 1, new QStandardItem("dictionaries"));
    }

    ui->tableViewStateModules->setModel(modelBiblies);
    ui->tableViewStateModules->resizeColumnsToContents();
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
