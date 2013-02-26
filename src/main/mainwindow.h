#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>

namespace Ui {
    class MainWindow;
}

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
QT_END_NAMESPACE


#include "settings.h"
#include "about.h" /// aboutdialog
#include "leftpanel.h" /// leftPanel
#include "leftpanel2.h"
#include "rightpanel.h" /// rightPanel
#include "bottompanel.h" /// bottomPanel
#include "moduleviewer.h"
#include "processmodule.h"
#include "moduledefinition.h"
#include "debughelper.h"
#include "qsopherimmodulelist.h"
#include "finddialog.h"
#include "noteeditor.h"
#include "managermodules.h"
#include "moduleimportdialog.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    /**
      \brief
      @function
      Show find dialog
      */
    void findInModules();
    /**
      \brief
      @functon
      Show application settings dialog
      */
    void showSettings();

    /**
      \brief
      @functon
      Show module manager dialog
      */
    void showModuleManager();

    //tray
    void showHide(QSystemTrayIcon::ActivationReason);

    // language
    /**
      \brief
      @functon
      Select language in ui
      */
    void setLangRu();
    /**
      \brief
      @functon
      Select language in ui
      */
    void setLangFr();
    /**
      \brief
      @functon
      Select language in ui
      */
    void setLangDe();
    /**
      \brief
      @functon
      Select language in ui
      */
    void setLangEn();
    /**
      \brief
      @function
      Open in browser home website
      */
    void aboutOpenSite();
    /**
      \brief
      @function
      Show help
      */
    void showHelp();

    void createNote();

    /**
     * @brief retranslate
     * Retranslate gui
     * @param t_str
     */
    void retranslate(QString t_str);

    /**
     * @brief loadModulesFromFolder
     * @functon
     * Load modules from path and add to list in app
     */
    void loadModulesFromFolder();

    /**
     * @brief loadDictFromFolder
     * @function
     * Load dictionaryes from path and add to list in app
     */
    void loadDictFromFolder();

    void loadCommentsFromFolder();

    /**
     * @brief showHideTray
     * @param state
     */
    void showHideTray();



//    void loadModules();

protected:
    void closeEvent(QCloseEvent *);
//    void mouseMoveEvent(QMouseEvent *);

private:
    Ui::MainWindow *ui;

    //about
    AboutDialog *GUI_About;    // about dialog
    Settings *GUI_Settings;
    RightPanel *GUI_RightPanel;
    LeftPanel *GUI_LeftPanel;
    LeftPanel2 *GUI_LeftPanel2;
    BottomPanel *GUI_BottomPanel;
    ModuleViewer *GUI_ModuleViewer;
    NoteEditor *GUI_NoteEditor;
    ManagerModules *GUI_ManagerModules;
    FindDialog *GUI_FindDialog;
    ModuleImportDialog *GUI_ModuleImportDialog;

    //tray
    QSystemTrayIcon *trIcon;
    QMenu *trayIconMenu;
    QAction *minimizeAction;
    QAction *maximizeAction;
    QAction *restoreAction;
    QAction *quitAction;

    ProcessModule* prModule;

    void convertModules(const QString f_type);

    /**
      @function
      debug function
      */
    void debug();
    /**
      @function
      init function
      */
    void init();
    /**
      @function
      */
    void createConnects();
    /**
      @function
      */
    void createTrayIcon();
    /**
      @function
      */
    void createActions();
    /**
      @function
      */
    void saveSettings();

};


#endif // MAINWINDOW_H
