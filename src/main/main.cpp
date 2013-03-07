#include "mainwindow.h"
#include "defines.h"
#include "config.h"


#include <QtGui/QApplication>

#include <QTextCodec>
#include <QTranslator>
#include <QLocale>

#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    a.setOrganizationName(GL_AUTHOR);
    a.setApplicationName(GL_PROG_NAME);

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
