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
    void setAppDir(const QString dir);

    /**
     * @brief setBibleDir
     * @param dir
     */
    void setBibleDir(const QString dir);
    void setApocryphaDir(const QString dir);
    void setBookDir(const QString dir);
    void setCommentsDir(const QString dir);
    /**
     * @brief setOtherDir
     * @param dir
     */
    void setOtherDir(const QString dir);
    /**
     * @brief setDictDir
     * @param dir
     */
    void setDictDir(const QString dir);
    /**
     * @brief setStrongDir
     * @param dir
     */
    void setStrongDir(const QString dir);
    /**
     * @brief setAppLang
     * @param lang
     */
    void setAppLang(const QString lang);

    /**
     * @brief setListBibles
     * @param newlist
     */
    void setListBibles(QSopherimModuleList* newlist);
    void setListBook(QSopherimModuleList* newlist);
    void setListApocrypha(QSopherimModuleList* newlist);

    /**
     * @brief setListDictionaries
     * @param newlist
     */
    void setListDictionaries(QSopherimModuleList* newlist);

    /**
     * @brief setListComments
     * @param newlist
     */
    void setListComments(QSopherimModuleList* newlist);

    /**
     * @brief addHiddenModule
     * @param nameModule
     */
    void addHiddenModule(const QString nameModule);
    /**
     * @brief showHiddenModule
     * @param nameModule
     */
    void showHiddenModule(const QString nameModule);

    /**
     * @brief getBibleDir
     * @return
     */
    QString getBibleDir();
    QString getBookDir();
    QString getCommentsDir();
    QString getApocryphaDir();
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
    void setLastChapter(const QString state);
    /**
     * @brief setLastBook
     * @param state
     */
    void setLastBook(const QString state);
    /**
     * @brief setLastModule
     * @param state
     */
    void setLastModule(const QString state);
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
    void setGuiTray(const bool state);
    /**
     * @brief getGuiTray
     * @return
     */
    bool getGuiTray();

    QString getStrongHebrew();
    QString getStrongGreek();

    void setStrongHebrew(const QString strong);
    void setStrongGreek(const QString strong);

    QSopherimModuleList* getListBibles();
    QSopherimModuleList* getListDictionaries();
    QSopherimModuleList* getListComments();
    QSopherimModuleList* getListBook();
    QSopherimModuleList* getListApocrypha();

    QStringList* getListHiddenModules();


    // viewer settings

    QColor getViewerColor();

    void setViewerColor(const QColor newColor);

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
    void setFontSize(const int  newSize);
    /**
     * @brief setFontColor
     * @param newColor
     */
    void setFontColor(const QColor newColor);
    /**
     * @brief setFontFamily
     * @param newFamily
     */
    void setFontFamily(const QString newFamily);

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
    QString m_commentsDir;
    QString m_apocryphaDir;
    QString m_bookDir;

    QString m_strongHebrew;
    QString m_strongGreek;

    QString m_lastChapter;
    QString m_lastBook;
    QString m_lastModule;

    QString m_lastType;

    QSopherimModuleList* m_listBibles;
    QSopherimModuleList* m_listDictinaries;
    QSopherimModuleList* m_listComments;
    QSopherimModuleList* m_listApocrypha;
    QSopherimModuleList* m_listBook;

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
