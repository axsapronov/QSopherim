/*
  The basis for creating an application
  (QMainwindow)

  Tray + translate + about dialog + mainwindow

  Author: Sapronov Alexander
  E-mail: sapronov.alexander92@gmail.com
  */

#include "ui_mainwindow.h" /// ui
#include "mainwindow.h" ///

#include <QUrl> /// open home site
#include <QCloseEvent>
#include <QMessageBox>
#include <QFileDialog> /// open module (test)
#include <QDesktopServices> /// tray
#include <QDesktopWidget> /// moved to center

#include <QTranslator>

#include "defines.h" /// defines
#include "config.h"
#include "filecommon.h"
#include "stringcommon.h"

#include <QProgressDialog>
#include <QProgressBar>
#include <QLabel>
#include <QApplication>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle(QString("%1 - %2").arg(GL_PROG_NAME).arg(GL_PROG_VERSION_STR));
    init();
    //    convertModulesFromFolder();
    //    convertDictFromFolder();

    // load modules
    GUI_LeftPanel->loadModules();
    GUI_LeftPanel->loadDictionaries();
    GUI_LeftPanel->loadComments();

    // open last text
    GUI_ModuleViewer->openLastChapter();
    GUI_LeftPanel2->loadJournal();

    //    loadModules();
    //        debug();
    ui->menuBar->setFont(Config::configuration()->getGUIMapFont()["FontMenu"]);
}
//------------------------------------------------------------------------------
MainWindow::~MainWindow()
{
    delete GUI_About;
    delete GUI_Settings;

    GUI_RightPanel->saveBookmarks();
    delete GUI_RightPanel;

    delete GUI_LeftPanel;
    delete GUI_LeftPanel2;
    delete GUI_ModuleViewer;
    delete GUI_NoteEditor;
    delete GUI_ManagerModules;
    delete GUI_FindDialog;
    delete GUI_ModuleImportDialog;

    delete trayIconMenu;
    delete trIcon;
    delete minimizeAction;
    delete maximizeAction;
    delete restoreAction;
    delete quitAction;

    delete prModule;

    delete ui;
}
//------------------------------------------------------------------------------
void MainWindow::init()
{
    GUI_About = new AboutDialog(this);
    GUI_Settings = new Settings(this);

    GUI_ManagerModules = new ManagerModules(this);
    GUI_FindDialog = new FindDialog(this);
    GUI_ModuleImportDialog = new ModuleImportDialog(this);

    /// panel init
    GUI_RightPanel = new RightPanel(this);
    GUI_LeftPanel = new LeftPanel(this);
    GUI_LeftPanel2 = new LeftPanel2(this);

    // to hide the title bar completely must replace the default widget with a generic one
    QWidget* t_titleBar = GUI_LeftPanel2->titleBarWidget();
    QWidget* t_emptyWidget2 = new QWidget();
    GUI_LeftPanel2->setTitleBarWidget(t_emptyWidget2);
    delete t_titleBar;

    t_titleBar = GUI_LeftPanel->titleBarWidget();
    QWidget* t_emptyWidget = new QWidget();
    GUI_LeftPanel->setTitleBarWidget(t_emptyWidget);
    delete t_titleBar;

    t_titleBar = GUI_RightPanel->titleBarWidget();
    QWidget* t_emptyWidget3 = new QWidget();
    GUI_RightPanel->setTitleBarWidget(t_emptyWidget3);
    delete t_titleBar;

    GUI_RightPanel->loadBookmarks();
    //    GUI_BottomPanel = new BottomPanel(this);

    GUI_RightPanel->setMinimumWidth(250);
    GUI_LeftPanel->setMinimumWidth(300);
//    GUI_LeftPanel->setMaximumWidth(350);
//    GUI_LeftPanel2->setMaximumWidth(350);
    GUI_LeftPanel2->setMinimumWidth(300);

    //    GUI_BottomPanel->setMinimumHeight(100);
    addDockWidget(Qt::LeftDockWidgetArea, GUI_LeftPanel);
    addDockWidget(Qt::LeftDockWidgetArea, GUI_LeftPanel2);
    addDockWidget(Qt::RightDockWidgetArea, GUI_RightPanel);
    //    addDockWidget(Qt::BottomDockWidgetArea, GUI_BottomPanel);

    GUI_RightPanel->hide();
    prModule = new ProcessModule();

    //    centralWidget()->setAttribute(Qt::WA_TransparentForMouseEvents);
    //    setMouseTracking(true);

    // load settings
    // replace to QString t_lang = GUI_Settings->getAppLang()
    // and switch t_lang?
    // and load load module settings
    GUI_Settings->loadSettings();
    if (GUI_Settings->getAPPLang() == "Russian" )
    {
        setLangRu();
    }
    if (GUI_Settings->getAPPLang() == "English")
    {
        setLangEn();
    }
    if (GUI_Settings->getAPPLang() == "Deutsch")
    {
        setLangDe();
    }
    if (GUI_Settings->getAPPLang() == "Français")
    {
        setLangFr();
    }

    //    ui->centralWidget->setMouseTracking(true);
    GUI_ModuleViewer = new ModuleViewer(this);
    GUI_NoteEditor = new NoteEditor(this);

    //    GUI_ModuleViewer->setMouseTracking(true);
    this->setCentralWidget(GUI_ModuleViewer);

    // Create menu for hide show panels and toolbars
    QAction *viewsAction = createPopupMenu() -> menuAction();
    viewsAction -> setText(tr("Toolbars and panels"));
    ui->mView->addAction(viewsAction);

    /// moved to center desktop
    //    QRect rect = QApplication::desktop()->availableGeometry(this);
    //    this->move(rect.width() / 2 - this->width() / 2,
    //               rect.height() / 2 - this->height() / 2);
    /// maximized
    this->showMaximized();

    createActions(); // create action for tray
    createTrayIcon(); // add actionts to tray menu

    createConnects(); // moved func

    showHideTray();
}
//------------------------------------------------------------------------------
void MainWindow::debug()
{
    //    QStringList fileName;
    //    fileName << "/home/files/Documents/Bible/unrar/Book_Spurgeon/bibleqt.ini";
    //    fileName << "/home/files/Documents/Bible/unrar/my/BIBLEQT.INI";
    //    fileName << "/home/files/Documents/Bible/unrar/NT_Russian_Kassian/Bibleqt.ini";
    //    fileName << "/home/files/Documents/Bible/unrar/Makarij/bibleqt.ini";


    //    QString str = "fasf 0432 fsdf 5635 fasdf" ;

    //    QRegExp rx("(\\d+)");

    //    myDebug() << str;
    //    QString str = "Offsets: 12 14 99 231 7";
    //    QStringList list;
    //    int pos = 0;

    //    while ((pos = rx.indexIn(str, pos)) != -1) {
    ////        list << rx.cap(1);
    //        str.replace(rx.cap(1), "<sup>" + rx.cap(1) + "</sup>");
    //        pos += rx.matchedLength() + 11;
    //    }
    //    myDebug() << list << str;
    // list: ["12", "14", "99", "231", "7"]


    //    QString fileStrong;
    //    fileStrong = "/home/files/Documents/Bible/oteh/Strongs/HEBREW.HTM";
    //    createListStrongs(fileStrong);
    ////    fileStrong = "/home/files/Develop/git/QSopherim/QSopherim-build-desktop/build/bin/strongs/strong.xml";
    ////    GUI_ModuleViewer->setStrongList(fileStrong);


    //    QHash<QString, QVector<int> > hash;

    //    QString str;
    //    str = "fsa2f fsaf asfas f4 f43 3 2 23d23 sfsd";
    //    myDebug() << getNextWord(str, 6);

    //    //    QString str = "";
    //    //    if (str.isEmpty())
    //    //    {
    //    //        myDebug() << "yes";
    //    //    }

    //    //    QString str;
    //    //    QString l1 = "module=\"Пятикнижие (перевод архим. Макария)\"";
    //    //    QString l2
    //    ////    str = "<note module=\"Пятикнижие (перевод архим. Макария)\" book=\"Левит\" chapter=\"3\" versebegin=\"0\" verseend=\"1\">gsadgsad";
    //    //    myDebug() << str;
    //    //    if (str.contains(l1) &&
    //    //            && )
    //    //    {
    //    //        myDebug() << "yes";
    //    //    }

    //    //    convertModulesFromFolder();
    //    //    for (int i = 0; i < fileName.size(); i++)
    //    //    {
    //    //        prModule->processing(fileName.at(i), OBVCore::Type_BibleQuoteModule);
    //    //    }

    //    // > 62
    //    // < 60
    //    //    // " " 127
    //    //        for (int i = 0; i < 255; i++)
    //    //        {
    //    //            myDebug() << QChar(i) << i;
    //    //        }
}
//------------------------------------------------------------------------------
void MainWindow::createConnects()
{
    if (Config::configuration()->getGuiTray())
    {
        //tray
        connect(trIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)), SLOT(showHide(QSystemTrayIcon::ActivationReason)));
    }

    // menu file
    connect(ui->action_File_Close, SIGNAL(triggered()), this, SLOT(close()));

    // menu settings
    connect(ui->action_Settings_General, SIGNAL(triggered()), SLOT(showSettings()));
    connect(GUI_Settings, SIGNAL(SIGNAL_UpdateTray()), SLOT(showHideTray()));

    connect(ui->action_Settings_Module_Import, SIGNAL(triggered()), GUI_ModuleImportDialog, SLOT(show()));

    // manager module
    connect(ui->action_Settings_Module, SIGNAL(triggered()), SLOT(showModuleManager()));

    //menu settings -> lang
    connect(ui->action_Settings_Language_Russian, SIGNAL(triggered()), SLOT(setLangRu()) );
    connect(ui->action_Settings_Language_English, SIGNAL(triggered()), SLOT(setLangEn()) );
    connect(ui->action_Settings_Language_Deutsch, SIGNAL(triggered()), SLOT(setLangDe()) );
    connect(ui->action_Settings_Language_France, SIGNAL(triggered()),  SLOT(setLangFr()) );

    // menu search

    // toolbar
    connect(ui->actionAction_Other_Create_Note, SIGNAL(triggered()), SLOT(createNote()));
