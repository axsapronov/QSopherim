#include "qsopherimmodulelist.h"
#include "debughelper.h"
#include "filecommon.h"
#include "config.h"

#include <QVector>
#include <QDir>
#include <QStringList>
#include <QDirIterator>

QSopherimModuleList::QSopherimModuleList()
{
    init();
}
//------------------------------------------------------------------------------
QSopherimModuleList::~QSopherimModuleList()
{
    for (int i = 0; i < moduleList.size(); i++)
    {
        delete moduleList.at(i);
    }
}
//------------------------------------------------------------------------------
void QSopherimModuleList::addModule(QSopherimModule * module)
{
    moduleList.push_back(module);
    cur_int++;
}
//------------------------------------------------------------------------------
int QSopherimModuleList::getCurNumberModule()
{
    return this->cur_int;
}
//------------------------------------------------------------------------------
QSopherimModule* QSopherimModuleList::getNextModule()
{
    return this->moduleList.at(cur_int + 1);
}
//------------------------------------------------------------------------------
QSopherimModule* QSopherimModuleList::getModule(int id)
{
    return moduleList.at(id);
}
//------------------------------------------------------------------------------
void QSopherimModuleList::init()
{
//    moduleList = new QVector<QSopherimModule*>;
    moduleList.clear();
    cur_int = -1;
}
//------------------------------------------------------------------------------
void QSopherimModuleList::refreshList(QString what)
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
void QSopherimModuleList::findModules(QString dir)
{
    if (!dir.isEmpty())
    {
        QStringList files;
        files = recursiveFind(dir);
        files = getModuleFilesList(files);
        for (int i = 0; i < files.size(); i++)
        {

            QSopherimModule* module = new QSopherimModule(getModuleInfo(files.at(i)));
//            myDebug() <<  module.getBookList().size();

            addModule(module);
            //            myDebug() << getModuleInfo(files.at(i));
        }
    }
}
//------------------------------------------------------------------------------
QStringList QSopherimModuleList::getModuleFilesList(QStringList files)
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
int QSopherimModuleList::getSize()
{
    return moduleList.size();
}
//------------------------------------------------------------------------------
QSopherimModule* QSopherimModuleList::getModuleWithName(QString name)
{
    for (int i = 0; moduleList.size(); i++)
    {
        if (name == getModule(i)->getModuleName())
            return getModule(i);
    }
    QSopherimModule *tes = new QSopherimModule();
    return tes;
}
//------------------------------------------------------------------------------
QStringList QSopherimModuleList::getModuleBooks(QString nameOfbook)
{
    QStringList bookList = getModuleWithName(nameOfbook)->getBookList();
    return bookList;
}
//------------------------------------------------------------------------------
void QSopherimModuleList::deleteModule(QString nameModule)
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
void QSopherimModuleList::hideModule(QString nameModule)
{
    for (int i = 0; i < moduleList.size(); i++)
    {
        if (moduleList.at(i)->getModuleName() == nameModule)
        {
            Config::configuration()->addHiddenModule(nameModule);
        }
    }
}
//------------------------------------------------------------------------------
void QSopherimModuleList::showModule(QString nameModule)
{
    for (int i = 0; i < moduleList.size(); i++)
    {
        if (moduleList.at(i)->getModuleName() == nameModule)
        {
            Config::configuration()->showHiddenModule(nameModule);
        }
    }
}
//------------------------------------------------------------------------------
void QSopherimModuleList::clearList()
{
    moduleList.clear();
}
//------------------------------------------------------------------------------
