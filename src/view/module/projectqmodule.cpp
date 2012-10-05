#include "projectqmodule.h"


ProjectQModule::ProjectQModule()
{
    init();
}
//------------------------------------------------------------------------------
ProjectQModule::ProjectQModule(QStringList list)
{
    init();
    moduleName = list.at(0);
    moduleShortName = list.at(1);
    chapterValue = list.at(2).toInt();
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
void ProjectQModule::init()
{
    chapterValue = 0;
    moduleName = "";
    moduleShortName = "";
}
//------------------------------------------------------------------------------
QStringList ProjectQModule::getModuleInfo()
{
    QStringList list;
    list << moduleName << moduleShortName << QString::number(chapterValue);
//    list << append(moduleName).append(moduleShortName).append(chapterValue);

    return list;
}
//------------------------------------------------------------------------------
