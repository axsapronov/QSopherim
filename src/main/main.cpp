#include "mainwindow.h"
#include "defines.h"
#include "config.h"
#include "debughelper.h"

#include <QtGui/QApplication>
#include <QtCore/QFSFileEngine>

#include <QTextCodec>
#include <QTranslator>
#include <QLocale>

#include <QDebug>


//------------------------------------------------------------------------------
bool removeDir(const QString &dirName)
{
    bool result = true;
    QDir dir(dirName);

    if(dir.exists(dirName))
    {
        foreach(const QFileInfo & info, dir.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files, QDir::DirsFirst))
        {
            if(info.isDir())
            {
                result = removeDir(info.absoluteFilePath());
            }
            else
            {
                result = QFile::remove(info.absoluteFilePath());
            }
            if(!result)
            {
                return result;
            }
        }
        result = dir.rmdir(dirName);
    }
    return result;
}
//------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //    a.setOrganizationName(GL_AUTHOR);

    a.setApplicationName(GL_PROG_NAME);
    a.setWindowIcon(QIcon(":/icons/images/logo.png"));

    QTextCodec * codec = QTextCodec::codecForName("UTF-8"); // set encoding for prog
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForTr(codec);

    Config *conf = new Config();

#ifdef Q_OS_WIN
    QString t_settings = "settings.ini";
    QString t_homeDataPath = QDir::currentPath();
    QString t_configHomePath = QDir::currentPath();
    QString t_dataHomePath = QDir::currentPath();
#endif
#ifdef Q_OS_LINUX
    QString t_settings = "settings.conf";
    QString t_homeDataPath = QFSFileEngine::homePath() + "/.qsopherim/";

    QString t_configHomePath = QFSFileEngine::homePath() + "/.config" + "/qsopherim/";
    QString t_dataHomePath = QFSFileEngine::homePath() + "/.local/share" + "/qsopherim/";

    QDir dir(t_homeDataPath);
    if(!dir.exists(t_homeDataPath))
        dir.mkpath(t_homeDataPath);

    if(!dir.exists(t_configHomePath))
        dir.mkpath(t_configHomePath);

    if(!dir.exists(t_dataHomePath))
        dir.mkpath(t_dataHomePath);

#endif
    conf->setConfigPath(t_configHomePath);
    conf->setDataPath(t_dataHomePath);
    conf->setAppDir(t_homeDataPath);

    if(!dir.exists(conf->getDataPath() + "strongs/"))
        dir.mkpath(conf->getDataPath() + "strongs/");

    if(!dir.exists(conf->getDataPath() + "plans/"))
        dir.mkpath(conf->getDataPath() + "plans/");

    if(!dir.exists(conf->getDataPath() + "modules/"))
        dir.mkpath(conf->getDataPath() + "modules/");

    conf->setStrongDir(conf->getDataPath() + "strongs/");
    conf->setDictDir(conf->getDataPath() + GL_MODULE_PATH + "dictionary/");
    conf->setAppLogFN(conf->getConfigPath() + "project.log");

    if (QFile::exists(conf->getConfigPath() + t_settings))
    {
        conf -> loadSettings();
    }
    else
        conf -> saveSettings();

    QString lang = conf->getAppLang();

    QTranslator translator;
    if (lang == "Russian") translator.load("QSopherim_ru",":lang/lang");
    if (lang == "Deutch") translator.load("QSopherim_de",":lang/lang");
    if (lang == "Français") translator.load("QSopherim_fr",":lang/lang");
    a.installTranslator(&translator);


    toLog(conf -> AppLogFN(), "-------");
    toLog(conf -> AppLogFN(), "Project started.");

    MainWindow w;
    w.show();

    return a.exec();
    //    return 0;
}
//------------------------------------------------------------------------------
