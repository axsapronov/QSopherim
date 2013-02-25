#ifndef __CONFIG__H
#define __CONFIG__H

#include <QString>
#include <QColor>
#include <QTranslator>

#include <QFont>
#include <QMap>

#include "qsopherimmodulelist.h"

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
    void setListBibles(QSopherimModuleList* newlist);

    /**
     * @brief setListDictionaries
     * @param newlist
     */
    void setListDictionaries(QSopherimModuleList* newlist);

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

    void setGUIMapFont(const QMap<QString, QFont> f_map);
    void setGUIMapFontName(const QString, const QFont);
    QMap<QString, QFont> getGUIMapFont();

    // history
    /**
     * @brief getJournalHistory
     * @return
     */
    QStringList *getJournalHistory();
    /**
     * @brief setJournalHistory
     * @param state
     */
    void setJournalHistory(const QStringList *state);

    // last chapter
    /**
     * @brief setLastType
     * @param state
     */
    void setLastType(const QString state);

    /**
     * @brief getLastType
     * @return
     */
    QString getLastType();

    /**
     * @brief setLastChapter
     * @param state
     */
    void setLastChapter(QString state);
    /**
     * @brief setLastBook
     * @param state
     */
    void setLastBook(QString state);
    /**
     * @brief setLastModule
     * @param state
     */
    void setLastModule(QString state);
    /**
     * @brief getLastChapter
     * @return
     */
    QString getLastChapter();
    /**
     * @brief getLastBook
     * @return
     */
    QString getLastBook();
    /**
     * @brief getLastModule
     * @return
     */
    QString getLastModule();
    // gui

    /**
     * @brief setGuiTray
     * @param state
     */
    void setGuiTray(bool state);
    /**
     * @brief getGuiTray
     * @return
     */
    bool getGuiTray();

    QString getStrongHebrew();
    QString getStrongGreek();

    void setStrongHebrew(QString strong);
    void setStrongGreek(QString strong);


    QSopherimModuleList* getListBibles();
    QSopherimModuleList* getListDictionaries();
    QStringList* getListHiddenModules();


    // viewer settings

    QColor getViewerColor();

    void setViewerColor(QColor newColor);

    // settings font for viewer

    /**
     * @brief getFontSize
     * @return
     */
    int getFontSize();
    /**
     * @brief getFontColor
     * @return
     */
    QColor getFontColor();
    /**
     * @brief getFontFamily
     * @return
     */
    QString getFontFamily();

    /**
     * @brief getFontBold
     * @return
     */
    bool getFontBold();
    /**
     * @brief getFontStrike
     * @return
     */
    bool getFontStrike();
    /**
     * @brief getFontUnderline
     * @return
     */
    bool getFontUnderline();
    /**
     * @brief getFontItalic
     * @return
     */
    bool getFontItalic();

    /**
     * @brief getOptionChangeTextColor
     * @return
     */
    bool getOptionChangeTextColor();

    /**
     * @brief setFontSize
     * @param newSize
     */
    void setFontSize(int  newSize);
    /**
     * @brief setFontColor
     * @param newColor
     */
    void setFontColor(QColor newColor);
    /**
     * @brief setFontFamily
     * @param newFamily
     */
    void setFontFamily(QString newFamily);

    /**
     * @brief setFontBold
     * @param state
     */
    void setFontBold(const bool state);
    /**
     * @brief setFontStrike
     * @param state
     */
    void setFontStrike(const bool state);
    /**
     * @brief setFontUnderline
     * @param state
     */
    void setFontUnderline(const bool state);
    /**
     * @brief setFontItalic
     * @param state
     */
    void setFontItalic(const bool state);

    /**
     * @brief setOptionChangeTextColor
     * @param state
     */
    void setOptionChangeTextColor(const bool state);

    bool getDayMode();
    void setDayMode(const bool state);

    bool getOptionAutoChapter();
    void setOptionAutoChapter(const bool state);

    static Config *configuration();

    bool isExistLastChapter();

private:
    QString m_appDir;

    QString m_bibleDir;
    QString m_otherDir;
    QString m_dictDir;
    QString m_strongDir;
    QString m_appLang;

    QString m_strongHebrew;
    QString m_strongGreek;

    QString m_lastChapter;
    QString m_lastBook;
    QString m_lastModule;

    QString m_lastType;

    QSopherimModuleList* m_listBibles;
    QSopherimModuleList* m_listDictinaries;
    QStringList* m_listHiddenModules;
    QStringList* m_journalHistory;

    // viewer settings

    QColor m_viewerColor;

    // settings font

    QColor m_fontColor;
    int m_fontSize;
    QString m_fontFamily;

    // fonts

    bool m_fontBold;
    bool m_fontItalic;
    bool m_fontUnderline;
    bool m_fontStrike;

    QMap<QString, QFont> m_GUIMapFont;
    // gui
    bool m_guiTray;

    // mode
    bool m_dayMode;
    bool m_optionAutoChapter;
    bool m_optionChangeTextColor;

};

#endif // __CONFIG__H
