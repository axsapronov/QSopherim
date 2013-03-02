#include "leftpanel.h"
#include "ui_leftpanel.h"
#include "debughelper.h"
#include "qsopherimmodulelist.h"
#include "moduleviewer.h"
#include "filecommon.h"

#include "strongcommon.h" // for book number

#include "config.h"
#include "defines.h"

#include <QStandardItemModel>
#include <QStringListModel>

#define GUI_TAB_BIBLE 0
#define GUI_TAB_BOOK 1
#define GUI_TAB_DICT 2
#define GUI_TAB_COMMENTS 3
#define GUI_TAB_APOCRYPHA 4
#define GUI_TAB_OTHER 5

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

    delete typeModelBook;
    delete typeModel;

    delete ui;
}
//------------------------------------------------------------------------------
void LeftPanel::init()
{
    createConnects();
    modelModules = new QStandardItemModel(0, 0, this);
    modelBooks = new QStandardItemModel(0, 0, this);
    modelChapters = new QStandardItemModel(0, 0, this);
    modelClear = new QStandardItemModel(0, 0, this);
    typeModelBook = new QStringListModel();
    typeModel = new QStringListModel();
    m_lastNameOfBook  = "";
    ui->tableBook->reset();
    ui->tableChapter->reset();
    ui->tableBookApocrypha->reset();
    ui->tableBookBook->reset();
    ui->tableChapterApocrypha->reset();
    ui->tableChapterBook->reset();

    sUpdateGUIDayMode();
    sUpdateGUIFont();

    ui->tabWidget->removeTab(ui->tabWidget->indexOf(ui->tabApocrypha));
    ui->tabWidget->removeTab(ui->tabWidget->indexOf(ui->tabComments));
    ui->tabWidget->removeTab(ui->tabWidget->indexOf(ui->tabBook));
    ui->tabWidget->removeTab(ui->tabWidget->indexOf(ui->tabDictionary));
    ui->tabWidget->removeTab(ui->tabWidget->indexOf(ui->tabOther));
}
//------------------------------------------------------------------------------
void LeftPanel::createConnects()
{
    // bible or book
    connect(ui->comBModules, SIGNAL(activated(QString)), SLOT(refreshBookList(QString)));
    connect(ui->comBModulesBook, SIGNAL(activated(QString)), SLOT(refreshBookList(QString)));
    connect(ui->comBModulesApocrypha, SIGNAL(activated(QString)), SLOT(refreshBookList(QString)));

    // comments
    connect(ui->comBComments, SIGNAL(activated(QString)), SLOT(sSetCommentsFromModule(QString)));

    connect(ui->tableBook, SIGNAL(clicked(QModelIndex)), SLOT(refreshChapterList(QModelIndex)));
    connect(ui->tableBookBook, SIGNAL(clicked(QModelIndex)), SLOT(refreshChapterList(QModelIndex)));
    connect(ui->tableBookApocrypha, SIGNAL(clicked(QModelIndex)), SLOT(refreshChapterList(QModelIndex)));

    connect(ui->tableChapter, SIGNAL(clicked(QModelIndex)), SLOT(showChapter(QModelIndex)));
    connect(ui->tableChapterBook, SIGNAL(clicked(QModelIndex)), SLOT(showChapter(QModelIndex)));
    connect(ui->tableChapterApocrypha, SIGNAL(clicked(QModelIndex)), SLOT(showChapter(QModelIndex)));

    // dict
    connect(ui->comBDictList, SIGNAL(activated(QString)), SLOT(refreshWordListFromDict(QString)));
    connect(ui->comBWordList, SIGNAL(activated(QString)), SLOT(showDescriptionWord(QString)));
    connect(ui->ListViewWordList, SIGNAL(clicked(QModelIndex)), SLOT(showWord(QModelIndex)));

    connect(ui->comBDictListFindWord, SIGNAL(activated(QString)), SLOT(showDescriptionWordFromOtherModules(QString)));

    connect(ui->tabWidget, SIGNAL(currentChanged(int)), SLOT(sShowHideLeftPanel2(int)));
}
//------------------------------------------------------------------------------
void LeftPanel::refreshListModule(QSopherimModuleList* list, const QString f_type)
{
    if (list->getSize() != 0 )
    {
        //* Rows and 1 Columns
        modelBooks->clear();
        modelChapters->clear();
        QStringList items;

        for (int i = 0; i < list->getSize(); i++)
        {
            if (!Config::configuration()->getListHiddenModules()->contains(list->getModule(i)->getModuleName()))
            {
                items << QString(list->getModule(i)->getModuleName());
            }
        }

        if (!items.isEmpty())
        {
            if (f_type == "Book")
            {
                ui->tabWidget->insertTab(GUI_TAB_BOOK, ui->tabBook, tr("Book"));
                typeModelBook = new QStringListModel(items, this);
                ui->comBModulesBook->setModel(typeModelBook);
                if (Config::configuration()->isExistLastChapter() and
                        Config::configuration()->getLastType() == f_type)
                    refreshBookList(ui->comBModulesBook->currentText(), f_type);
            }

            if (f_type == "Bible")
            {
                typeModel = new QStringListModel(items, this);
                ui->comBModules->setModel(typeModel);
                if (Config::configuration()->isExistLastChapter() and
                        Config::configuration()->getLastType() == f_type)
                    refreshBookList(ui->comBModules->currentText(), f_type);
            }

            if (f_type == "Apocrypha")
            {
                ui->tabWidget->insertTab(GUI_TAB_APOCRYPHA, ui->tabApocrypha, tr("Apocrypha"));
                typeModel = new QStringListModel(items, this);
                ui->comBModulesApocrypha->setModel(typeModel);
                if (Config::configuration()->isExistLastChapter() and
                        Config::configuration()->getLastType() == f_type)
                    refreshBookList(ui->comBModulesApocrypha->currentText(), f_type);
            }
        }

    }

    // show hide tabs if modules (of type) is empty
    showHideTabs();
}
//------------------------------------------------------------------------------
void LeftPanel::refreshListDict(QSopherimModuleList* list)
{
    if (list->getSize() != 0 )
    {
        // dict tab
        ui->tabWidget->insertTab(GUI_TAB_DICT, ui->tabDictionary, tr("Dictionary"));
        Config::configuration()->setListDictionaries(list);
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
    }
    else
    {
        // dict tab
        ui->tabWidget->removeTab(ui->tabWidget->indexOf(ui->tabDictionary));
    }
}
//------------------------------------------------------------------------------
void LeftPanel::refreshListComments(QSopherimModuleList* list)
{
    if (list->getSize() != 0 )
    {
        // dict tab
        ui->tabWidget->insertTab(GUI_TAB_COMMENTS, ui->tabComments, tr("Comments"));
        Config::configuration()->setListComments(list);
        QStringList items;
        for (int i = 0; i < list->getSize(); i++)
        {
            if (!Config::configuration()->getListHiddenModules()->contains(list->getModule(i)->getModuleName()))
            {
                items << QString(list->getModule(i)->getModuleName());
            }
        }
        typeModel = new QStringListModel(items, this);
        ui->comBComments->setModel(typeModel);
        sSetCommentsFromModule(ui->comBComments->itemText(0));
    }
    else
    {
        // dict tab
        ui->tabWidget->removeTab(ui->tabWidget->indexOf(ui->tabComments));
    }
}
//------------------------------------------------------------------------------
void LeftPanel::refreshChapterList(const QModelIndex f_ind)
{
    QTableView *t_table = (QTableView*)sender();

    if (t_table == ui->tableBook)
    {
        refreshChapterList("Bible", f_ind);
    }

    if (t_table == ui->tableBookBook)
    {
        refreshChapterList("Book", f_ind);
    }

    if (t_table == ui->tableBookApocrypha)
    {
        refreshChapterList("Apocrypha", f_ind);
    }
}
//------------------------------------------------------------------------------
void LeftPanel::refreshChapterList(const QString f_type, const QModelIndex f_ind)
{
    modelChapters->clear();
    int chapterValue = 0;

    QString t_curModule;

    if (f_type == "Bible")
        t_curModule = ui->comBModules->currentText();

    if (f_type == "Book")
        t_curModule = ui->comBModulesBook->currentText();

    if (f_type == "Apocrypha")
        t_curModule = ui->comBModulesApocrypha->currentText();

    chapterValue = Config::configuration()->getListModulesFromMap(f_type)->getModuleWithName(t_curModule)
            ->getValueChapterForBookFromModule(f_ind.data(0).toString());

    modelChapters->clear();
    for (int i = 0; i < chapterValue; i++)
    {
        modelChapters->setItem(i, 0, new QStandardItem(QString::number(i + 1)));
    }


    if (f_type == "Bible")
    {
        ui->tableChapter->setModel(modelChapters);
        ui->tableChapter->resizeColumnsToContents();
    }

    if (f_type == "Book")
    {
        ui->tableChapterBook->setModel(modelChapters);
        ui->tableChapterBook->resizeColumnsToContents();
    }

    if (f_type == "Apocrypha")
    {
        ui->tableChapterApocrypha->setModel(modelChapters);
        ui->tableChapterApocrypha->resizeColumnsToContents();
    }

    m_lastNameOfBook  = f_ind.data(0).toString();
}
//------------------------------------------------------------------------------
void LeftPanel::showChapter(const QModelIndex ind, const QString f_type)
{
    QString t_nameOfBook;
    QModelIndexList selectedList;
    QString t_curModule;


    // bible
    if (f_type == "Bible")
    {
        selectedList = ui->tableBook->selectionModel()->selectedRows();
        t_curModule = ui->comBModules->currentText();
    }

    // book
    if (f_type == "Book")
    {
        selectedList = ui->tableBookBook->selectionModel()->selectedRows();
        t_curModule = ui->comBModulesBook->currentText();
    }

    if (f_type == "Apocrypha")
    {
        selectedList = ui->tableBookApocrypha->selectionModel()->selectedRows();
        t_curModule = ui->comBModulesApocrypha->currentText();
    }

    QString t_pathToModule = Config::configuration()->getAppDir() +
            Config::configuration()->getListModulesFromMap(f_type)->getModuleWithName(t_curModule)->getModulePath();

    for( int i = 0; i < selectedList.count(); i++)
    {
        t_nameOfBook = selectedList.at(i).data(0).toString();
    }
    m_lastNameOfBook = t_nameOfBook;


    t_pathToModule.replace("module" + GL_FORMAT_MODULE
                           , "text" + GL_FORMAT_TEXT);

    ModuleViewer::viewer()->setModuleName(t_curModule);
    ModuleViewer::viewer()->showChapter(t_curModule, m_lastNameOfBook ,
                                        ind.row() + 1, f_type);

    t_pathToModule.replace("text" + GL_FORMAT_TEXT, "notes" + GL_FORMAT_NOTES);
    emit SIGNAL_ShowNotes(t_curModule, m_lastNameOfBook, QString::number(ind.row() + 1), t_pathToModule);


    emit SIGNAL_AddRecordToJournal(t_curModule,
                                   m_lastNameOfBook ,
                                   QString::number(ind.row() + 1));
}
//------------------------------------------------------------------------------
void LeftPanel::showChapter(const QModelIndex ind)
{
    QTableView *t_table = (QTableView*)sender();
    // bible
    if (t_table == ui->tableChapter)
        showChapter(ind, "Bible");

    // book
    if (t_table == ui->tableChapterBook)
        showChapter(ind, "Book");

    // apocrypha
    if (t_table == ui->tableChapterApocrypha)
        showChapter(ind, "Apocrypha");
}
//------------------------------------------------------------------------------
void LeftPanel::refreshBookList(const QString nameOfModule, const QString f_type)
{
    modelBooks->clear();
    modelChapters->clear();

    int t_number;
    QString t_bookName;

    bool flag;
    bool flag2 = Config::configuration()->isExistLastChapter()
            and Config::configuration()->getOptionAutoChapter();

    QStringList bookList = Config::configuration()->getListModulesFromMap(f_type)->getModuleBooks(nameOfModule);

    if (f_type == "Bible")
        flag = (ui->tableBook->model() and flag2);

    if (f_type == "Book")
        flag = (ui->tableBookBook->model() and flag2);

    if (f_type == "Apocrypha")
        flag = (ui->tableBookApocrypha->model()and flag2);


    if (flag)
        t_number = getNumberOfBook(Config::configuration()->getLastBook());

    for (int i = 0; i < bookList.size() - 1; i++)
    {
        modelBooks->setItem(i, 0, new QStandardItem(bookList.at(i)));

        if (flag and t_number == getNumberOfBook(bookList.at(i)))
            t_bookName = bookList.at(i);
    }

    if (f_type == "Bible")
    {
        ui->tableBook->setModel(modelBooks);
        ui->tableBook->resizeColumnsToContents();

        if (flag)
            makeOptionAutoChapter(t_bookName);
    }

    if (f_type == "Book")
    {
        ui->tableBookBook->setModel(modelBooks);
        ui->tableBookBook->resizeColumnsToContents();
    }

    if (f_type == "Apocrypha")
    {
        ui->tableBookApocrypha->setModel(modelBooks);
        ui->tableBookApocrypha->resizeColumnsToContents();
    }
}
//------------------------------------------------------------------------------
void LeftPanel::refreshBookList(const QString nameOfModule)
{
    QComboBox *combo = (QComboBox*)sender();

    if (combo == ui->comBModules)
        refreshBookList(nameOfModule, "Bible");

    if (combo == ui->comBModulesBook)
        refreshBookList(nameOfModule, "Book");

    if (combo == ui->comBModulesApocrypha)
        refreshBookList(nameOfModule, "Apocrypha");
}
//------------------------------------------------------------------------------
void LeftPanel::refreshComboBooks()
{
    refreshBookList(ui->comBModulesBook->currentText(), "Book");
    refreshBookList(ui->comBModules->currentText(), "Bible");
    refreshBookList(ui->comBModulesApocrypha->currentText(), "Apocrypha");
}
//------------------------------------------------------------------------------
void LeftPanel::retranslate()
{
    ui->retranslateUi(this);
}
//------------------------------------------------------------------------------
void LeftPanel::showChapterFromJournal(const QString f_module, const QString f_book, const QString f_chapter)
{
    QString t_type = Config::configuration()->getTypeOfModule(f_module);

    if (!t_type.isEmpty())
    {
        QString t_pathToModule = Config::configuration()->getAppDir() +
                Config::configuration()->getListModulesFromMap(t_type)->getModuleWithName(f_module)->getModulePath();

        t_pathToModule.replace("module" + GL_FORMAT_MODULE
                               , "text" + GL_FORMAT_TEXT);
        m_lastNameOfBook  = f_book;


        // refresh tab for bible modules or book modules
        refreshBookList(f_module, t_type);

        if (t_type == "Bible")
        {
            ui->comBModules->setCurrentIndex(ui->comBModules->findText(f_module));
            ui->tabWidget->setCurrentIndex(ui->tabWidget->indexOf(ui->tabBible)); // bible
        }

        if (t_type == "Book")
        {
            ui->comBModulesBook->setCurrentIndex(ui->comBModulesBook->findText(f_module));
            ui->tabWidget->setCurrentIndex(ui->tabWidget->indexOf(ui->tabBook)); // book
        }

        if (t_type == "Apocrypha")
        {
            ui->comBModulesApocrypha->setCurrentIndex(ui->comBModulesApocrypha->findText(f_module));
            ui->tabWidget->setCurrentIndex(ui->tabWidget->indexOf(ui->tabApocrypha)); // apocrypha
        }

        ModuleViewer::viewer()->setModuleName(f_module);
        ModuleViewer::viewer()->showChapter(f_module, f_book,
                                            f_chapter.toInt());
    }
}
//------------------------------------------------------------------------------
void LeftPanel::refreshWordListFromDict(const QString curText)
{
    QString t_pathToFile = QString(Config::configuration()->getAppDir() + "dictionary/" +
                                   curText + "/dict" + GL_FORMAT_TEXT);
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
void LeftPanel::showDescriptionWord(const QString word)
{
    QString t_pathToFile = QString(Config::configuration()->getAppDir() + "dictionary/" +
                                   ui->comBDictList->currentText() + "/dict" + GL_FORMAT_TEXT);

    QString t_text = QString(tr("<b>Word: <i>%1</i></b><br><br>")).arg(word) + getDescriptionForWordFromDict(t_pathToFile, word);
    ui->view->setText(t_text);
}
//------------------------------------------------------------------------------
void LeftPanel::showDescriptionWordFromOtherModules(const QString word)
{
    QString t_pathToFile = QString(Config::configuration()->getAppDir() + "dictionary/" +
                                   ui->comBDictListFindWord->currentText() + "/dict" + GL_FORMAT_TEXT);

    QString t_text = getDescriptionForWordFromDict(t_pathToFile, word);
    ui->view->setText(t_text);
}
//------------------------------------------------------------------------------
void LeftPanel::showWord(const QModelIndex ind)
{
    QString word = ind.data(0).toString();
    m_curWord = word;
    showDescriptionWord(word);

    QStringList list = getListDictWithWord(word);

    ui->comBDictListFindWord->clear();
    ui->comBDictListFindWord->addItems(list);
}
//------------------------------------------------------------------------------
QStringList LeftPanel::getListDictWithWord(const QString word)
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
void LeftPanel::sShowHideLeftPanel2(const int f_tab)
{
    Q_UNUSED(f_tab);
    //    if (f_tab != GUI_TAB_DICT) // dict

    // show if select module
    if (ui->tabWidget->currentWidget() != ui->tabDictionary)
        emit SIGNAL_ShowHideLeftPanel2(false);

    //    switch (f_tab)
    //    {
    //    case GUI_TAB_BIBLE: refreshBookList(ui->comBModules->currentText(), "Bible"); break;
    //    case GUI_TAB_BOOK: refreshBookList(ui->comBModulesBook->currentText(), "Book"); break;
    //    case GUI_TAB_APOCRYPHA: refreshBookList(ui->comBModulesApocrypha->currentText(), "Apocrypha"); break;
    //        //    case GUI_TAB_OTHER: refreshBookList(ui->comBModulesBook->currentText(), "Other"); break;
    //    case GUI_TAB_DICT : emit SIGNAL_ShowHideLeftPanel2(true); // hide if select dict
    //    case GUI_TAB_COMMENTS: emit SIGNAL_ShowHideLeftPanel2(true); break;
    //    }

    if (ui->tabWidget->currentWidget() == ui->tabBible)
        refreshBookList(ui->comBModules->currentText(), "Bible");

    if (ui->tabWidget->currentWidget() == ui->tabBook)
        refreshBookList(ui->comBModulesBook->currentText(), "Book");

    if (ui->tabWidget->currentWidget() == ui->tabComments)
        emit SIGNAL_ShowHideLeftPanel2(true);

    if (ui->tabWidget->currentWidget() == ui->tabApocrypha)
        refreshBookList(ui->comBModulesApocrypha->currentText(), "Apocrypha");

    if (ui->tabWidget->currentWidget() == ui->tabDictionary)
        emit SIGNAL_ShowHideLeftPanel2(true);

}
//------------------------------------------------------------------------------
void LeftPanel::sUpdateGUI()
{
    if (!checkedNewAndOldChapter())
    {
        // old != new
        if (Config::configuration()->getLastType() == "Bible")
        {
            refreshBookList(Config::configuration()->getLastModule()
                            , Config::configuration()->getLastType());
            for (int i = 0; i < ui->tableBook->model()->rowCount(); i++)
            {
                if (ui->tableBook->model()->data(ui->tableBook->model()->index(i, 0), 0).toString() == Config::configuration()->getLastBook())
                {
                    ui->tabWidget->setCurrentIndex(ui->tabWidget->indexOf(ui->tabBible));
                    ui->comBModules->setCurrentIndex(ui->comBModules->findText(Config::configuration()->getLastModule()));
                    ui->tableBook->setCurrentIndex(ui->tableBook->model()->index(i, 0));
                    refreshChapterList(Config::configuration()->getLastType(), ui->tableBook->currentIndex());
                    ui->tableChapter->setCurrentIndex(ui->tableChapter->model()->index(Config::configuration()->getLastChapter().toInt() - 1, 0));
                }
            }
        }

        if (Config::configuration()->getLastType() == "Book")
        {
            refreshBookList(Config::configuration()->getLastModule()
                            , Config::configuration()->getLastType());

            for (int i = 0; i < ui->tableBookBook->model()->rowCount(); i++)
            {
                if (ui->tableBookBook->model()->data(ui->tableBookBook->model()->index(i, 0), 0).toString() == Config::configuration()->getLastBook())
                {
                    ui->tabWidget->setCurrentIndex(ui->tabWidget->indexOf(ui->tabBook));
                    ui->comBModulesBook->setCurrentIndex(ui->comBModulesBook->findText(Config::configuration()->getLastModule()));
                    ui->tableBookBook->setCurrentIndex(ui->tableBookBook->model()->index(i, 0));
                    refreshChapterList(Config::configuration()->getLastType(), ui->tableBookBook->currentIndex());
                    ui->tableChapterBook->setCurrentIndex(ui->tableChapterBook->model()->index(Config::configuration()->getLastChapter().toInt() - 1, 0));

                }
            }
        }

        if (Config::configuration()->getLastType() == "Apocrypha")
        {
            refreshBookList(Config::configuration()->getLastModule()
                            , Config::configuration()->getLastType());

            for (int i = 0; i < ui->tableBookApocrypha->model()->rowCount(); i++)
            {
                if (ui->tableBookApocrypha->model()->data(ui->tableBookApocrypha->model()->index(i, 0), 0).toString() == Config::configuration()->getLastBook())
                {
                    ui->tabWidget->setCurrentIndex(ui->tabWidget->indexOf(ui->tabApocrypha));
                    ui->comBModulesApocrypha->setCurrentIndex(ui->comBModulesApocrypha->findText(Config::configuration()->getLastModule()));
                    ui->tableBookApocrypha->setCurrentIndex(ui->tableBookApocrypha->model()->index(i, 0));
                    refreshChapterList(Config::configuration()->getLastType(), ui->tableBookApocrypha->currentIndex());
                    ui->tableChapterApocrypha->setCurrentIndex(ui->tableChapterApocrypha->model()->index(Config::configuration()->getLastChapter().toInt() - 1, 0));

                }
            }
        }
    }
}
//------------------------------------------------------------------------------
void LeftPanel::makeOptionAutoChapter(const QString f_bookName)
{
    // old != new
    if (Config::configuration()->isExistLastChapter() and Config::configuration()->getLastType() == "Bible"
            and ui->tableBook->model()->rowCount())
    {
        for (int i = 0; i < ui->tableBook->model()->rowCount(); i++)
        {
            if (ui->tableBook->model()->data(ui->tableBook->model()->index(i, 0), 0).toString() == f_bookName)
            {
                ui->tableBook->setCurrentIndex(ui->tableBook->model()->index(i, 0));
                refreshChapterList(Config::configuration()->getLastType(), ui->tableBook->currentIndex());
                ui->tableChapter->setCurrentIndex(ui->tableChapter->model()->index(Config::configuration()->getLastChapter().toInt() - 1, 0));
                showChapter(ui->tableChapter->currentIndex(), "Bible");
            }
        }
    }
}
//------------------------------------------------------------------------------
bool LeftPanel::checkedNewAndOldChapter()
{
    bool flag = false;
    if (Config::configuration()->getLastType() == "Bible"
            and !ui->comBModules->currentText().isEmpty()
            and ui->tableBook->verticalHeader()->count() != 0
            and !ui->tableBook->model()->data(ui->tableBook->currentIndex()).toString().isEmpty()
            and !ui->tableChapter->model()->data(ui->tableChapter->currentIndex()).toString().isEmpty())
    {
        flag = Config::configuration()->getLastModule() == ui->comBModules->currentText()
                and ui->tableBook->model()->data(ui->tableBook->currentIndex()).toString() == Config::configuration()->getLastBook();
        //                and ui->tableChapter->model()->data(ui->tableChapter->currentIndex()).toString() != Config::configuration()->getLastChapter();

    }

    if (Config::configuration()->getLastType() == "Book"
            and !ui->comBModulesBook->currentText().isEmpty()
            and ui->tableBookBook->verticalHeader()->count() != 0
            and !ui->tableBookBook->model()->data(ui->tableBookBook->currentIndex()).toString().isEmpty()
            and !ui->tableChapterBook->model()->data(ui->tableChapterBook->currentIndex()).toString().isEmpty()
            )
    {
        flag = Config::configuration()->getLastModule() == ui->comBModulesBook->currentText()
                and ui->tableBookBook->model()->data(ui->tableBookBook->currentIndex()).toString() == Config::configuration()->getLastBook();
        //                and ui->tableChapterBook->model()->data(ui->tableChapterBook->currentIndex()).toString() != Config::configuration()->getLastChapter();
    }

    return flag;
}
//------------------------------------------------------------------------------
void LeftPanel::sUpdateGUIDayMode()
{
    // todo
    // добавить настройку цвета шрифта
    // добавить настройку цвета выделения и тд и тп
    QPalette p = ui->tableBook->palette();
    if (Config::configuration()->getDayMode())
    {
        p.setColor(QPalette::Base, GL_COLOR_DAY);
    }
    else
    {
        p.setColor(QPalette::Base, GL_COLOR_NIGHT);
    }
    ui->tableBookBook->setPalette(p);
    ui->tableChapter->setPalette(p);
    ui->tableChapterBook->setPalette(p);
    ui->tableBook->setPalette(p);
    ui->ListViewWordList->setPalette(p);
    ui->view->setPalette(p);
    ui->comBWordList->setPalette(p);
    ui->comBDictList->setPalette(p);
    ui->comBModules->setPalette(p);
    ui->comBModulesBook->setPalette(p);
    ui->comBDictListFindWord->setPalette(p);
    ui->textBrComments->setPalette(p);
    ui->comBComments->setPalette(p);
    ui->comBModulesApocrypha->setPalette(p);
    ui->tableBookApocrypha->setPalette(p);
    ui->tableChapterApocrypha->setPalette(p);
}
//------------------------------------------------------------------------------
void LeftPanel::sSetCommentsFromModule(const QString f_nameModule)
{
    if (Config::configuration()->isExistLastChapter())
    {
        ui->textBrComments->setText(getCommentForChapter(Config::configuration()->getAppDir() + Config::configuration()->getListComments()->getModuleWithName(f_nameModule)->getModulePath()
                                                         , Config::configuration()->getLastBook()
                                                         , Config::configuration()->getLastChapter()));
    }
}
//------------------------------------------------------------------------------
void LeftPanel::loadComments()
{
    QSopherimModuleList* list = new QSopherimModuleList();
    list->refreshList("comments/");
    refreshListComments(list);
}
//------------------------------------------------------------------------------
void LeftPanel::loadDictionaries()
{
    QSopherimModuleList* list = new QSopherimModuleList();
    list->refreshList("dictionary/");
    refreshListDict(list);
}
//------------------------------------------------------------------------------
void LeftPanel::loadModules()
{
    QSopherimModuleList* list = new QSopherimModuleList();
    list->refreshList();
    Config::configuration()->setListBibles(list);
    refreshListModule(list, "Bible");
}
//------------------------------------------------------------------------------
void LeftPanel::loadBooks()
{
    QSopherimModuleList* list = new QSopherimModuleList();
    list->refreshList("book/");
    Config::configuration()->setListBook(list);
    refreshListModule(list, "Book");
}
//------------------------------------------------------------------------------
void LeftPanel::loadApocrypha()
{
    QSopherimModuleList* list = new QSopherimModuleList();
    list->refreshList("apocrypha/");
    Config::configuration()->setListApocrypha(list);
    refreshListModule(list, "Apocrypha");
}
//------------------------------------------------------------------------------
void LeftPanel::showHideTabs()
{
    //    if (ui->comBModules->count() == 0)
    //        ui->tabWidget->removeTab(ui->tabWidget->indexOf(ui->tabBible));

    if (ui->comBModulesBook->count() == 0)
        ui->tabWidget->removeTab(ui->tabWidget->indexOf(ui->tabBook));

    if (ui->comBModulesApocrypha->count() == 0)
        ui->tabWidget->removeTab(ui->tabWidget->indexOf(ui->tabApocrypha));

    if (ui->comBComments->count() == 0)
        ui->tabWidget->removeTab(ui->tabWidget->indexOf(ui->tabComments));

    if (ui->comBDictList->count() == 0)
        ui->tabWidget->removeTab(ui->tabWidget->indexOf(ui->tabDictionary));

}
//------------------------------------------------------------------------------
void LeftPanel::loadFirstBook()
{
    refreshBookList(ui->comBModules->currentText(), "Bible");
}
//------------------------------------------------------------------------------
void LeftPanel::sUpdateGUIFont()
{
    ui->comBModules->setFont(Config::configuration()->getGUIMapFont()["ModulesName"]);
    ui->comBModulesBook->setFont(Config::configuration()->getGUIMapFont()["ModulesName"]);
    ui->comBComments->setFont(Config::configuration()->getGUIMapFont()["ModulesName"]);
    ui->comBModulesApocrypha->setFont(Config::configuration()->getGUIMapFont()["ModulesName"]);

    ui->tableBook->setFont(Config::configuration()->getGUIMapFont()["BookName"]);
    ui->tableBookBook->setFont(Config::configuration()->getGUIMapFont()["BookName"]);
    ui->tableBookApocrypha->setFont(Config::configuration()->getGUIMapFont()["BookName"]);
    ui->textBrComments->setFont(Config::configuration()->getGUIMapFont()["BookName"]);
}
//------------------------------------------------------------------------------
