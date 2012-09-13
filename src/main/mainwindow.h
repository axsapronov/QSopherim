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

class AboutDialog;
class Settings;
class LeftPanel;
class LeftPanel2;
class RightPanel;
class BottomPanel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    /**
      @function
      Show application settings dialog
      */
    void showSettings();

    //tray
    void showHide(QSystemTrayIcon::ActivationReason);

    // language
    /**
      @functon
      Select language in ui
      */
    void setLangRu();
    /**
      @functon
      Select language in ui
      */
    void setLangFr();
    /**
      @functon
      Select language in ui
      */
    void setLangDe();
    /**
      @functon
      Select language in ui
      */
    void setLangEn();
    /**
      @function
      Open in browser home website
      */
    void aboutOpenSite();
    /**
      @function
      Show help
      */
    void showHelp();

protected:
    void closeEvent(QCloseEvent *);
private:
    Ui::MainWindow *ui;

    //about
    AboutDialog *GUI_About;    // about dialog
    Settings *GUI_Settings;
    RightPanel *GUI_RightPanel;
    LeftPanel *GUI_LeftPanel;
    LeftPanel2 *GUI_LeftPanel2;
    BottomPanel *GUI_BottomPanel;

    //tray
    QSystemTrayIcon *trIcon;
    QMenu *trayIconMenu;
    QAction *minimizeAction;
    QAction *maximizeAction;
    QAction *restoreAction;
    QAction *quitAction;

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
