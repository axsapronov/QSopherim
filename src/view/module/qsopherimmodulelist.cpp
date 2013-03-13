#include "qsopherimmodulelist.h"
#include "debughelper.h"
#include "filecommon.h"
#include "config.h"
#include "defines.h"

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
    for (int i = 0; i < m_moduleList.size(); i++)
    {
        delete m_moduleList.at(i);
    }
}
//------------------------------------------------------------------------------
void QSopherimModuleList::addModule(QSopherimModule * module)
{
    m_moduleList.push_back(module);
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
    return this->m_moduleList.at(cur_int + 1);
}
//------------------------------------------------------------------------------
QSopherimModule* QSopherimModuleList::getModule(int id)
{
    return m_moduleList.at(id);
}
//------------------------------------------------------------------------------
void QSopherimModuleList::init()
{
    //    m_moduleList = new QVector<QSopherimModule*>;
    m_moduleList.clear();
    cur_int = -1;
}
//------------------------------------------------------------------------------
void QSopherimModuleList::refreshList(const QString what)
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

    QString t_pathToIniFile = Config::configuration()->getPathType(what);
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
            addModule(new QSopherimModule(getModuleInfo(files.at(i))));
        }
    }
}
//------------------------------------------------------------------------------
QStringList QSopherimModuleList::getModuleFilesList(QStringList files)
{
    QStringList list;
    for(int i = 0; i < files.size(); i++)
    {
        if(files.at(i).indexOf(GL_FORMAT_MODULE) >= 0)
        {
            list << files.at(i);
        }
    }
    return list;
}
//------------------------------------------------------------------------------
int QSopherimModuleList::getSize()
{
    return m_moduleList.size();
}
//------------------------------------------------------------------------------
QSopherimModule* QSopherimModuleList::getModuleWithName(const QString name)
{
    if (!name.isEmpty())
    {
        for (int i = 0; i < m_moduleList.size(); i++)
        {
            if (name == getModule(i)->getModuleName())
                return getModule(i);
        }
    }
    QSopherimModule *tes = new QSopherimModule();
    return tes;

}
//------------------------------------------------------------------------------
QStringList QSopherimModuleList::getModuleBooks(const QString nameOfModule)
{
    QStringList bookList = getModuleWithName(nameOfModule)->getBookList();
    return bookList;
}
//------------------------------------------------------------------------------
void QSopherimModuleList::deleteModule(const QString nameModule)
{
    for (int i = 0; i < m_moduleList.size(); i++)
    {
        if (m_moduleList.at(i)->getModuleName() == nameModule)
        {
            QString t_path = Config::configuration()->getDataPath() + GL_MODULE_PATH + m_moduleList.at(i)->getModulePath();
            QFile::remove(t_path);
            t_path.replace("module" + GL_FORMAT_MODULE, "text" + GL_FORMAT_TEXT);
            QFile::remove(QString(t_path).replace("module" + GL_FORMAT_MODULE, "text" + GL_FORMAT_TEXT));
            t_path.replace("text" + GL_FORMAT_TEXT, "dict" + GL_FORMAT_TEXT);
            QFile::remove(QString(t_path).replace("module" + GL_FORMAT_MODULE, "dict" + GL_FORMAT_TEXT));
            t_path.remove("dict" + GL_FORMAT_TEXT);
            QDir dir (t_path);

            dir.rmpath(t_path);
            m_moduleList.remove(i);
        }
    }
    cur_int--;
}
//------------------------------------------------------------------------------
void QSopherimModuleList::hideModule(const QString nameModule)
{
    for (int i = 0; i < m_moduleList.size(); i++)
    {
        if (m_moduleList.at(i)->getModuleName() == nameModule)
        {
            Config::configuration()->addHiddenModule(nameModule);
        }
    }
}
//------------------------------------------------------------------------------
void QSopherimModuleList::showModule(const QString nameModule)
{
    for (int i = 0; i < m_moduleList.size(); i++)
    {
        if (m_moduleList.at(i)->getModuleName() == nameModule)
        {
            Config::configuration()->showHiddenModule(nameModule);
        }
    }
}
//------------------------------------------------------------------------------
void QSopherimModuleList::clearList()
{
    m_moduleList.clear();
}
//------------------------------------------------------------------------------
bool QSopherimModuleList::isExist(const QString nameModule)
{
    if (this->m_moduleList.size())
    {
        for (int i = 0; i < this->m_moduleList.size(); i++)
        {
            if (nameModule == getModule(i)->getModuleName())
                return true;
        }
    }
    return false;
}
//------------------------------------------------------------------------------
