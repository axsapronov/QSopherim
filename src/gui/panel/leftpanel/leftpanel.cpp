#include "leftpanel.h"
#include "ui_leftpanel.h"
#include "debughelper.h"
#include "qsopherimmodulelist.h"
#include "moduleviewer.h"
#include "filecommon.h"

#include "config.h"


#include <QStandardItemModel>
#include <QStringListModel>

#define GUI_TAB_BIBLE 0
#define GUI_TAB_BOOK 1
#define GUI_TAB_DICT 2



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

    delete typeModelBook;
    delete typeModel;

    delete ui;
}
//------------------------------------------------------------------------------
void LeftPanel::refreshListModule(QSopherimModuleList* list)
{
    Config::configuration()->setListBibles(list);
    //    this->modelModules = new QStandardItemModel(moduleList->getSize(), 1, this);
    //* Rows and 1 Columns
    modelBooks->clear();
    modelChapters->clear();
    moduleList = list;
    QStringList items_bible;
    QStringList items_book;
    for (int i = 0; i < list->getSize(); i++)
    {
        if (!Config::configuration()->getListHiddenModules()->contains(list->getModule(i)->getModuleName()))
        {
            if (list->getModule(i)->getModuleType() == "Bible")
                items_bible << QString(list->getModule(i)->getModuleName());

            if (list->getModule(i)->getModuleType() == "Book")
                items_book << QString(list->getModule(i)->getModuleName());
        }
    }

    if (!items_book.isEmpty())
    {
        typeModelBook = new QStringListModel(items_book, this);
        ui->comBModulesBook->setModel(typeModelBook);
        refreshBookList(ui->comBModulesBook->currentText(), "Book");
    }

    if (!items_bible.isEmpty())
    {
        typeModel = new QStringListModel(items_bible, this);
        ui->comBModules->setModel(typeModel);
        refreshBookList(ui->comBModules->currentText(), "Bible");
    }

}
//------------------------------------------------------------------------------
void LeftPanel::refreshListDict(QSopherimModuleList* list)
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
    refreshWordListFromDict(ui->comBDictList->currentText());
    //    refreshBookList(ui->comBModules->currentText());
}
//------------------------------------------------------------------------------
void LeftPanel::refreshBookList(QSopherimModuleList* list)
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
    QTableView *t_table = (QTableView*)sender();

    modelChapters->clear();
    int chapterValue = 0;

    if (t_table == ui->tableBook)
        chapterValue = moduleList->getModuleWithName(ui->comBModules->currentText())
                ->getValueChapterForBookFromModule(moind.data(0).toString());

    if (t_table == ui->tableBookBook)
        chapterValue = moduleList->getModuleWithName(ui->comBModulesBook->currentText())
                ->getValueChapterForBookFromModule(moind.data(0).toString());

    modelChapters->clear();
    for (int i = 0; i < chapterValue; i++)
    {
        modelChapters->setItem(i, 0, new QStandardItem(QString::number(i + 1)));
        //        myDebug() << "yes";
    }


    if (t_table == ui->tableBook)
    {
        ui->tableChapter->setModel(modelChapters);
        ui->tableChapter->resizeColumnsToContents();
    }

    if (t_table == ui->tableBookBook)
    {
        ui->tableChapterBook->setModel(modelChapters);
        ui->tableChapterBook->resizeColumnsToContents();
    }

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
    moduleList = new QSopherimModuleList();
    typeModelBook = new QStringListModel();
    typeModel = new QStringListModel();
    m_lastNameOfBook  = "";
    ui->tableBook->reset();
    ui->tableChapter->reset();
}
//------------------------------------------------------------------------------
void LeftPanel::createConnects()
{
    // bible or book
    connect(ui->comBModules, SIGNAL(activated(QString)), SLOT(refreshBookList(QString)));
    connect(ui->comBModulesBook, SIGNAL(activated(QString)), SLOT(refreshBookList(QString)));

    connect(ui->tableBook, SIGNAL(clicked(QModelIndex)), SLOT(refreshChapterList(QModelIndex)));
    connect(ui->tableBookBook, SIGNAL(clicked(QModelIndex)), SLOT(refreshChapterList(QModelIndex)));

    connect(ui->tableChapter, SIGNAL(clicked(QModelIndex)), SLOT(showChapter(QModelIndex)));
    connect(ui->tableChapterBook, SIGNAL(clicked(QModelIndex)), SLOT(showChapter(QModelIndex)));

    // dict
    connect(ui->comBDictList, SIGNAL(activated(QString)), SLOT(refreshWordListFromDict(QString)));
    connect(ui->comBWordList, SIGNAL(activated(QString)), SLOT(showDescriptionWord(QString)));
    connect(ui->ListViewWordList, SIGNAL(clicked(QModelIndex)), SLOT(showWord(QModelIndex)));

    connect(ui->comBDictListFindWord, SIGNAL(activated(QString)), SLOT(showDescriptionWordFromOtherModules(QString)));

    connect(ui->tabWidget, SIGNAL(currentChanged(int)), SLOT(sShowHideLeftPanel2(int)));
}
//------------------------------------------------------------------------------
void LeftPanel::showChapter(QModelIndex ind)
{
    // так как выделение с книги может спадать, то надо запоминать последнюю книгу

    QTableView *t_table = (QTableView*)sender();

    QString t_nameOfBook;
    QModelIndexList selectedList;
    QString t_pathToModule;
    QString t_curModule;

    // bible
    if (t_table == ui->tableChapter)
    {
        selectedList = ui->tableBook->selectionModel()->selectedRows();
        t_curModule = ui->comBModules->currentText();
    }

    // book
    if (t_table == ui->tableChapterBook)
    {
        selectedList = ui->tableBookBook->selectionModel()->selectedRows();
        t_curModule = ui->comBModulesBook->currentText();
    }

    for( int i = 0; i < selectedList.count(); i++)
    {
        t_nameOfBook = selectedList.at(i).data(0).toString();
    }
    m_lastNameOfBook = t_nameOfBook;

    t_pathToModule = Config::configuration()->getAppDir() +
            moduleList->getModuleWithName(t_curModule)->getModulePath();
    t_pathToModule.replace("module.ini", "text.xml");

    ModuleViewer::viewer()->setModuleName(t_curModule);
    ModuleViewer::viewer()->showChapter(t_pathToModule, m_lastNameOfBook ,
                                        ind.row() + 1);


    emit SIGNAL_AddRecordToJournal(t_curModule,
                                   m_lastNameOfBook ,
                                   QString::number(ind.row() + 1));

}
//------------------------------------------------------------------------------
void LeftPanel::refreshBookList(QString nameOfModule, QString f_type)
{
    modelBooks->clear();
    modelChapters->clear();

    QStringList bookList = moduleList->getModuleBooks(nameOfModule);
    for (int i = 0; i < bookList.size() - 1; i++)
    {
        modelBooks->setItem(i, 0, new QStandardItem(bookList.at(i)));
    }

    if (f_type == "Bible")
    {
        ui->tableBook->setModel(modelBooks);
        ui->tableBook->resizeColumnsToContents();
    }

    if (f_type == "Book")
    {
        ui->tableBookBook->setModel(modelBooks);
        ui->tableBookBook->resizeColumnsToContents();
    }
}
//------------------------------------------------------------------------------
void LeftPanel::refreshBookList(QString nameOfModule)
{
    QComboBox *combo = (QComboBox*)sender();

    if (combo == ui->comBModules)
        refreshBookList(nameOfModule, "Bible");

    if (combo == ui->comBModulesBook)
        refreshBookList(nameOfModule, "Book");
}
//------------------------------------------------------------------------------
void LeftPanel::refreshComboBooks()
{
    refreshBookList(ui->comBModulesBook->currentText(), "Book");
    refreshBookList(ui->comBModules->currentText(), "Bible");
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


    // refresh tab for bible modules or book modules
    refreshBookList(module, moduleList->getModuleWithName(module)->getModuleType());

    if (moduleList->getModuleWithName(module)->getModuleType() == "Bible")
    {
        ui->comBModules->setCurrentIndex(ui->comBModules->findText(module));
        ui->tabWidget->setCurrentIndex(GUI_TAB_BIBLE); // bible
        //todo добавить автоматический выбор открытой главы и книги
    }

    if (moduleList->getModuleWithName(module)->getModuleType() == "Book")
    {
        ui->comBModulesBook->setCurrentIndex(ui->comBModulesBook->findText(module));
        ui->tabWidget->setCurrentIndex(GUI_TAB_BOOK); // book
    }




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
void LeftPanel::sShowHideLeftPanel2(int f_tab)
{
    // not copy many of tab 1, tab 2, tab N
    if (f_tab != GUI_TAB_DICT) // dict
        // show if select module
        emit SIGNAL_ShowHideLeftPanel2(false);

    switch (f_tab)
    {
    case GUI_TAB_BIBLE: refreshBookList(ui->comBModules->currentText(), "Bible"); break;
    case GUI_TAB_BOOK: refreshBookList(ui->comBModulesBook->currentText(), "Book"); break;
    case GUI_TAB_DICT : emit SIGNAL_ShowHideLeftPanel2(true); // hide if select dict
    }

}
//------------------------------------------------------------------------------

