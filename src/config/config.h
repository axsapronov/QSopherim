#ifndef __CONFIG__H
#define __CONFIG__H

#include <QString>
#include <QColor>
#include <QTranslator>

#include "projectqmodulelist.h"

//====================== class Config ============================

class Config
{
public:

    Config();
    void loadSettings();
    void saveSettings();
    //variables for global use via  Config::configuration() -> variable()
    QString getAppDir();
    void setAppDir(QString dir);

    void setBibleDir(QString dir);
    void setOtherDir(QString dir);
    void setDictDir(QString dir);
    void setAppLang(QString lang);

    void setListBibles(ProjectQModuleList* newlist);
    void setListDictionaries(ProjectQModuleList* newlist);

    QString getBibleDir();
    QString getDictDir();
    QString getOtherDir();
    QString getAppLang();

    ProjectQModuleList* getListBibles();
    ProjectQModuleList* getListDictionaries();


    // settings font
    int getFontSize();
    QColor getFontColor();
    QString getFontFamily();

    void setFontSize(int  newSize);
    void setFontColor(QColor newColor);
    void setFontFamily(QString newFamily);

    static Config *configuration();

private:
    QString m_appDir;

    QString m_bibleDir;
    QString m_otherDir;
    QString m_dictDir;
    QString m_appLang;

    ProjectQModuleList* m_listBibles;
    ProjectQModuleList* m_listDictinaries;

    // settings font
    QColor m_fontColor;
    int m_fontSize;
    QString m_fontFamily;
};

#endif // __CONFIG__H
