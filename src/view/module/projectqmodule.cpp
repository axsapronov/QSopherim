#include "projectqmodule.h"

ProjectQModule::ProjectQModule()
{

}
//------------------------------------------------------------------------------
int ProjectQModule::getChapterValue()
{
   return this->chapterValue;
}
//------------------------------------------------------------------------------
QString ProjectQModule::getModuleName()
{
    return this->moduleName;
}
//------------------------------------------------------------------------------
QString ProjectQModule::getModuleShortName()
{
    return this->moduleShortName;
}
//------------------------------------------------------------------------------
void ProjectQModule::setChapterValue(int newvalue)
{
    this->chapterValue = newvalue;
}
//------------------------------------------------------------------------------
void ProjectQModule::setModuleName(QString newname)
{
    this->moduleName = newname;
}
//------------------------------------------------------------------------------
void ProjectQModule::setModuleShortName(QString newname)
{
    this->moduleShortName = newname;
}
//------------------------------------------------------------------------------
