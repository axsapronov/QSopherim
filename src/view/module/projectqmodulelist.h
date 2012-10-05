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
private:
    QVector<ProjectQModule>* moduleList;
    int cur_int;

    void init();

    //
};

#endif // PROJECTQMODULELIST_H
