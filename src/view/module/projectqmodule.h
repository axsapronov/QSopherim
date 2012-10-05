#ifndef PROJECTQMODULE_H
#define PROJECTQMODULE_H

#include <QString>
#include <QStringList>

class ProjectQModule
{
public:
    ProjectQModule();
    ProjectQModule(QStringList list);

    QString getModuleName();
    void setModuleName(QString);

    QString getModuleShortName();
    void setModuleShortName(QString);

    int getChapterValue();
    void setChapterValue(int);

    QStringList getModuleInfo();
private:
    QString moduleName;
    QString moduleShortName;
    int chapterValue;

    void init();

};

#endif // PROJECTQMODULE_H
