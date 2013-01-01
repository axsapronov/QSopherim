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
    ~Config();
    void loadSettings();
    void saveSettings();
    //variables for global use via  Config::configuration() -> variable()
    QString getAppDir();
    void setAppDir(QString dir);

    /**
     * @brief setBibleDir
     * @param dir
     */
    void setBibleDir(QString dir);
    /**
     * @brief setOtherDir
     * @param dir
     */
    void setOtherDir(QString dir);
    /**
     * @brief setDictDir
     * @param dir
     */
    void setDictDir(QString dir);
    /**
     * @brief setStrongDir
     * @param dir
     */
    void setStrongDir(QString dir);
    /**
     * @brief setAppLang
     * @param lang
     */
    void setAppLang(QString lang);

    /**
     * @brief setListBibles
     * @param newlist
     */
    void setListBibles(ProjectQModuleList* newlist);

    /**
     * @brief setListDictionaries
     * @param newlist
     */
    void setListDictionaries(ProjectQModuleList* newlist);

    /**
     * @brief addHiddenModule
     * @param nameModule
     */
    void addHiddenModule(QString nameModule);
    /**
     * @brief showHiddenModule
     * @param nameModule
     */
    void showHiddenModule(QString nameModule);

    /**
     * @brief getBibleDir
     * @return
     */
    QString getBibleDir();
    /**
     * @brief getDictDir
     * @return
     */
    QString getDictDir();
    /**
     * @brief getStrongDir
     * @return
     */
    QString getStrongDir();
    /**
     * @brief getOtherDir
     * @return
     */
    QString getOtherDir();
    /**
     * @brief getAppLang
     * @return
     */
    QString getAppLang();

    QString getStrongHebrew();
    QString getStrongGreek();

    void setStrongHebrew(QString strong);
    void setStrongGreek(QString strong);


    ProjectQModuleList* getListBibles();
    ProjectQModuleList* getListDictionaries();
    QStringList* getListHiddenModules();


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
    QString m_strongDir;
    QString m_appLang;

    QString m_strongHebrew;
    QString m_strongGreek;

    ProjectQModuleList* m_listBibles;
    ProjectQModuleList* m_listDictinaries;
    QStringList* m_listHiddenModules;

    // settings font
    QColor m_fontColor;
    int m_fontSize;
    QString m_fontFamily;
};

#endif // __CONFIG__H
