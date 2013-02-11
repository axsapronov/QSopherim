#include "qsopherimmodule.h"
#include "debughelper.h"

QSopherimModule::QSopherimModule()
{
    init();
}
//------------------------------------------------------------------------------
QSopherimModule::QSopherimModule(QSopherimModuleInfo list)
{
    init();
//    moduleName = list.at(0);
//    moduleShortName = list.at(1);
//    chapterValue = list.at(2).toInt();
//    modulePath = list.at(3);
    m_moduleName = list.moduleName;
    m_moduleShortName  = list.moduleShortName;
    m_bookValue = list.bookValue;
    m_modulePath = list.modulePath;
    m_bookList = list.bookList;
    m_numberOfChaptersInBook = list.numberOfChaptersInBook;
    m_moduleType = list.moduleType;
//    myDebug() << getBookList().size();
//    myDebug() << this;
}
//------------------------------------------------------------------------------
int QSopherimModule::getBookValue()
{
   return m_bookValue;
}
//------------------------------------------------------------------------------
QString QSopherimModule::getModuleName()
{
    return m_moduleName;
}
//------------------------------------------------------------------------------
QString QSopherimModule::getModuleShortName()
{
    return m_moduleShortName;
}
//------------------------------------------------------------------------------
void QSopherimModule::setBookValue(int newvalue)
{
    m_bookValue = newvalue;
}
//------------------------------------------------------------------------------
void QSopherimModule::setModuleName(QString newname)
{
    m_moduleName = newname;
}
//------------------------------------------------------------------------------
void QSopherimModule::setModuleShortName(QString newname)
{
    m_moduleShortName = newname;
}
//------------------------------------------------------------------------------
void QSopherimModule::init()
{
    m_bookValue = 0;
    m_moduleName = "";
    m_moduleShortName = "";
    m_modulePath = "";
    m_bookList.clear();
    m_numberOfChaptersInBook.clear();
    m_moduleType = "";
}
//------------------------------------------------------------------------------
QSopherimModuleInfo QSopherimModule::getModuleInfo()
{
    QSopherimModuleInfo list;
    list.moduleName = m_moduleName;
    list.moduleShortName = m_moduleShortName;
    list.bookValue = m_bookValue;
    list.modulePath = m_modulePath;
    list.bookList = m_bookList;
    list.numberOfChaptersInBook = m_numberOfChaptersInBook;
    list.moduleType = m_moduleType;
//    myDebug() << "fasf" <<  this;

//    list << moduleName
//         << moduleShortName
//         << QString::number(chapterValue)
//         << modulePath;
//    list << append(moduleName).append(moduleShortName).append(chapterValue);

    return list;
}
//------------------------------------------------------------------------------
void QSopherimModule::setModulePath(QString newPath)
{
    m_modulePath = newPath;
}
//------------------------------------------------------------------------------
QString QSopherimModule::getModulePath()
{
    return m_modulePath;
}
//------------------------------------------------------------------------------
QStringList QSopherimModule::getBookList()
{
//    myDebug() << bookList.size();
//    myDebug() << "fasf" << this;
    return m_bookList;
}
//------------------------------------------------------------------------------
void QSopherimModule::setBookList(QStringList newlist)
{
    m_bookList = newlist;
}
//------------------------------------------------------------------------------
QHash<QString, int> QSopherimModule::getNumberOfChaptersInBooks()
{
    return m_numberOfChaptersInBook;
}
//------------------------------------------------------------------------------
void QSopherimModule::setNumberOfChaptersInBooks(QHash<QString, int> newP)
{
    m_numberOfChaptersInBook = newP;
}
//------------------------------------------------------------------------------
int QSopherimModule::getValueChapterForBookFromModule(QString nameOfBook)
{
    return m_numberOfChaptersInBook.value(nameOfBook);
}
//------------------------------------------------------------------------------
QString QSopherimModule::getModuleType()
{
    return m_moduleType;
}
//------------------------------------------------------------------------------
void QSopherimModule::setModuleType(QString newType)
{
    m_moduleType = newType;
}
//------------------------------------------------------------------------------
