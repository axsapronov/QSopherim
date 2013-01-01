#include "config.h"
#include "debughelper.h"
#include "filecommon.h"
#include "stringcommon.h"

#include <QSettings>
#include <QDir>


static Config *static_configuration = 0;
Config::Config()
{
    if( !static_configuration )
    {
        static_configuration = this;
        m_fontSize = 12;
        m_fontColor = QColor(qRgb(0,0,0));
        m_fontFamily = "DejaVu Sans";
        m_appLang = "Russian";

        m_listHiddenModules = new QStringList;
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
    QSettings settings("settings.conf", QSettings::NativeFormat);

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

    //    fontColor = settings.value("font/color");
    m_fontSize = settings.value("font/size").toInt();
    m_fontFamily = settings.value("font/family").toString();

    m_strongGreek = settings.value("strongs/greek").toString();
    m_strongHebrew = settings.value("strongs/hebrew").toString();

    if (!QFile::exists(m_appDir + "strongs.xml"))
        createEmptyXML(m_appDir + "strongs.xml");


    // hide settings
    m_listHiddenModules->append(settings.value(QString("modules/hidden")).toString().split("_:_"));
    *m_listHiddenModules = removeEmptyQStringFromQStringList(m_listHiddenModules);
    //    myDebug() << m_listHiddenModules->size() << *m_listHiddenModules;


    //    myDebug() << QString(getAppDir() + bibleDir);

    //        setAppLogLevel( settings.value(QString("LogLevel-Application") ).toInt() );
    //        setPrjLogLevel( settings.value(QString("LogLevel-Project") ).toInt() );
    //        toAppLog(2, "Load application settings");

    //miscellaneous settings
    //        lang = settings.value(QString("Language") ).toString();
    //        src = settings.value(QString("Source") ).toStringList();
    //        QStringList::iterator it = src.begin();
    //        for (; it != src.end(); ++it) {
    //            *it = urlifyFileName( absolutifyFileName(*it, prjDir) );
    //        }
    //        sideBar = settings.value(QString("SideBarPage") ).toInt();
    //        rebuildDocs = settings.value(QString("RebuildDocDB"), true ).toBool();
    //        profileFNs = settings.value(QString("Projects") ).toStringList();
    //        profileFNs = absolutifyFileList(profileFNs, prjDir);	//we will load this list to widget in LeftPanel::initialize()
    //        curProject = settings.value(QString("ActiveProject") ).toString();
    //        curProject = absolutifyFileName(curProject, prjDir);	 //absolutify project file path
    //        setContentsSortOrder(settings.value(QString("ContentsSortOrder") ).toString());

    //        //window and font settings
    //        winGeometry = settings.value(QString("WindowGeometry")).toByteArray();
    //        mainWinState = settings.value(QString("MainWindowState")).toByteArray();
    //        pointFntSize = settings.value(QString("FontSize"), qApp -> font().pointSizeF()).toDouble();
    //        m_fontSettings.windowFont = qVariantValue<QFont>(settings.value(QString("WindowFont"), qApp -> font()));
    //        m_fontSettings.browserFont = qVariantValue<QFont>(settings.value(QString("BrowserFont"), qApp -> font()));
    //        m_fontSettings.useWindowFont = settings.value(QString("UseWindowFont"), false).toBool();
    //        m_fontSettings.useBrowserFont = settings.value(QString("UseBrowserFont"), false).toBool();
    //        m_fontSettings.windowWritingSystem = static_cast<QFontDatabase::WritingSystem>(
    //                    settings.value(QString("WindowWritingSystem"), QFontDatabase::Latin).toInt());
    //        m_fontSettings.browserWritingSystem = static_cast<QFontDatabase::WritingSystem>(
    //                    settings.value(QString("BrowserWritingSystem"), QFontDatabase::Latin).toInt());
    //        m_fontSettings.browserFont.setPointSizeF(pointFntSize);

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
    QSettings settings("settings.conf", QSettings::NativeFormat);
    settings.setValue(QString("language/lang"), m_appLang);
    settings.setValue(QString("dir/bible"), m_bibleDir);
    settings.setValue(QString("dir/other"), m_otherDir);
    settings.setValue(QString("dir/dict"), m_dictDir);

    // font settings
    //    settings.setValue(QString("font/color"), fontColor);
    settings.setValue(QString("font/size"), m_fontSize);
    settings.setValue(QString("font/family"), m_fontFamily);

    // strongs settings
    settings.setValue(QString("strongs/hebrew"), m_strongHebrew);
    settings.setValue(QString("strongs/greek"), m_strongGreek);

    // hide settings
    QString t_hiddenModules;
    for (int i = 0; i < m_listHiddenModules->size(); i++)
    {
        t_hiddenModules.append(m_listHiddenModules->at(i) + "_:_");
    }
    settings.setValue(QString("modules/hidden"), t_hiddenModules);

    //    //miscellaneous settings
    //    settings.setValue(QString("Language"), lang);
    //    settings.setValue(QString("Projects"), relatifyFileList(profileFNs, prjDir) );
    //    settings.setValue(QString("ActiveProject"), curProject /*relatifyFileName(curProject, prjDir) */);
    //    settings.setValue(QString("Source"),src );	 //paths relatified in MainWindow::saveSettings()
    //    settings.setValue(QString("SideBarPage"), sideBarPage() );
    //    settings.setValue(QString("RebuildDocDB"), rebuildDocs );
    //    settings.setValue(QString("ContentsSortOrder"), contentsSortOrder );

    //    //window and font settings
    //    settings.setValue(QString("WindowGeometry"), winGeometry);
    //    settings.setValue(QString("MainWindowState"), mainWinState );
    //    settings.setValue(QString("FontSize"), pointFntSize);
    //    settings.setValue(QString("WindowFont"), m_fontSettings.windowFont);
    //    settings.setValue(QString("BrowserFont"), m_fontSettings.browserFont);
    //    settings.setValue(QString("UseWindowFont"), m_fontSettings.useWindowFont);
    //    settings.setValue(QString("UseBrowserFont"), m_fontSettings.useBrowserFont);
    //    settings.setValue(QString("WindowWritingSystem"), m_fontSettings.windowWritingSystem);
    //    settings.setValue(QString("BrowserWritingSystem"), m_fontSettings.browserWritingSystem);

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
ProjectQModuleList* Config::getListBibles()
{
    return m_listBibles;
}
//------------------------------------------------------------------------------
ProjectQModuleList* Config::getListDictionaries()
{
    return m_listDictinaries;
}
//------------------------------------------------------------------------------
void Config::setListBibles(ProjectQModuleList *newlist)
{
    m_listBibles = newlist;
}
//------------------------------------------------------------------------------
void Config::setListDictionaries(ProjectQModuleList *newlist)
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
    m_strongGreek= strong;
}
//------------------------------------------------------------------------------
