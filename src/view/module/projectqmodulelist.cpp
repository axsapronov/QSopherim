#include "projectqmodulelist.h"
#include "debughelper.h"
#include "filecommon.h"
#include "config.h"

#include <QVector>
#include <QDir>
#include <QStringList>
#include <QDirIterator>

ProjectQModuleList::ProjectQModuleList()
{
    init();
}
//------------------------------------------------------------------------------
void ProjectQModuleList::addModule(ProjectQModule * module)
{
    moduleList.push_back(module);
    cur_int++;
}
//------------------------------------------------------------------------------
int ProjectQModuleList::getCurNumberModule()
{
    return this->cur_int;
}
//------------------------------------------------------------------------------
ProjectQModule* ProjectQModuleList::getNextModule()
{
    return this->moduleList.at(cur_int + 1);
}
//------------------------------------------------------------------------------
ProjectQModule* ProjectQModuleList::getModule(int id)
{
    return moduleList.at(id);
}
//------------------------------------------------------------------------------
void ProjectQModuleList::init()
{
//    moduleList = new QVector<ProjectQModule*>;
    moduleList.clear();
    cur_int = -1;
}
//------------------------------------------------------------------------------
void ProjectQModuleList::refreshList(QString what)
{
    /*
     *P.S. для удобства добавить в settings файл модуля
     *пункт с путем до модуля, относительно curdir
     *пройти по внутренним папкам, и если нашел модуль,
     *то глянуть, есть ли такой уже
     *если нет, то
     *создать его
     *и добавить в список
     */
    QString t_pathToIniFile = QString(Config::configuration()->getAppDir() + what);
    findModules(t_pathToIniFile);
}
//------------------------------------------------------------------------------
void ProjectQModuleList::findModules(QString dir)
{
    if (!dir.isEmpty())
    {
        QStringList files;
        files = recursiveFind(dir);
        files = getModuleFilesList(files);
        for (int i = 0; i < files.size(); i++)
        {

            ProjectQModule* module = new ProjectQModule(getModuleInfo(files.at(i)));
//            myDebug() <<  module.getBookList().size();

            addModule(module);
            //            myDebug() << getModuleInfo(files.at(i));
        }
    }
}
//------------------------------------------------------------------------------
QStringList ProjectQModuleList::getModuleFilesList(QStringList files)
{
    QStringList list;
    for(int i = 0; i < files.size(); i++)
    {
        if(files.at(i).indexOf(".ini") >= 0)
        {
            list << files.at(i);
        }
    }
    return list;
}
//------------------------------------------------------------------------------
int ProjectQModuleList::getSize()
{
    return moduleList.size();
}
//------------------------------------------------------------------------------
ProjectQModule* ProjectQModuleList::getModuleWithName(QString name)
{
    for (int i = 0; moduleList.size(); i++)
    {
        if (name == getModule(i)->getModuleName())
            return getModule(i);
    }
    ProjectQModule *tes = new ProjectQModule();
    return tes;
}
//------------------------------------------------------------------------------
QStringList ProjectQModuleList::getModuleBooks(QString nameOfbook)
{
    QStringList bookList = getModuleWithName(nameOfbook)->getBookList();
    return bookList;
}
//------------------------------------------------------------------------------
void ProjectQModuleList::deleteModule(QString nameModule)
{
    for (int i = 0; i < moduleList.size(); i++)
    {
        if (moduleList.at(i)->getModuleName() == nameModule)
        {
            QString t_path = Config::configuration()->getAppDir() + moduleList.at(i)->getModulePath();
            QFile::remove(t_path);
            t_path.replace("module.ini", "text.xml");
            QFile::remove(QString(t_path).replace("module.ini", "text.xml"));
            t_path.replace("text.xml", "dict.xml");
            QFile::remove(QString(t_path).replace("module.ini", "dict.xml"));
            t_path.remove("dict.xml");
            QDir dir (t_path);

            dir.rmpath(t_path);
            moduleList.remove(i);
        }
    }
    cur_int--;
}
//------------------------------------------------------------------------------
void ProjectQModuleList::hideModule(QString nameModule)
{
    for (int i = 0; i < moduleList.size(); i++)
    {
        if (moduleList.at(i)->getModuleName() == nameModule)
        {
            Config::configuration()->addHiddenModule(nameModule);
        }
    }
//    cur_int--;
}
//------------------------------------------------------------------------------
void ProjectQModuleList::showModule(QString nameModule)
{
    for (int i = 0; i < moduleList.size(); i++)
    {
        if (moduleList.at(i)->getModuleName() == nameModule)
        {
            Config::configuration()->showHiddenModule(nameModule);
        }
    }
//    cur_int++;
}
//------------------------------------------------------------------------------
