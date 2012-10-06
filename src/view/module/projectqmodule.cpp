#include "projectqmodule.h"
#include "debughelper.h"

ProjectQModule::ProjectQModule()
{
    init();
}
//------------------------------------------------------------------------------
ProjectQModule::ProjectQModule(ProjectQModuleInfo list)
{
    init();
//    moduleName = list.at(0);
//    moduleShortName = list.at(1);
//    chapterValue = list.at(2).toInt();
//    modulePath = list.at(3);
    moduleName = list.moduleName;
    moduleShortName  = list.moduleShortName;
    bookValue = list.bookValue;
    modulePath = list.modulePath;
    bookList = list.bookList;
//    myDebug() << getBookList().size();
//    myDebug() << this;
}
//------------------------------------------------------------------------------
int ProjectQModule::getBookValue()
{
   return this->bookValue;
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
void ProjectQModule::setBookValue(int newvalue)
{
    this->bookValue = newvalue;
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
    bookValue = 0;
    moduleName = "";
    moduleShortName = "";
    modulePath = "";
    bookList.clear();
}
//------------------------------------------------------------------------------
ProjectQModuleInfo ProjectQModule::getModuleInfo()
{
    ProjectQModuleInfo list;
    list.moduleName = moduleName;
    list.moduleShortName = moduleShortName;
    list.bookValue = bookValue;
    list.modulePath = modulePath;
    list.bookList = bookList;
//    myDebug() << "fasf" <<  this;

//    list << moduleName
//         << moduleShortName
//         << QString::number(chapterValue)
//         << modulePath;
//    list << append(moduleName).append(moduleShortName).append(chapterValue);

    return list;
}
//------------------------------------------------------------------------------
void ProjectQModule::setModulePath(QString newPath)
{
    modulePath = newPath;
}
//------------------------------------------------------------------------------
QString ProjectQModule::getModulePath()
{
    return modulePath;
}
//------------------------------------------------------------------------------
QStringList ProjectQModule::getBookList()
{
//    myDebug() << bookList.size();
    myDebug() << "fasf" << this;
    return bookList;
}
//------------------------------------------------------------------------------
void ProjectQModule::setBookList(QStringList newlist)
{
    bookList = newlist;
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
