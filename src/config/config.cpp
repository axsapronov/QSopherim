#include "config.h"


#include <QSettings>
#include <QtDebug>

static Config *static_configuration = 0;
Config::Config()
{
    if( !static_configuration ) {
        static_configuration = this;
    } else {
        qWarning( "Multiple configurations not allowed!" );
    }
}
//------------------------------------------------------------------------------
QString Config::getAppDir()
{
    return appDir;
}
//------------------------------------------------------------------------------
void Config::setAppDir(QString newst)
{
    appDir = newst;
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

    bibleDir = settings.value(QString("dir/bible")).toString();
    dictDir = settings.value(QString("dir/dict")).toString();
    otherDir = settings.value(QString("dir/other")).toString();
    appLang = settings.value("language/lang").toString();
    if (appLang.isEmpty())
        appLang = "Russian";

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
    settings.setValue(QString("language/lang"), appLang);
    settings.setValue(QString("dir/bible"), bibleDir);
    settings.setValue(QString("dir/other"), otherDir);
    settings.setValue(QString("dir/dict"), dictDir);

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
QString Config::getBibleDir()
{
    return bibleDir;
}
//------------------------------------------------------------------------------
void Config::setBibleDir(QString dir)
{
    bibleDir = dir;
}
//------------------------------------------------------------------------------
QString Config::getDictDir()
{
    return dictDir;
}
//------------------------------------------------------------------------------
void Config::setDictDir(QString dir)
{
    dictDir = dir;
}
//------------------------------------------------------------------------------
QString Config::getOtherDir()
{
    return otherDir;
}
//------------------------------------------------------------------------------
void Config::setOtherDir(QString dir)
{
    otherDir = dir;
}
//------------------------------------------------------------------------------
QString Config::getAppLang()
{
    return appLang;
}
//------------------------------------------------------------------------------
void Config::setAppLang(QString lang)
{
    appLang = lang;
}
//------------------------------------------------------------------------------

