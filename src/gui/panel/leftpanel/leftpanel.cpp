#include "leftpanel.h"
#include "ui_leftpanel.h"
#include "debughelper.h"
#include "projectqmodulelist.h"
#include "moduleviewer.h"
#include "filecommon.h"

#include "config.h"


#include <QStandardItemModel>
#include <QStringListModel>



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
    delete modelBooks;
    delete modelChapters;
    delete modelModules;
    delete modelClear;
    delete moduleList;
    delete typeModel;

    delete ui;
}
//------------------------------------------------------------------------------
void LeftPanel::refreshListModule(ProjectQModuleList* list)
{
    Config::configuration()->setListBibles(list);
    //    this->modelModules = new QStandardItemModel(moduleList->getSize(), 1, this);
    //* Rows and 1 Columns
    modelBooks->clear();
    modelChapters->clear();
    moduleList = list;
    QStringList items;
    for (int i = 0; i < list->getSize(); i++)
    {
        if (!Config::configuration()->getListHiddenModules()->contains(list->getModule(i)->getModuleName()))
        {
            items << QString(list->getModule(i)->getModuleName());
        }
    }
    typeModel = new QStringListModel(items, this);
    ui->comBModules->setModel(typeModel);
    refreshBookList(ui->comBModules->currentText());
}
//------------------------------------------------------------------------------
void LeftPanel::refreshListDict(ProjectQModuleList* list)
{
    Config::configuration()->setListDictionaries(list);
    //    this->modelModules = new QStandardItemModel(moduleList->getSize(), 1, this);
    //* Rows and 1 Columns
    //    modelBooks->clear();
    //    modelChapters->clear();
    //    moduleList = list;
    QStringList items;
    for (int i = 0; i < list->getSize(); i++)
    {
        if (!Config::configuration()->getListHiddenModules()->contains(list->getModule(i)->getModuleName()))
        {
            items << QString(list->getModule(i)->getModuleName());
        }
    }
    typeModel = new QStringListModel(items, this);
    ui->comBDictList->setModel(typeModel);
    //    refreshBookList(ui->comBModules->currentText());
}
//------------------------------------------------------------------------------
void LeftPanel::refreshBookList(ProjectQModuleList* list)
{
    //    moduleList = list;
    Q_UNUSED (list)
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

    //    this->modelBooks = new QStandardItemModel(moduleList->getSize(), 1, this);
    //    //* Rows and 1 Columns

    //    for (int i = 0; i < moduleList->getSize(); i++)
    //    {
    //        modelBooks->setItem(i, 0, new QStandardItem(
    //                                  QString(moduleList->getModule(i)->getModuleName())));
    ////    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Column1 Header")));
    ////    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Column2 Header")));
    ////    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Column3 Header")));
    //    }

    //    ui->tableBook->setModel(modelBooks);
    //    ui->tableBook->resizeColumnsToContents();

    //    // Demonstrating look and feel features


    //    ui->tableBook->setAnimated(false);
    //    ui->tableBook->setIndentation(20);
    //    ui->tableBook->setSortingEnabled(true);


}
//------------------------------------------------------------------------------
void LeftPanel::refreshChapterList(QModelIndex moind)
{
    modelChapters->clear();
    int chapterValue = moduleList->getModuleWithName(ui->comBModules->currentText())
            ->getValueChapterForBookFromModule(moind.data(0).toString());
    modelChapters->clear();
    for (int i = 0; i < chapterValue; i++)
    {
        modelChapters->setItem(i, 0, new QStandardItem(QString::number(i + 1)));
        //        myDebug() << "yes";
    }
    ui->tableChapter->setModel(modelChapters);
    ui->tableChapter->resizeColumnsToContents();
    m_lastNameOfBook  = moind.data(0).toString();
}
//------------------------------------------------------------------------------
void LeftPanel::init()
{
    createConnects();
    modelModules = new QStandardItemModel(0, 0, this);
    modelBooks = new QStandardItemModel(0, 0, this);
    modelChapters = new QStandardItemModel(0, 0, this);
    modelClear = new QStandardItemModel(0, 0, this);
    moduleList = new ProjectQModuleList();
    m_lastNameOfBook  = "";
    ui->tableBook->reset();
    ui->tableChapter->reset();
}
//------------------------------------------------------------------------------
void LeftPanel::createConnects()
{
    connect(ui->comBModules, SIGNAL(activated(QString)), SLOT(refreshBookList(QString)));
    connect(ui->tableBook, SIGNAL(clicked(QModelIndex)), SLOT(refreshChapterList(QModelIndex)));
    connect(ui->tableChapter, SIGNAL(clicked(QModelIndex)), SLOT(showChapter(QModelIndex)));
    connect(ui->comBDictList, SIGNAL(activated(QString)), SLOT(refreshWordListFromDict(QString)));
    connect(ui->comBWordList, SIGNAL(activated(QString)), SLOT(showDescriptionWord(QString)));
    connect(ui->ListViewWordList, SIGNAL(clicked(QModelIndex)), SLOT(showWord(QModelIndex)));

    connect(ui->comBDictListFindWord, SIGNAL(activated(QString)), SLOT(showDescriptionWordFromOtherModules(QString)));
}
//------------------------------------------------------------------------------
void LeftPanel::showChapter(QModelIndex ind)
{
    /// так как выделение с книги может спадать, то надо запоминать последнюю книгу

    QString t_nameOfBook;
    QModelIndexList selectedList = ui->tableBook->selectionModel()->selectedRows();
    for( int i = 0; i < selectedList.count(); i++)
    {
        t_nameOfBook = selectedList.at(i).data(0).toString();
    }

    QString t_pathToModule = Config::configuration()->getAppDir() +
            moduleList->getModuleWithName(ui->comBModules->currentText())->getModulePath();
    t_pathToModule.replace("module.ini", "text.xml");

    ModuleViewer::viewer()->setModuleName(ui->comBModules->currentText());
    ModuleViewer::viewer()->showChapter(t_pathToModule, m_lastNameOfBook ,
                                        ind.row() + 1);
    emit SIGNAL_AddRecordToJournal(ui->comBModules->currentText(),
                                   m_lastNameOfBook ,
                                   QString::number(ind.row() + 1));

}
//------------------------------------------------------------------------------
void LeftPanel::refreshBookList(QString nameOfBook)
{
    modelBooks->clear();
    modelChapters->clear();
    QStringList bookList = moduleList->getModuleBooks(nameOfBook);
    //    myDebug() << moduleList->getModuleWithName(ui->comBModules->currentText());
    //    myDebug() << bookList.size();
    for (int i = 0; i < bookList.size() - 1; i++)
    {
        modelBooks->setItem(i, 0, new QStandardItem(bookList.at(i)));
        //        myDebug() << "yes";
    }

    ui->tableBook->setModel(modelBooks);
    ui->tableBook->resizeColumnsToContents();
}
//------------------------------------------------------------------------------
void LeftPanel::retranslate()
{
    ui->retranslateUi(this);
}
//------------------------------------------------------------------------------
void LeftPanel::showChapterFromJournal(QString module, QString book, QString chapter)
{
    QString t_pathToModule = Config::configuration()->getAppDir() +
            moduleList->getModuleWithName(module)->getModulePath();
    t_pathToModule.replace("module.ini", "text.xml");

    m_lastNameOfBook  = book;

    ui->comBModules->setCurrentIndex(ui->comBModules->findText(module));
    refreshBookList(module);

    ModuleViewer::viewer()->setModuleName(module);
    ModuleViewer::viewer()->showChapter(t_pathToModule, book,
                                        chapter.toInt());
}
//------------------------------------------------------------------------------
void LeftPanel::refreshWordListFromDict(QString curText)
{
    QString t_pathToFile = QString(Config::configuration()->getAppDir() + "dictionary/" +
                                   curText + "/dict.xml");
    QStringList wordList = getListWord(t_pathToFile);

    QStandardItemModel* modelWord = new QStandardItemModel;
    for (int i = 0; i < wordList.size() - 1; i++)
    {
        modelWord->setItem(i, 0, new QStandardItem(wordList.at(i)));
        //        myDebug() << "yes";
    }

    ui->ListViewWordList->setModel(modelWord);

    // find desc from other dict

}
//------------------------------------------------------------------------------
void LeftPanel::showDescriptionWord(QString word)
{
    QString t_pathToFile = QString(Config::configuration()->getAppDir() + "dictionary/" +
                                   ui->comBDictList->currentText() + "/dict.xml");

    QString t_text = getDescriptionForWordFromDict(t_pathToFile, word);
    ui->view->setText(t_text);
}
//------------------------------------------------------------------------------
void LeftPanel::showDescriptionWordFromOtherModules(QString word)
{
    word = m_curWord;
    QString t_pathToFile = QString(Config::configuration()->getAppDir() + "dictionary/" +
                                   ui->comBDictListFindWord->currentText() + "/dict.xml");

    QString t_text = getDescriptionForWordFromDict(t_pathToFile, word);
    ui->view->setText(t_text);
}
//------------------------------------------------------------------------------
void LeftPanel::showWord(QModelIndex ind)
{
    QString word = ind.data(0).toString();
    m_curWord = word;
    showDescriptionWord(word);

    QStringList list = getListDictWithWord(word);

    ui->comBDictListFindWord->clear();
    ui->comBDictListFindWord->addItems(list);
}
//------------------------------------------------------------------------------
void LeftPanel::setListModuleFromList()
{
    Config::configuration()->setListBibles(moduleList);
}
//------------------------------------------------------------------------------
QStringList LeftPanel::getListDictWithWord(QString word)
{
    QStringList r_list;

    QStringList t_list = recursiveFind(Config::configuration()->getAppDir() + "dictionary/");
    for (int var = 0; var < t_list.size(); var++)
    {
        if (t_list.at(var).indexOf("dict.xml") >= 0)
        {
            QString t_text = getDescriptionForWordFromDict(t_list.at(var), word);
            if (!t_text.isEmpty())
            {
                QStringList t_l;
                t_l << QString(t_list.at(var)).split("/");
                r_list << t_l.at(t_l.size() - 2);
            }
        }
    }
    return r_list;
}
//------------------------------------------------------------------------------
