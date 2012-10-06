#include "leftpanel.h"
#include "ui_leftpanel.h"
#include "debughelper.h"
#include "projectqmodulelist.h"

#include <QStandardItemModel>


LeftPanel::LeftPanel(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::LeftPanel)
{
    ui->setupUi(this);
    init();
}
//------------------------------------------------------------------------------
LeftPanel::~LeftPanel()
{
    delete ui;
}
//------------------------------------------------------------------------------
void LeftPanel::refreshBookList(ProjectQModuleList* list)
{
    moduleList = list;
    myDebug() << "refresh";
    //    myDebug() << list->getSize();
    /*
     *Принимает лист модулей
     *После чего создает элементы в вью
     *Если рассматривать по алфавиту, то парсит первый модуль первую главу
     *чтобы отобразить
     *Наверное, лучше сделать отдельный виджет для показывания
     *Связать его с левой панелью и работать.
     */

    this->modelModules = new QStandardItemModel(moduleList->getSize(), 1, this);
    //* Rows and 1 Columns

    for (int i = 0; i < moduleList->getSize(); i++)
    {
        modelModules->setItem(i, 0, new QStandardItem(
                                  QString(moduleList->getModule(i).getModuleName())));
//    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Column1 Header")));
//    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Column2 Header")));
//    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Column3 Header")));
    }

    ui->tableBook->setModel(modelModules);
    ui->tableBook->resizeColumnsToContents();

//    // Demonstrating look and feel features


//    ui->tableBook->setAnimated(false);
//    ui->tableBook->setIndentation(20);
//    ui->tableBook->setSortingEnabled(true);


}
//------------------------------------------------------------------------------
void LeftPanel::refreshChapterList(QModelIndex moind)
{
//    myDebug() << moind.data(0).toString();
    int chapterValue = moduleList->getModuleWithName(moind.data(0).toString()).getChapterValue();
//    myDebug() << chapterValue;
}
//------------------------------------------------------------------------------
void LeftPanel::init()
{
    createConnects();
    modelModules = new QStandardItemModel(0, 0, this);
    modelChapters = new QStandardItemModel(0, 0, this);
    moduleList = new ProjectQModuleList();
}
//------------------------------------------------------------------------------
void LeftPanel::createConnects()
{

    connect(ui->tableBook, SIGNAL(clicked(QModelIndex)), SLOT(refreshChapterList(QModelIndex)));
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