//    connect(ui->actionAction_Other_Update_List_Module, SIGNAL(triggered()), SLOT(convertModulesFromFolder()));

    // menu about
    connect(ui->action_About_About, SIGNAL(triggered()), GUI_About, SLOT(show()));
    connect(ui->action_About_About_Qt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(ui->action_About_Site, SIGNAL(triggered()), this, SLOT(aboutOpenSite()));
    connect(ui->action_About_Help, SIGNAL(triggered()), SLOT(showHelp()));

    // other
//    connect(prModule, SIGNAL(SIGNAL_ProcessModuleOk()), GUI_LeftPanel, SLOT(loadModules()));
//    connect(prModule, SIGNAL(SIGNAL_ProcessDictOk()), GUI_LeftPanel, SLOT(loadDictionaries()));
//    connect(prModule, SIGNAL(SIGNAL_ProcessCommentsOk()), GUI_LeftPanel, SLOT(loadComments()));

    // module viewer
    connect(GUI_ModuleViewer, SIGNAL(SIGNAL_ShowNoteList(QString,QString,QString,QString,QString)),
            GUI_LeftPanel2, SLOT(showNoteList(QString,QString,QString,QString,QString)));
    connect(GUI_ModuleViewer, SIGNAL(SIGNAL_ShowStrong(QString)),
            GUI_LeftPanel2, SLOT(showStrong(QString)));
    connect(GUI_ModuleViewer, SIGNAL(SIGNAL_AddNote()), SLOT(createNote()));

    connect(GUI_ModuleViewer, SIGNAL(SIGNAL_ShowChapterFinish())
            , GUI_LeftPanel, SLOT(sUpdateGUI()));

    // settings
    connect(GUI_Settings, SIGNAL(SIGNAL_RetranslateGUI(QString)),
            SLOT(retranslate(QString)));

    // manager module
    connect(GUI_ManagerModules, SIGNAL(SIGNAL_RefreshModules()), GUI_LeftPanel, SLOT(loadDictionaries()));
    connect(GUI_ManagerModules, SIGNAL(SIGNAL_RefreshModules()), GUI_LeftPanel, SLOT(loadModules()));

    connect(GUI_ManagerModules, SIGNAL(SIGNAL_SetGreekStrong(QString))
            , GUI_LeftPanel2, SLOT(sSetStrongGreek(QString)));
    connect(GUI_ManagerModules, SIGNAL(SIGNAL_SetHebrewStrong(QString))
            , GUI_LeftPanel2, SLOT(sSetStrongHebrew(QString)));

    // import modules
    connect(GUI_ModuleImportDialog, SIGNAL(SIGNAL_StartConvertModules()), SLOT(convertModulesFromFolder()));
    connect(GUI_ModuleImportDialog, SIGNAL(SIGNAL_StartConvertDict()), SLOT(convertDictFromFolder()));
    connect(GUI_ModuleImportDialog, SIGNAL(SIGNAL_StartConvertComments()), SLOT(convertCommentsFromFolder()));
    connect(GUI_ModuleImportDialog, SIGNAL(SIGNAL_StartConvertApocrypha()), SLOT(convertApocryphaFromFolder()));

    // connect fron left1 to left2 panels
    connect(GUI_LeftPanel, SIGNAL(SIGNAL_AddRecordToJournal(QString,QString,QString))
            , GUI_LeftPanel2, SLOT(addRecordToJournal(QString,QString,QString)));

    connect(GUI_LeftPanel2, SIGNAL(SIGNAL_ShowChapterFromJournal(QString,QString,QString))
            , GUI_LeftPanel, SLOT(showChapterFromJournal(QString,QString,QString)));

    connect(GUI_LeftPanel, SIGNAL(SIGNAL_ShowHideLeftPanel2(bool))
            , GUI_LeftPanel2, SLOT(setHidden(bool)));

    // connect settings and module viewer
    connect(GUI_Settings, SIGNAL(SIGNAL_ReLoadFontSettings()), GUI_ModuleViewer,
            SLOT(updateFontSettings()));

    connect(GUI_ModuleViewer, SIGNAL(SIGNAL_AddNewBookmark(QString)),
            GUI_RightPanel, SLOT(addNewBookmark(QString)));


    connect(GUI_Settings, SIGNAL(SIGNAL_UpdateDayMode()), GUI_LeftPanel, SLOT(sUpdateGUIDayMode()));
    connect(GUI_Settings, SIGNAL(SIGNAL_UpdateDayMode()), GUI_LeftPanel2, SLOT(sUpdateGUIDayMode()));


    // connect find dialog to left2 panel
    connect(GUI_FindDialog, SIGNAL(SIGNAL_ShowChapter(QString, QString, QString)),
            GUI_LeftPanel, SLOT(showChapterFromJournal(QString,QString,QString)));


    connect(GUI_RightPanel, SIGNAL(SIGNAL_OpenBookmark(QString, QString, QString)),
            GUI_LeftPanel, SLOT(showChapterFromJournal(QString,QString,QString)));
    connect(GUI_RightPanel, SIGNAL(SIGNAL_OpenBookmark(QString, QString, QString)),
            GUI_LeftPanel2, SLOT(addRecordToJournal(QString,QString,QString)));

    // menu search
    connect(ui->action_Search_Find_In_Text, SIGNAL(triggered()), GUI_ModuleViewer,
            SLOT(find()));
    connect(ui->action_Search_Find_Next, SIGNAL(triggered()), GUI_ModuleViewer,
            SLOT(findNext()));
    connect(ui->action_Search_Find_Previous, SIGNAL(triggered()), GUI_ModuleViewer,
            SLOT(findPrevious()));
    connect(ui->action_Search_Find_In_Modules, SIGNAL(triggered()), SLOT(findInModules()));
}
//------------------------------------------------------------------------------
void MainWindow::showHide(QSystemTrayIcon::ActivationReason r)
{
    if (r == QSystemTrayIcon::Trigger)
    {
        if ( !this->isVisible() )
        {
            this->show();
        }
        else
        {
            this->hide();
        }
    }
}
//------------------------------------------------------------------------------
void MainWindow::createTrayIcon()
{
    trIcon = new QSystemTrayIcon();  //init
    trIcon->setIcon(QIcon(":/images/images/img.png"));  //set ico

    trayIconMenu = new QMenu(this);  // create menu
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(maximizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    trIcon->setContextMenu(trayIconMenu); //set menu
}
//------------------------------------------------------------------------------
void MainWindow::createActions()
{
    minimizeAction = new QAction(tr("&Hide"), this);
    connect(minimizeAction, SIGNAL(triggered()), this, SLOT(hide()));

    maximizeAction = new QAction(tr("&Expand"), this);
    connect(maximizeAction, SIGNAL(triggered()), this, SLOT(showMaximized()));

    restoreAction = new QAction(tr("&Restore"), this);
    connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));

    quitAction = new QAction(tr("Q&uit"), this);
    connect(quitAction, SIGNAL(triggered()), this, SLOT(close()));
}
//------------------------------------------------------------------------------
void MainWindow::setLangEn()
{
    ui->action_Settings_Language_Deutsch ->setChecked(false);
    ui->action_Settings_Language_Russian ->setChecked(false);
    ui->action_Settings_Language_France ->setChecked(false);
    ui->action_Settings_Language_English ->setChecked(true);
    QString t_lang = "English";
    if (Config::configuration()->getAppLang() != t_lang)
    {
        retranslate(t_lang);
    }
}

