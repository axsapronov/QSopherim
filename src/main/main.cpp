#include "mainwindow.h"
#include "defines.h"
#include "config.h"
#include "debughelper.h"
#include "anyoption.h"

#include <QtGui/QApplication>

#include <QTextCodec>
#include <QTranslator>
#include <QLocale>

#include <QDebug>


//------------------------------------------------------------------------------
bool removeDir(const QString &dirName)
{
    bool result = true;
    QDir dir(dirName);

    if(dir.exists(dirName)) {
        foreach(const QFileInfo & info, dir.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files, QDir::DirsFirst)) {
            if(info.isDir()) {
                result = removeDir(info.absoluteFilePath());
            } else {
                result = QFile::remove(info.absoluteFilePath());
            }
            if(!result) {
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
    AnyOption *opt = new AnyOption();
    const QString s =  GL_PROG_NAME + GL_PROG_VERSION_STR;
    opt->addUsage(s.toStdString().c_str());
    opt->addUsage("Usage: ");
    opt->addUsage("");
    opt->addUsage(" -h  --help                 Prints this help ");
    opt->addUsage(" --configPath 	        Path to config files ");
    opt->addUsage("");
    opt->setFlag("help", 'h');
    opt->setOption("configPath");
    opt->processCommandArgs(argc, argv);
    if(opt->getValue("help") != NULL) {
        opt->printUsage();
        return 0;
    }
    a.setApplicationName(GL_PROG_NAME);
    a.setWindowIcon(QIcon(":/icons/images/logo.png"));

    QTextCodec * codec = QTextCodec::codecForName("UTF-8"); // set encoding for prog
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForTr(codec);

    Config *conf = new Config();
    conf->setAppDir(QDir::currentPath() + "/");
    conf->setStrongDir(QDir::currentPath() + "/strongs/");
    conf->setDictDir(QDir::currentPath() + "/" + GL_MODULE_PATH + "dictionary/");
    conf->setAppLogFN(conf->getAppDir() + "project.log");

#ifdef Q_OS_WIN
    QString t_settings = "settings.ini";
#endif
#ifdef Q_OS_LINUX
    QString t_settings = "settings.conf";
#endif

    if (QFile::exists(conf->getAppDir() + t_settings))
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
