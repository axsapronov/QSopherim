#include "config.h"
#include "debughelper.h"
#include "filecommon.h"
#include "stringcommon.h"

#include "defines.h"

#include <QSettings>
#include <QDir>

static Config *static_configuration = 0;
Config::Config()
{
    if( !static_configuration )
    {
        static_configuration = this;

        m_fontSize = 12;
        m_fontColor = QColor(qRgb(0, 0, 0));
        m_viewerColor = QColor(qRgb(240, 240, 255));
        m_dayMode = true;

        #ifdef Q_OS_WIN
            m_fontFamily = "Tahoma";
            m_fontMenu = "Tahoma";
            m_fontModulesName = "Tahoma";
            m_fontBookName = "Tahoma";
            m_fontStrongsHebrew = "Tahoma";
            m_fontStrongsGreek = "Tahoma";
            m_fontJournal = "Tahoma";
            m_fontNotes = "Tahoma";
            m_fontReadingPlan = "Tahoma";
        #endif

        #ifdef Q_OS_LINUX
            m_fontFamily = "DejaVu Sans";
            m_fontMenu = "DejaVu Sans";
            m_fontModulesName = "DejaVu Sans";
            m_fontBookName = "DejaVu Sans";
            m_fontStrongsHebrew = "DejaVu Sans";
            m_fontStrongsGreek = "DejaVu Sans";
            m_fontJournal = "DejaVu Sans";
            m_fontNotes = "DejaVu Sans";
            m_fontReadingPlan = "DejaVu Sans";
        #endif


        m_appLang = "Russian";
        m_fontBold = false;
        m_fontItalic = false;
        m_fontStrike = false;
        m_fontUnderline = false;
        m_optionChangeTextColor = true;
        m_guiTray = true;

        m_lastChapter = "";
        m_lastBook = "";
        m_lastModule = "";
        m_lastType = "Bible";

        m_listHiddenModules = new QStringList;
        m_journalHistory = new QStringList;
    }
    else
    {
        qWarning( "Multiple configurations not allowed!" );
    }
}
//------------------------------------------------------------------------------
Config::~Config()
{
    delete m_listHiddenModules;
    delete m_journalHistory;
    delete m_listBibles;
    delete m_listDictinaries;
    delete this;
}
//------------------------------------------------------------------------------
QString Config::getAppDir()
{
    return m_appDir;
}
//------------------------------------------------------------------------------
void Config::setAppDir(QString newst)
{
    m_appDir = newst;
}
//------------------------------------------------------------------------------
Config *Config::configuration()
{
    Q_ASSERT( static_configuration );
    return static_configuration;
}
//------------------------------------------------------------------------------
void Config::loadSettings()
{
    #ifdef Q_OS_WIN
        QSettings settings("settings.ini", QSettings::IniFormat);
    #endif
    #ifdef Q_OS_LINUX
        QSettings settings("settings.conf", QSettings::NativeFormat);
    #endif

    m_bibleDir = settings.value(QString("dir/bible")).toString();
    m_dictDir = settings.value(QString("dir/dict")).toString();
    m_otherDir = settings.value(QString("dir/other")).toString();
    m_appLang = settings.value(QString("language/lang")).toString();
    if (m_appLang.isEmpty())
        m_appLang = "Russian";

    QDir dir;
    dir.mkpath(getAppDir() + "bible");
    dir.mkpath(getAppDir() + "dictionary");
    dir.mkpath(getAppDir() + "other");

    // viewer settings
    m_viewerColor = qVariantValue<QColor> (settings.value("viewer/color"));
    m_optionChangeTextColor = settings.value("viewer/colorchangind").toBool();

    // font settings for viewer
    m_fontColor = qVariantValue<QColor> (settings.value("font/color"));
    m_fontSize = settings.value("font/size").toInt();
    m_fontFamily = settings.value("font/family").toString();
    m_fontBold = settings.value("font/bold").toBool();
    m_fontItalic = settings.value("font/italic").toBool();
    m_fontUnderline = settings.value("font/underline").toBool();
    m_fontStrike = settings.value("font/strike").toBool();

    // font settings
    m_fontMenu = settings.value("font/menu").toString();
    m_fontModulesName = settings.value("font/modulesname").toString();
    m_fontBookName = settings.value("font/bookname").toString();
    m_fontStrongsHebrew = settings.value("font/strongshebrew").toString();
    m_fontStrongsGreek = settings.value("font/strongsgreek").toString();
    m_fontJournal = settings.value("font/journal").toString();
    m_fontNotes = settings.value("font/notes").toString();
    m_fontReadingPlan = settings.value("font/readingplan").toString();

    m_strongGreek = settings.value("strongs/greek").toString();
    m_strongHebrew = settings.value("strongs/hebrew").toString();

    // gui settings
    m_guiTray = settings.value("gui/tray").toBool();
    m_dayMode = settings.value("gui/daymode").toBool();

    // last
    m_lastChapter = settings.value("history/chapter").toString();
    m_lastBook = settings.value("history/book").toString();
    m_lastModule = settings.value("history/module").toString();
    m_lastType = settings.value("history/type").toString();

    // strongs
    if (!QFile::exists(m_appDir + "strongs.xml"))
        createEmptyXML(m_appDir + "strongs.xml");


    // hide settings
    m_listHiddenModules->append(settings.value(QString("modules/hidden")).toString().split("_:_"));
    *m_listHiddenModules = removeEmptyQStringFromQStringList(m_listHiddenModules);

    m_journalHistory->append(settings.value(QString("history/journal")).toString().split(GL_SYMBOL_SPLIT_JOURNAL));
    *m_journalHistory = removeEmptyQStringFromQStringList(m_journalHistory);


    //    myDebug() << QString(getAppDir() + bibleDir);

    //        setAppLogLevel( settings.value(QString("LogLevel-Application") ).toInt() );
    //        setPrjLogLevel( settings.value(QString("LogLevel-Project") ).toInt() );
    //        toAppLog(2, "Load application settings");

    //miscellaneous settings

    //        //window and font settings
    //        winGeometry = settings.value(QString("WindowGeometry")).toByteArray();
    //        mainWinState = settings.value(QString("MainWindowState")).toByteArray();
    //        pointFntSize = settings.value(QString("FontSize"), qApp -> font().pointSizeF()).toDouble();

    //        //settings from Settings window
    //        setContentsAdditionalView(	settings.value(QString("ContentsAdditionalView")).toBool() );
    //        setShowSubItemsTitle(		settings.value(QString("ShowSubItemsTitle")).toBool() );
    //        setAutoCollapse(			settings.value(QString("AutoCollapse")).toBool() );
    //    //    backupDir = settings.value(QString("BackupPath") ).toString();
    //    //    backupDir = absolutifyFileName(backupDir, prjDir);		//absolutify path to backup dir
    //    //    externalEditor = settings.value(QString("ExternalEditor") ).toString();
    //    //    externalEditor = absolutifyFileName(externalEditor, prjDir); //absolutify file path to editor
    //    //    externalBrowser = settings.value(QString("ExternalBrowser") ).toString();
    //    //    externalBrowser = absolutifyFileName(externalBrowser, prjDir);	//absolutify file path to browser
    //    //    externalArchiver = settings.value(QString("ExternalArchiver") ).toString();
    //    //    externalArchiver = absolutifyFileName(externalArchiver, prjDir);	//absolutify file path to archiver
    //    //    externalArchiverOptions = settings.value(QString("ExternalArchiverOptions") ).toString();
    //        setItemAutoProperties(settings.value(QString("ItemAutoProperties")).toBool() );
    //        setAutoNumbers(			settings.value(QString("AutoNumbers")).toBool() );

    //        setAcceptDropImages(settings.value(QLatin1String("AcceptDropImages")).toBool() );

    //        //settings from Signature window
    //        setDefaultSignatureID(		settings.value(QString("DefaultSignatureID")).toInt() );

    //        toAppLog(2, "- done");

}
//------------------------------------------------------------------------------
void Config::saveSettings()
{
    //    toAppLog(2, "Save application settings");
#ifdef Q_OS_WIN
    QSettings settings("settings.ini", QSettings::IniFormat);
#endif
#ifdef Q_OS_LINUX
    QSettings settings("settings.conf", QSettings::NativeFormat);
#endif

    settings.setValue(QString("language/lang"), m_appLang);
    settings.setValue(QString("dir/bible"), m_bibleDir);
    settings.setValue(QString("dir/other"), m_otherDir);
    settings.setValue(QString("dir/dict"), m_dictDir);

    // viewer
    settings.setValue(QString("viewer/color"), m_viewerColor);
    settings.setValue(QString("viewer/colorchanging"), m_optionChangeTextColor);

    // font settings for viewer
    settings.setValue(QString("font/color"), m_fontColor);
    settings.setValue(QString("font/size"), m_fontSize);
    settings.setValue(QString("font/family"), m_fontFamily);

    settings.setValue(QString("font/bold"), m_fontBold);
    settings.setValue(QString("font/italic"), m_fontItalic);
    settings.setValue(QString("font/underline"), m_fontUnderline);
    settings.setValue(QString("font/strike"), m_fontStrike);

    // font settings
    settings.setValue(QString("font/menu"), m_fontMenu);
    settings.setValue(QString("font/modulesname"), m_fontModulesName);
    settings.setValue(QString("font/bookname"), m_fontBookName);
    settings.setValue(QString("font/strongshebrew"), m_fontStrongsHebrew);
    settings.setValue(QString("font/strongsgreek"), m_fontStrongsGreek);
    settings.setValue(QString("font/journal"), m_fontJournal);
    settings.setValue(QString("font/notes"), m_fontNotes);
    settings.setValue(QString("font/readingplan"), m_fontReadingPlan);

    // strongs settings
    settings.setValue(QString("strongs/hebrew"), m_strongHebrew);
    settings.setValue(QString("strongs/greek"), m_strongGreek);

    // gui settings
    settings.setValue(QString("gui/tray"), m_guiTray);
    settings.setValue(QString("gui/daymode"), m_dayMode);

    // last module
    settings.setValue(QString("history/module"), m_lastModule);
    settings.setValue(QString("history/book"), m_lastBook);
    settings.setValue(QString("history/chapter"), m_lastChapter);
    settings.setValue(QString("history/type"), m_lastType);

    // hide settings
    QString t_hiddenModules;
    for (int i = 0; i < m_listHiddenModules->size(); i++)
    {
        t_hiddenModules.append(m_listHiddenModules->at(i) + "_:_");
    }
    settings.setValue(QString("modules/hidden"), t_hiddenModules);

    // journal
    QString t_journalHistory;
    for (int i = 0; i < m_journalHistory->size(); i++)
    {
        t_journalHistory.append(m_journalHistory->at(i) + GL_SYMBOL_SPLIT_JOURNAL);
    }
    settings.setValue(QString("history/journal"), t_journalHistory);


    //    //settings from Settings window
    ////    settings.setValue(QString("ExternalEditor"), relatifyFileName(externalEditor, prjDir) );
    ////    settings.setValue(QString("ExternalBrowser"), relatifyFileName(externalBrowser, prjDir) );
    ////    settings.setValue(QString("ExternalArchiver"), relatifyFileName(externalArchiver, prjDir) );
    ////    settings.setValue(QString("ExternalArchiverOptions"), ExternalArchiverOptions());
    ////    settings.setValue(QString("BackupPath"), relatifyFileName(backupDir, prjDir) );
    //    settings.setValue(QString("ContentsAdditionalView"), contentsAdditionalView);
    //    settings.setValue(QString("ShowSubItemsTitle"), showSubItemsTitle);
    //    settings.setValue(QString("AutoCollapse"),autoCollapse);
    //    settings.setValue(QString("LogLevel-Application"),AppLogLevel());
    //    settings.setValue(QString("LogLevel-Project"),PrjLogLevel());
    //    settings.setValue(QString("ItemAutoProperties"),ItemAutoProperties());
    //    settings.setValue(QString("AutoNumbers"),AutoNumbers());


    //    settings.setValue(QLatin1String("AcceptDropImages"),AcceptDropImages());
    //    //settings from Signature window
    //    settings.setValue(QString("DefaultSignatureID"),DefaultSignatureID());

    //    toAppLog(2, "- done");
}//saveSettings()
//------------------------------------------------------------------------------
QString Config::getStrongDir()
{
    return m_strongDir;
}
//------------------------------------------------------------------------------
void Config::setStrongDir(QString dir)
{
    m_strongDir = dir;
}
//------------------------------------------------------------------------------
QString Config::getBibleDir()
{
    return m_bibleDir;
}
//------------------------------------------------------------------------------
void Config::setBibleDir(QString dir)
{
    m_bibleDir = dir;
}
//------------------------------------------------------------------------------
QString Config::getDictDir()
{
    return m_dictDir;
}
//------------------------------------------------------------------------------
void Config::setDictDir(QString dir)
{
    m_dictDir = dir;
}
//------------------------------------------------------------------------------
QString Config::getOtherDir()
{
    return m_otherDir;
}
//------------------------------------------------------------------------------
void Config::setOtherDir(QString dir)
{
    m_otherDir = dir;
}
//------------------------------------------------------------------------------
QString Config::getAppLang()
{
    return m_appLang;
}
//------------------------------------------------------------------------------
void Config::setAppLang(QString lang)
{
    m_appLang = lang;
}
//------------------------------------------------------------------------------
void Config::setFontColor(QColor newColor)
{
    m_fontColor = newColor;
}
//------------------------------------------------------------------------------
void Config::setFontFamily(QString newFamily)
{
    m_fontFamily = newFamily;
}
//------------------------------------------------------------------------------
void Config::setFontSize(int newSize)
{
    m_fontSize = newSize;
}
//------------------------------------------------------------------------------
QString Config::getFontFamily()
{
    return m_fontFamily;
}
//------------------------------------------------------------------------------
QColor Config::getFontColor()
{
    return m_fontColor;
}
//------------------------------------------------------------------------------
int Config::getFontSize()
{
    return m_fontSize;
}
//------------------------------------------------------------------------------
QSopherimModuleList* Config::getListBibles()
{
    return m_listBibles;
}
//------------------------------------------------------------------------------
QSopherimModuleList* Config::getListDictionaries()
{
    return m_listDictinaries;
}
//------------------------------------------------------------------------------
void Config::setListBibles(QSopherimModuleList *newlist)
{
    m_listBibles = newlist;
}
//------------------------------------------------------------------------------
void Config::setListDictionaries(QSopherimModuleList *newlist)
{
    m_listDictinaries = newlist;
}
//------------------------------------------------------------------------------
void Config::addHiddenModule(QString nameModule)
{
    m_listHiddenModules->append(nameModule);
}
//------------------------------------------------------------------------------
void Config::showHiddenModule(QString nameModule)
{
    int i = m_listHiddenModules->size() - 1;
    do
    {
        if (m_listHiddenModules->at(i) == nameModule)
        {
            m_listHiddenModules->removeAt(i);
            i = 0;
        }
    } while (i > 1 );
}
//------------------------------------------------------------------------------
QStringList* Config::getListHiddenModules()
{
    return m_listHiddenModules;
}
//------------------------------------------------------------------------------
QString Config::getStrongHebrew()
{
    return m_strongHebrew;
}
//------------------------------------------------------------------------------
void Config::setStrongHebrew(QString strong)
{
    m_strongHebrew = strong;
}
//------------------------------------------------------------------------------
QString Config::getStrongGreek()
{
    return m_strongGreek;
}
//------------------------------------------------------------------------------
void Config::setStrongGreek(QString strong)
{
    m_strongGreek = strong;
}
//------------------------------------------------------------------------------
void Config::setFontBold(bool state)
{
    m_fontBold = state;
}
//------------------------------------------------------------------------------
void Config::setFontItalic(bool state)
{
    m_fontItalic = state;
}
//------------------------------------------------------------------------------
void Config::setFontStrike(bool state)
{
    m_fontStrike = state;
}
//------------------------------------------------------------------------------
void Config::setFontUnderline(bool state)
{
    m_fontUnderline = state;
}
//------------------------------------------------------------------------------
bool Config::getFontBold()
{
    return m_fontBold;
}
//------------------------------------------------------------------------------
bool Config::getFontUnderline()
{
    return m_fontUnderline;
}
//------------------------------------------------------------------------------
bool Config::getFontItalic()
{
    return m_fontItalic;
}
//------------------------------------------------------------------------------
bool Config::getFontStrike()
{
    return m_fontStrike;
}
//------------------------------------------------------------------------------
QColor Config::getViewerColor()
{
    return m_viewerColor;
}
//------------------------------------------------------------------------------
void Config::setViewerColor(QColor newColor)
{
    m_viewerColor = newColor;
}
//------------------------------------------------------------------------------
void Config::setOptionChangeTextColor(bool state)
{
    m_optionChangeTextColor = state;
}
//------------------------------------------------------------------------------
bool Config::getOptionChangeTextColor()
{
    return m_optionChangeTextColor;
}
//------------------------------------------------------------------------------
bool Config::getGuiTray()
{
    return m_guiTray;
}
//------------------------------------------------------------------------------
void Config::setGuiTray(bool state)
{
    m_guiTray = state;
}
//------------------------------------------------------------------------------
void Config::setLastChapter(QString state)
{
    m_lastChapter = state;
}
//------------------------------------------------------------------------------
void Config::setLastBook(QString state)
{
    m_lastBook = state;
}
//------------------------------------------------------------------------------
void Config::setLastModule(QString state)
{
    m_lastModule = state;
}
//------------------------------------------------------------------------------
QString Config::getLastChapter()
{
    return m_lastChapter;
}
//------------------------------------------------------------------------------
QString Config::getLastBook()
{
    return m_lastBook;
}
//------------------------------------------------------------------------------
QString Config::getLastModule()
{
    return m_lastModule;
}
//------------------------------------------------------------------------------
QString Config::getLastType()
{
    return m_lastType;
}
//------------------------------------------------------------------------------
void Config::setLastType(const QString state)
{
    m_lastType = state;
}
//------------------------------------------------------------------------------
void Config::setJournalHistory(const QStringList* list)
{
    *m_journalHistory = *list;
}
//------------------------------------------------------------------------------
QStringList* Config::getJournalHistory()
{
    return m_journalHistory;
}
//------------------------------------------------------------------------------
void Config::setFontMenu(QString newFamily)
{
    m_fontMenu = newFamily;
}
//------------------------------------------------------------------------------
QString Config::getFontMenu()
{
    return m_fontMenu;
}
//------------------------------------------------------------------------------
void Config::setFontModulesName(QString newFamily)
{
    m_fontModulesName = newFamily;
}
//------------------------------------------------------------------------------
QString Config::getFontModulesName()
{
    return m_fontModulesName;
}
//------------------------------------------------------------------------------
void Config::setFontBookName(QString newFamily)
{
    m_fontBookName = newFamily;
}
//------------------------------------------------------------------------------
QString Config::getFontBookName()
{
    return m_fontBookName;
}
//------------------------------------------------------------------------------
void Config::setFontStrongsHebrew(QString newFamily)
{
    m_fontStrongsHebrew = newFamily;
}
//------------------------------------------------------------------------------
QString Config::getFontStrongsHebrew()
{
    return m_fontStrongsHebrew;
}
//------------------------------------------------------------------------------
void Config::setFontStrongsGreek(QString newFamily)
{
    m_fontStrongsGreek = newFamily;
}
//------------------------------------------------------------------------------
QString Config::getFontStrongsGreek()
{
    return m_fontStrongsGreek;
}
//------------------------------------------------------------------------------
void Config::setFontJournal(QString newFamily)
{
    m_fontJournal = newFamily;
}
//------------------------------------------------------------------------------
QString Config::getFontJournal()
{
    return m_fontJournal;
}
//------------------------------------------------------------------------------
void Config::setFontNotes(QString newFamily)
{
    m_fontNotes = newFamily;
}
//------------------------------------------------------------------------------
QString Config::getFontNotes()
{
    return m_fontNotes;
}
//------------------------------------------------------------------------------
void Config::setFontReadingPlan(QString newFamily)
{
    m_fontReadingPlan = newFamily;
}
//------------------------------------------------------------------------------
QString Config::getFontReadingPlan()
{
    return m_fontReadingPlan;
}
//------------------------------------------------------------------------------
void Config::setDayMode(bool state)
{
    m_dayMode = state;
}
//------------------------------------------------------------------------------
bool Config::getDayMode()
{
    return m_dayMode;
}
//------------------------------------------------------------------------------