//------------------------------------------------------------------------------
void MainWindow::setLangRu()
{
    ui->action_Settings_Language_Deutsch ->setChecked(false);
    ui->action_Settings_Language_Russian ->setChecked(true);
    ui->action_Settings_Language_France ->setChecked(false);
    ui->action_Settings_Language_English ->setChecked(false);
    QString t_lang = "Russian";
    if (Config::configuration()->getAppLang() != t_lang)
    {
        retranslate(t_lang);
    }
}
//------------------------------------------------------------------------------
void MainWindow::setLangDe()
{
    ui->action_Settings_Language_Deutsch ->setChecked(true);
    ui->action_Settings_Language_Russian ->setChecked(false);
    ui->action_Settings_Language_France ->setChecked(false);
    ui->action_Settings_Language_English ->setChecked(false);
    QString t_lang = "Deutch";
    if (Config::configuration()->getAppLang() != t_lang)
    {
        retranslate(t_lang);
    }
}
//------------------------------------------------------------------------------
void MainWindow::setLangFr()
{
    ui->action_Settings_Language_Deutsch ->setChecked(false);
    ui->action_Settings_Language_Russian ->setChecked(false);
    ui->action_Settings_Language_France ->setChecked(true);
    ui->action_Settings_Language_English ->setChecked(false);

    QString t_lang = "Français";
    if (Config::configuration()->getAppLang() != t_lang)
    {
        retranslate(t_lang);
    }
}
//------------------------------------------------------------------------------
void MainWindow::aboutOpenSite()
{
    QDesktopServices::openUrl(QUrl(GL_WEB_SITE));
}
//------------------------------------------------------------------------------
void MainWindow::showSettings()
{
    //set sett
    GUI_Settings->show();
}
//------------------------------------------------------------------------------
void MainWindow::showModuleManager()
{
    //set sett
    GUI_LeftPanel->setListModuleFromList();
    GUI_ManagerModules->loadListModules();
    GUI_ManagerModules->loadStrongList();
    GUI_ManagerModules->show();
}
//------------------------------------------------------------------------------
void MainWindow::closeEvent(QCloseEvent *e)
{
    //    myDebug()<< "closeEvent()";
    saveSettings();
    e -> accept();
}
//------------------------------------------------------------------------------
//void MainWindow::mouseMoveEvent(QMouseEvent *e)
//{
//    //    myDebug()<< "closeEvent()";
////    saveSettings();
////    e -> accept();
////    int x = e->pos().x() - GUI_NoteEditor->geometry().x();
////    int y = e->pos().y() - GUI_NoteEditor->geometry().y();
//////    myDebug() << e->pos() - GUI_NoteEditor->geometry().x;
////    myDebug() << e->pos();
////    myDebug() << x << y;
////    GUI_NoteEditor->mouseMoveEvent(e);
//}
//------------------------------------------------------------------------------
void MainWindow::saveSettings()
{
    Config *config = Config::configuration();
    //    myDebug() << "src = start to save settings";
    //    config -> setSideBarPage(helpDock -> tabWidget() -> currentIndex());
    //    config -> setWindowGeometry(saveGeometry());
    //    config -> setMainWindowState(saveState());

    //    // Create list of the tab urls
    //    QStringList lst;
    //    QList<HelpWindow*> browsers = tabs -> browsers();
    //    foreach (HelpWindow *browser, browsers){
    //        //        myDebug() << "src = " << browser -> source().toString();
    //        lst << relatifyFileName(browser -> source().toString(), config -> PrjDir());
    //        //        myDebug() << "lst = " << lst;
    //    }
    //    config -> setSource(lst);
    config -> saveSettings();
}
//------------------------------------------------------------------------------
void MainWindow::showHelp()
{
    //    HtmlHelp(NULL, "help.chm", HH_DISPLAY_TOPIC, 0);
}
//------------------------------------------------------------------------------
void MainWindow::convertModules(const QString f_type)
{
    if (!Config::configuration()->getBibleDir().isEmpty())
    {
        QProgressDialog loadProgress("", "It's not Cancel", 0, 100);
        loadProgress.setValue(0);
        loadProgress.setMinimumWidth(300);
        // move center
        QRect rect = QApplication::desktop()->availableGeometry(this);
        loadProgress.move(rect.width() / 2 - loadProgress.width() / 2,
                          rect.height() / 2 - loadProgress.height() / 2 );
        loadProgress.setWindowTitle(tr("Convert") + QString(" | %1 - %2").arg(GL_PROG_NAME).arg(GL_PROG_VERSION_STR));
        loadProgress.show();


        QLabel overallLabel(&loadProgress);
        overallLabel.setGeometry(11, 10, 400, 20);
        QStringList listModules;

        if (f_type == "Book" or f_type == "Bible")
        {
            overallLabel.setText(tr("Convert: bible modules"));
            overallLabel.show();
            listModules = getListModulesFromPath(Config::configuration()->getBibleDir(), ".ini");
            for (int i = 0; i < listModules.size(); i++)
            {
                prModule->processing(listModules.at(i), OBVCore::Type_BibleQuoteModule);
                loadProgress.setValue(100 * i / listModules.size());
                QApplication::processEvents();
            }
            GUI_LeftPanel->loadModules();
        }

        if (f_type == "Dictionary")
        {
            overallLabel.setText(tr("Convert: dictionary modules"));
            overallLabel.show();
            listModules = getListModulesFromPath(
                        Config::configuration()->getDictDir()
                        , ".idx");
            for (int i = 0; i < listModules.size(); i++)
            {
                prModule->processing(listModules.at(i), OBVCore::Type_BibleQuoteDictModule);
                loadProgress.setValue(100 * i / listModules.size());
                QApplication::processEvents();
            }
            GUI_LeftPanel->loadDictionaries();
        }

        if (f_type == "Comments")
        {
            overallLabel.setText(tr("Convert: comments modules"));
            overallLabel.show();
            listModules = getListModulesFromPath(
                        Config::configuration()->getBibleDir()
                        , ".ini");

            for (int i = 0; i < listModules.size(); i++)
            {
                prModule->processing(listModules.at(i), OBVCore::Type_BibleQuoteComments);
                loadProgress.setValue(100 * i / listModules.size());
                QApplication::processEvents();
            }
            GUI_LeftPanel->loadComments();
        }


        if (f_type == "Apocrypha")
        {
            overallLabel.setText(tr("Convert: apocrypha modules"));
            overallLabel.show();
            listModules = getListModulesFromPath(Config::configuration()->getApocryphaDir(), ".ini");
            for (int i = 0; i < listModules.size(); i++)
            {
                prModule->processing(listModules.at(i), OBVCore::Type_BibleQuoteApocrypha);
                loadProgress.setValue(100 * i / listModules.size());
                QApplication::processEvents();
            }
            GUI_LeftPanel->loadApocrypha();
        }


    }
    else
    {
        GUI_LeftPanel->loadModules();
    }
}
//------------------------------------------------------------------------------
void MainWindow::convertModulesFromFolder()
{
    convertModules("Bible");
}
//------------------------------------------------------------------------------
void MainWindow::convertDictFromFolder()
{
    convertModules("Dictionary");
}
//------------------------------------------------------------------------------
//void MainWindow::loadModules()
//{
//    QProgressDialog loadProgress("", "It's not Cancel", 0, 100);
//    loadProgress.setValue(0);
//    loadProgress.setGeometry(750, 300, 400, 170);
//    loadProgress.show();

