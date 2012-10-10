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

#include "defines.h" /// defines
#include "about.h" /// aboutdialog
#include "settings.h"
#include "config.h"

#include "leftpanel.h" /// leftPanel
#include "leftpanel2.h"
#include "rightpanel.h" /// rightPanel
#include "bottompanel.h" /// bottomPanel
#include "moduleviewer.h"
#include "processmodule.h"
#include "moduledefinition.h"
#include "debughelper.h"
#include "projectqmodulelist.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
    debug();
}
//------------------------------------------------------------------------------
MainWindow::~MainWindow()
{
    delete ui;
}
//------------------------------------------------------------------------------
void MainWindow::init()
{
    GUI_About = new AboutDialog(this);
    GUI_Settings = new Settings(this);

    /// panel init
    GUI_RightPanel = new RightPanel();
    GUI_LeftPanel = new LeftPanel(this);
    //    GUI_LeftPanel2 = new LeftPanel2(this);
    //    GUI_BottomPanel = new BottomPanel(this);

    GUI_RightPanel->setMinimumWidth(200);
    GUI_LeftPanel->setMinimumWidth(200);
    //    GUI_BottomPanel->setMinimumHeight(100);
    addDockWidget(Qt::LeftDockWidgetArea, GUI_LeftPanel);
    //    addDockWidget(Qt::LeftDockWidgetArea, GUI_LeftPanel2);
    //    addDockWidget(Qt::RightDockWidgetArea, GUI_RightPanel);
    //    addDockWidget(Qt::BottomDockWidgetArea, GUI_BottomPanel);

    prModule = new ProcessModule();


    GUI_ModuleViewer = new ModuleViewer(this);
    setCentralWidget(GUI_ModuleViewer);
    /// load settings
    // replace to QString t_lang = GUI_Settings->getAppLang()
    // and switch t_lang?
    /// and load load module settings
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

    /// moved to center desktop
    //    QRect rect = QApplication::desktop()->availableGeometry(this);
    //    this->move(rect.width() / 2 - this->width() / 2,
    //               rect.height() / 2 - this->height() / 2);
    /// maximized
    this->showMaximized();

    createActions(); // create action for tray
    createTrayIcon(); // add actionts to tray menu
    createConnects(); // moved func
    trIcon->show();  //display tray

}
//------------------------------------------------------------------------------
void MainWindow::debug()
{
    QStringList fileName;

//    fileName << "/home/files/Documents/Bible/unrar/Book_Spurgeon/bibleqt.ini";
    fileName << "/home/files/Documents/Bible/unrar/my/BIBLEQT.INI";
//    fileName << "/home/files/Documents/Bible/unrar/NT_Russian_Kassian/Bibleqt.ini";
//    fileName << "/home/files/Documents/Bible/unrar/Makarij/bibleqt.ini";

    for (int i = 0; i < fileName.size(); i++)
    {
        prModule->processing(fileName.at(i), OBVCore::Type_BibleQuoteModule);
    }

    // > 62
    // < 60
//    for (int i = 0; i < 255; i++)
//    {
//        myDebug() << QChar(i) << i;
//    }
}
//------------------------------------------------------------------------------
void MainWindow::createConnects()
{
    //tray
    connect(trIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)), SLOT(showHide(QSystemTrayIcon::ActivationReason)));

    // menu file
    connect(ui->action_File_Close, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->action_File_Open_Module_Test, SIGNAL(triggered()), SLOT(openModule()));

    // menu settings
    connect(ui->action_Settings_General, SIGNAL(triggered()), SLOT(showSettings()));

    //menu settings -> lang
    connect(ui->action_Settings_Language_Russian, SIGNAL(triggered()), SLOT(setLangRu()) );
    connect(ui->action_Settings_Language_English, SIGNAL(triggered()), SLOT(setLangEn()) );
    connect(ui->action_Settings_Language_Deutsch, SIGNAL(triggered()), SLOT(setLangDe()) );
    connect(ui->action_Settings_Language_France, SIGNAL(triggered()),  SLOT(setLangFr()) );

    // menu search


    // menu about
    connect(ui->action_About_About, SIGNAL(triggered()), GUI_About, SLOT(show()));
    connect(ui->action_About_About_Qt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(ui->action_About_Site, SIGNAL(triggered()), this, SLOT(aboutOpenSite()));
    connect(ui->action_About_Help, SIGNAL(triggered()), SLOT(showHelp()));

    /// other
    connect(prModule, SIGNAL(signal_processOk()), SLOT(processFinish()));
    //    connect(prModule, SIGNAL(signal_processOk()), SLOT(processFinish()));
    //    connect(QO)
    //    connect(prModule, SIGNAL(signal_processOk()), SLOT(processFinish()));
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
    trIcon->setIcon(QIcon(":/images/img.png"));  //set ico

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
        Config::configuration()->setAppLang(t_lang);
        QMessageBox msgBox;
        msgBox.setText("Settings has been modified. Please restart the"
                       "application for the entry into force of the settings");
        msgBox.exec();
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
        Config::configuration()->setAppLang(t_lang);
        QMessageBox msgBox;
        msgBox.setText("Settings has been modified. Please restart the"
                       "application for the entry into force of the settings");
        msgBox.exec();
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
        Config::configuration()->setAppLang(t_lang);
        QMessageBox msgBox;
        msgBox.setText("Settings has been modified. Please restart the"
                       "application for the entry into force of the settings");
        msgBox.exec();
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
        Config::configuration()->setAppLang(t_lang);
        QMessageBox msgBox;
        msgBox.setText("Settings has been modified. Please restart the"
                       "application for the entry into force of the settings");
        msgBox.exec();
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
void MainWindow::closeEvent(QCloseEvent *e)
{
    //    myDebug()<< "closeEvent()";
    saveSettings();
    e -> accept();
}
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
void MainWindow::openModule()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open module(test)"), "",
                                                    tr("test module (*.ini)"));
    if (!fileName.isEmpty())
    {
        //        ProjectOpen(fileName);
        //        ProcessModule(fileName, OBVCore::BibleQuoteModule);
    }
}
//------------------------------------------------------------------------------
void MainWindow::processFinish()
{
    myDebug() << "Process finish";
    //    ProjectQModule* test = new ProjectQModule();
    //    test->setChapterValue(5);
    //    test->setModuleName("fasf");
    ProjectQModuleList* list = new ProjectQModuleList();

    //    list->AddModule(test);
    list->refreshList();
    //        myDebug() << list->getCurNumberModule();
    //    myDebug() << list->getModule(0).getModuleName();

    for (int i = 0; i < list->getSize(); i++ )
    {
        //        myDebug() << list->getModule(i).getModuleInfo();
    }
    GUI_LeftPanel->refreshList(list);
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
