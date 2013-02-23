#ifndef Settings_H
#define Settings_H

#include <QDialog>

#include "fontdialog.h"

namespace Ui
{
class Settings;
}


class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();

    /**
      @function
      Init
      */
    void init();
    /**
      @function
      Load settings
      */
    void loadSettings();
    /**
      @function
      Save settings
      */
    void saveSettings();
    /*
      @function
      Return lang of app
      */
    QString getAPPLang();
    /*
      @function
      Set lang of app
      */
    void setAPPLang(QString new_lang);

    void retranslate();

signals:
    void SIGNAL_RetranslateGUI(QString);
    void SIGNAL_ReLoadModules();
    void SIGNAL_ReLoadFontSettings();
    void SIGNAL_UpdateTray();
    void SIGNAL_UpdateDayMode();

private slots:
    void accept();
    /**
       @function
       Browse path to dict modules
       */
    void browseDictDir();
    /**
       @function
       Browse path to bible modules
       */
    void browseBibleDir();
    /**
       @function
       Browse path to other modules
       */
    void browseOtherDir();
    void selectFontColor();

    void fontSettings();

private:
    Ui::Settings *ui;
    QString m_APP_Lang;
    QColor m_fontColor;
    QColor m_viewerColor;

    FontDialog GUI_Font;
    /**
      @function
      Debug function
      */
    void debug();
    /**
      @function
      Create connects
      */
    void createConnect();
    /**
      @function
      Return true if modify settings, false or not
      @return flag
      */
    bool getModifySettings();
    void setParams();
};

#endif // Settings_H
