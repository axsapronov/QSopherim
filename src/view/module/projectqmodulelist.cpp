#include "projectqmodulelist.h"
#include <QVector>

ProjectQModuleList::ProjectQModuleList()
{
    init();
}
//------------------------------------------------------------------------------
void ProjectQModuleList::AddModule(ProjectQModule * module)
{
    moduleList->push_back(*module);
    cur_int++;
}
//------------------------------------------------------------------------------
int ProjectQModuleList::getCurNumberModule()
{
    return this->cur_int;
}
//------------------------------------------------------------------------------
ProjectQModule ProjectQModuleList::getNextModule()
{
    return this->moduleList->at(cur_int + 1);
}
//------------------------------------------------------------------------------
ProjectQModule ProjectQModuleList::getModule(int id)
{
    return moduleList->at(id);
}
//------------------------------------------------------------------------------
void ProjectQModuleList::init()
{
    moduleList = new QVector<ProjectQModule>;
    cur_int = 0;
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
