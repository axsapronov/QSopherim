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
    moduleName = list.moduleName;
    moduleShortName  = list.moduleShortName;
    bookValue = list.bookValue;
    modulePath = list.modulePath;
    bookList = list.bookList;
    numberOfChaptersInBook = list.numberOfChaptersInBook;
//    myDebug() << getBookList().size();
//    myDebug() << this;
}
//------------------------------------------------------------------------------
int QSopherimModule::getBookValue()
{
   return this->bookValue;
}
//------------------------------------------------------------------------------
QString QSopherimModule::getModuleName()
{
    return this->moduleName;
}
//------------------------------------------------------------------------------
QString QSopherimModule::getModuleShortName()
{
    return this->moduleShortName;
}
//------------------------------------------------------------------------------
void QSopherimModule::setBookValue(int newvalue)
{
    this->bookValue = newvalue;
}
//------------------------------------------------------------------------------
void QSopherimModule::setModuleName(QString newname)
{
    this->moduleName = newname;
}
//------------------------------------------------------------------------------
void QSopherimModule::setModuleShortName(QString newname)
{
    this->moduleShortName = newname;
}
//------------------------------------------------------------------------------
void QSopherimModule::init()
{
    bookValue = 0;
    moduleName = "";
    moduleShortName = "";
    modulePath = "";
    bookList.clear();
    numberOfChaptersInBook.clear();
}
//------------------------------------------------------------------------------
QSopherimModuleInfo QSopherimModule::getModuleInfo()
{
    QSopherimModuleInfo list;
    list.moduleName = moduleName;
    list.moduleShortName = moduleShortName;
    list.bookValue = bookValue;
    list.modulePath = modulePath;
    list.bookList = bookList;
    list.numberOfChaptersInBook = numberOfChaptersInBook;
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
    modulePath = newPath;
}
//------------------------------------------------------------------------------
QString QSopherimModule::getModulePath()
{
    return modulePath;
}
//------------------------------------------------------------------------------
QStringList QSopherimModule::getBookList()
{
//    myDebug() << bookList.size();
//    myDebug() << "fasf" << this;
    return bookList;
}
//------------------------------------------------------------------------------
void QSopherimModule::setBookList(QStringList newlist)
{
    bookList = newlist;
}
//------------------------------------------------------------------------------
QHash<QString, int> QSopherimModule::getNumberOfChaptersInBooks()
{
    return numberOfChaptersInBook;
}
//------------------------------------------------------------------------------
void QSopherimModule::setNumberOfChaptersInBooks(QHash<QString, int> newP)
{
    numberOfChaptersInBook = newP;
}
//------------------------------------------------------------------------------
int QSopherimModule::getValueChapterForBookFromModule(QString nameOfBook)
{
    return numberOfChaptersInBook.value(nameOfBook);
}
//------------------------------------------------------------------------------
