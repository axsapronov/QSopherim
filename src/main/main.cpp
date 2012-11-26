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

    Config *conf = new Config();
    conf -> setAppDir(QDir::currentPath() + "/");
    if (QFile::exists(conf->getAppDir() + "settings.conf"))
    {
        conf -> loadSettings();
    }
    else
        conf -> saveSettings();

    QTextCodec * codec = QTextCodec::codecForName("UTF-8"); // set encoding for prog
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForTr(codec);

    QString lang = conf->getAppLang();

    QTranslator translator;
    if (lang.isEmpty())
        lang = "Russian";
    if (lang == "Russian") translator.load("projectQ_ru",":lang/lang");
    if (lang == "Deutch") translator.load("projectQ_de",":lang/lang");
    if (lang == "Français") translator.load("projectQ_fr",":lang/lang");
    a.installTranslator(&translator);

    MainWindow w;
    w.show();
    return a.exec();
}
