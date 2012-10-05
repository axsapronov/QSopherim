#ifndef PROJECTQMODULE_H
#define PROJECTQMODULE_H

#include <QString>

class ProjectQModule
{
public:
    ProjectQModule();

    QString getModuleName();
    void setModuleName(QString);

    QString getModuleShortName();
    void setModuleShortName(QString);

    int getChapterValue();
    void setChapterValue(int);
private:
    QString moduleName;
    QString moduleShortName;
    int chapterValue;

};

#endif // PROJECTQMODULE_H
