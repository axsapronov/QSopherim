#ifndef PROJECTQMODULELIST_H
#define PROJECTQMODULELIST_H

#include "projectqmodule.h"
class ProjectQModule;
#include <QVector>

class ProjectQModuleList
{

public:
    explicit ProjectQModuleList();
    ProjectQModule getNextModule();
    ProjectQModule getModule(int id);

    void AddModule(ProjectQModule*);
    int getCurNumberModule();

    void refreshList();
    int getSize();
    ProjectQModule getModuleWithName(QString name);
private:
    QVector<ProjectQModule>* moduleList;
    int cur_int;
    void init();
    QStringList recursiveFind(QString directory);
    void findModules(QString dir);
    QStringList getModuleFilesList(QStringList files);
    //
};

#endif // PROJECTQMODULELIST_H