//    QLabel overallLabel(&loadProgress);
//    overallLabel.setGeometry(11, 10, 378, 20);
//    overallLabel.setText("Load modules");
//    overallLabel.show();

//    QStringList listModules = getListModulesFromPath(Config::configuration()->getBibleDir());
//    for (int i = 0; i < listModules.size(); i++)
//    {
//        prModule->processing(listModules.at(i), OBVCore::Type_BibleQuoteModule);
//        loadProgress.setValue(100 * i / listModules.size());
//        QApplication::processEvents();
//    }


//    listModules = getListModulesFromPath(
//                Config::configuration()->getDictDir()
//                , ".idx");
//    for (int i = 0; i < listModules.size(); i++)
//    {
//        prModule->processing(listModules.at(i), OBVCore::Type_BibleQuoteDictModule);
//        loadProgress.setValue(100 * i / listModules.size());
//        QApplication::processEvents();
//    }

//}
//------------------------------------------------------------------------------
void MainWindow::createNote()
{
    if (GUI_ModuleViewer->getModuleName().isEmpty())
        return;
    if (GUI_ModuleViewer->getChapterValue().isEmpty())
        return;

    GUI_NoteEditor->setPath(GUI_ModuleViewer->getPath());
    GUI_NoteEditor->setModuleName(GUI_ModuleViewer->getModuleName());
    GUI_NoteEditor->setBookName(GUI_ModuleViewer->getBookName());
    GUI_NoteEditor->setChapterValue(GUI_ModuleViewer->getChapterValue());
    GUI_NoteEditor->setVerse(GUI_ModuleViewer->getLastNumberLine());
    GUI_NoteEditor->show();
}
//------------------------------------------------------------------------------
void MainWindow::retranslate(QString t_lang)
{
    // remove translate
    QString lan = "QSopherim_" + getShortLang(Config::configuration()->getAppLang());
    QTranslator translator2;
    translator2.load(lan,":lang/lang");

    qApp->removeTranslator(&translator2);
    ui->retranslateUi(this);

    // set new translate
    Config::configuration()->setAppLang(t_lang);
    QTranslator translator;
    lan = "QSopherim_" + getShortLang(t_lang);
    translator.load(lan,":lang/lang");
    qApp->installTranslator(&translator);

    ui->retranslateUi(this);

    GUI_About->retranslate();    // about dialog
    GUI_Settings->retranslate();
    GUI_RightPanel->retranslate();
    GUI_LeftPanel->retranslate();
    GUI_LeftPanel2->retranslate();
    //    GUI_BottomPanel->retranslate();
    GUI_ModuleViewer->retranslate();
    GUI_NoteEditor->retranslate();

}
//------------------------------------------------------------------------------
void MainWindow::findInModules()
{
    GUI_FindDialog->preShowDialog();
    GUI_FindDialog->show();
}
//------------------------------------------------------------------------------
void MainWindow::showHideTray()
{
    if (Config::configuration()->getGuiTray())
    {
        trIcon->show();  //display tray
    }
    else
    {
        trIcon->hide();
    }
}
//------------------------------------------------------------------------------
void MainWindow::convertCommentsFromFolder()
{
    convertModules("Comments");
}
//------------------------------------------------------------------------------
void MainWindow::convertApocryphaFromFolder()
{
    convertModules("Apocrypha");
}
//------------------------------------------------------------------------------
