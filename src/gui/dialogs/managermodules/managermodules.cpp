#include "managermodules.h"
#include "ui_managermodules.h"

#include "config.h"
#include "qsopherimmodulelist.h"
#include "debughelper.h"
#include "filecommon.h"
#include "strongcommon.h"
#include "stringcommon.h"

#include <QStandardItemModel>
#include <QFileDialog>

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
    m_listModule = new QSopherimModuleList;
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

    // strongs settings
    connect(ui->pBBrowseStrong, SIGNAL(clicked()), SLOT(sBrowseStrong()));
    connect(ui->pBAddGreekStrong, SIGNAL(clicked()), SLOT(sAddStrongToGreek()));
    connect(ui->pBAddHebrewStrong, SIGNAL(clicked()), SLOT(sAddStrongToHebrew()));
    connect(ui->comBHebrewStrong, SIGNAL(activated(QString)), SLOT(sSetHebrewStrong(QString)));
    connect(ui->comBGreekStrong, SIGNAL(activated(QString)), SLOT(sSetGreekStrong(QString)));
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
        //todo
        if (Config::configuration()->getListHiddenModules()->contains(selectedList.at(i).data(0).toString()))
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
    QSopherimModuleList* list = Config::configuration()->getListBibles();
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
void ManagerModules::sBrowseStrong()
{
    QFileDialog::Options options;
    QString selectedFilter;
    QString fileName = QFileDialog::getOpenFileName(this
                                                    , tr("Select strong (.htm)")
                                                    , ""
                                                    , tr("All Files (*);;Html Files (*.htm)")
                                                    , &selectedFilter
                                                    , options);
    if (!fileName.isEmpty())
        ui->LEStrongPath->setText(fileName);
}
//------------------------------------------------------------------------------
void ManagerModules::sAddStrongToGreek()
{
    QString t_str = ui->LEStrongPath->text();

    if (ui->comBGreekStrong->findText(ui->LEStrongName->text()) >= 0)
    {
//        myDebug() << "yes1";
        // input other name
    }
    else
    {
        // надо в файл записывать все соответствия имя стронга = путь к нему
        createListStrongs(t_str, ui->LEStrongName->text());
        ui->ListWGreek->addItem(ui->LEStrongName->text());
        ui->comBGreekStrong->addItem(ui->LEStrongName->text());


        addStrongToConfFile(ui->LEStrongName->text(), "greek");

        if (ui->comBGreekStrong->count() == 1)
        {
            emit SIGNAL_SetGreekStrong(t_str);
        }
    }
}
//------------------------------------------------------------------------------
void ManagerModules::sAddStrongToHebrew()
{
    QString t_str = ui->LEStrongPath->text();

    if (ui->comBHebrewStrong->findText(ui->LEStrongName->text()) >= 0)
    {
        // input other name
    }
    else
    {
        //    QString t_name = QStringList(QStringList(t_str.split("/")).last().split(".")).first();
        createListStrongs(t_str, ui->LEStrongName->text());
        ui->ListWHebrew->addItem(ui->LEStrongName->text());
        ui->comBHebrewStrong->addItem(ui->LEStrongName->text());

        addStrongToConfFile(ui->LEStrongName->text(), "hebrew");

        if (ui->comBGreekStrong->count() == 1)
        {
            emit SIGNAL_SetHebrewStrong(t_str);
        }
    }
}
//------------------------------------------------------------------------------
void ManagerModules::sSetGreekStrong(QString f_strong)
{
    QString t_str = getFullPathToStrong(f_strong);
    Config::configuration()->setStrongGreek(t_str);
    emit SIGNAL_SetGreekStrong(getFullPathToStrong(f_strong));
}
//------------------------------------------------------------------------------
void ManagerModules::sSetHebrewStrong(QString f_strong)
{
    QString t_str = getFullPathToStrong(f_strong);
    Config::configuration()->setStrongHebrew(t_str);
    emit SIGNAL_SetHebrewStrong(t_str);
    //    fileStrong = "/home/files/Develop/git/QSopherim/QSopherim-build-desktop/build/bin/strongs/strong.xml";
    //    GUI_ModuleViewer->setStrongList(fileStrong);
}
//------------------------------------------------------------------------------
QString ManagerModules::getFullPathToStrong(QString f_strong)
{
    QString r_path;

    QString t_path = Config::configuration()->getAppDir() + "/strongs.xml";
    QStringList t_list = QStringList(getTextFromHtmlFile(t_path).split("\n"));
    for (int i = 0; i < t_list.size(); i++)
    {
        if (t_list.at(i).contains(f_strong))
        {
            QString t_str = t_list.at(i);
            int pos1 = t_str.indexOf("path=\""); // leng = 6
            int pos2 = t_str.indexOf("\"><"); // leng = 3
            r_path = t_str.mid(pos1 + 6, pos2 - pos1 - 6);
        }
    }
    return Config::configuration()->getStrongDir() + r_path;
}
//------------------------------------------------------------------------------
void ManagerModules::addStrongToConfFile(QString f_name, QString f_language)
{
    QString t_path = Config::configuration()->getAppDir() + "strongs.xml";

    QString t_text = getTextFromHtmlFile(t_path);
    QString t_str =
            QString("<strong language=\"%1\" name=\"%2\" path=\"%3\"></strong>")
            .arg(f_language)
            .arg(f_name)
            .arg(f_name + ".xml");

    t_text.remove("</xml>").append(t_str + "\n").append("</xml>");

    QFile file(t_path);
    if (file.exists())
        file.remove();

    createEmpty(t_path, t_text);
}
//------------------------------------------------------------------------------
void ManagerModules::loadStrongList()
{
    m_hebrewList.clear();
    m_greekList.clear();

    QXmlStreamReader xmlReader;
    xmlReader.addData(getTextFromHtmlFile(Config::configuration()->getAppDir()
                                          + "strongs.xml"));
    // get strongs
    while(!xmlReader.atEnd())
    {
        if(xmlReader.isStartElement())
        {
            QStringList sl;
            sl << xmlReader.name().toString();
            QXmlStreamAttributes attrs = xmlReader.attributes();
            if (attrs.value("language").toString() == "hebrew")
            {
                m_hebrewList << attrs.value("name").toString();
            }
            else
            {
                m_greekList << attrs.value("name").toString();
            }
        }
        xmlReader.readNext();
    }
    // clear empty
    m_hebrewList = removeEmptyQStringFromQStringList(&m_hebrewList);
    m_greekList = removeEmptyQStringFromQStringList(&m_greekList);

    // clear
    ui->comBGreekStrong->clear();
    ui->comBHebrewStrong->clear();

    // add to combo
    ui->comBGreekStrong->addItems(m_greekList);
    ui->comBHebrewStrong->addItems(m_hebrewList);

    // add to list widget
    ui->ListWGreek->addItems(m_greekList);
    ui->ListWHebrew->addItems(m_hebrewList);
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
