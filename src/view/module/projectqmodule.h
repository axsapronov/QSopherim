#ifndef PROJECTQMODULE_H
#define PROJECTQMODULE_H

#include <QString>
#include <QStringList>


class ProjectQModuleInfo
{
public:
    QString moduleName;
    QString moduleShortName;
    QString modulePath;
    QStringList bookList;
    int bookValue;
};

class ProjectQModule
{
public:
    ProjectQModule();
    ProjectQModule(ProjectQModuleInfo list);

    QString getModuleName();
    void setModuleName(QString);

    QString getModuleShortName();
    void setModuleShortName(QString);

    int getBookValue();
    void setBookValue(int);

    QString getModulePath();
    void setModulePath(QString newpath);

    ProjectQModuleInfo getModuleInfo();

    QStringList getBookList();
    void setBookList(QStringList);
private:
    QString moduleName;
    QString moduleShortName;
    QString modulePath;
    QStringList bookList;
    int bookValue;

    void init();

};

#endif // PROJECTQMODULE_H
