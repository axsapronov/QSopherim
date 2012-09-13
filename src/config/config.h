#ifndef __CONFIG__H
#define __CONFIG__H

#include <QString>
//====================== class Config ============================

class Config
{
public:

    Config();
    void loadSettings();
    void saveSettings();
    //variables for global use via  Config::configuration() -> variable()
    QString getAppDir();
    void setAppDir(QString dir);

    void setBibleDir(QString dir);
    void setOtherDir(QString dir);
    void setDictDir(QString dir);
    void setAppLang(QString lang);

    QString getBibleDir();
    QString getDictDir();
    QString getOtherDir();
    QString getAppLang();

    static Config *configuration();

private:
    QString appDir;

    QString bibleDir;
    QString otherDir;
    QString dictDir;
    QString appLang;
};

#endif // __CONFIG__H
