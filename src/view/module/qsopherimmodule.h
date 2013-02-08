#ifndef QSopherimMODULE_H
#define QSopherimMODULE_H

#include <QString>
#include <QStringList>
#include <QHash>

class QSopherimModuleInfo
{
public:
    QString moduleName;
    QString moduleShortName;
    QString modulePath;
    QStringList bookList;
    int bookValue;
    QHash<QString, int> numberOfChaptersInBook;
};

class QSopherimModule
{
public:
    QSopherimModule();
    QSopherimModule(QSopherimModuleInfo list);

    QString getModuleName();
    void setModuleName(QString);

    QString getModuleShortName();
    void setModuleShortName(QString);

    int getBookValue();
    void setBookValue(int);

    QString getModulePath();
    void setModulePath(QString newpath);

    QSopherimModuleInfo getModuleInfo();

    QStringList getBookList();
    void setBookList(QStringList);

    QHash<QString, int> getNumberOfChaptersInBooks();
    void setNumberOfChaptersInBooks(QHash<QString, int>);

    int getValueChapterForBookFromModule(QString nameOfBook);


private:
    QString moduleName;
    QString moduleShortName;
    QString modulePath;
    QStringList bookList;
    int bookValue;
    QHash<QString, int> numberOfChaptersInBook;

    void init();

};

#endif // QSopherimMODULE_H
