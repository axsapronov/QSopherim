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
    QString moduleType;
    int bookValue;
    QHash<QString, int> numberOfChaptersInBook;
};

class QSopherimModule
{
public:
    QSopherimModule();
    QSopherimModule(QSopherimModuleInfo list);

    /**
     * @brief getModuleName
     * @return
     */
    QString getModuleName();
    /**
     * @brief setModuleName
     */
    void setModuleName(QString);

    /**
     * @brief getTypeModule
     * @return
     */
    QString getModuleType();
    /**
     * @brief setTypeModule
     */
    void setModuleType(const QString);

    /**
     * @brief getModuleShortName
     * @return
     */
    QString getModuleShortName();
    /**
     * @brief setModuleShortName
     */
    void setModuleShortName(QString);
    /**
     * @brief getBookValue
     * @return
     */
    int getBookValue();
    /**
     * @brief setBookValue
     */
    void setBookValue(int);
    /**
     * @brief getModulePath
     * @return
     */
    QString getModulePath();
    /**
     * @brief setModulePath
     * @param newpath
     */
    void setModulePath(QString newpath);
    /**
     * @brief getModuleInfo
     * @return
     */
    QSopherimModuleInfo getModuleInfo();
    /**
     * @brief getBookList
     * @return
     */
    QStringList getBookList();
    /**
     * @brief setBookList
     */
    void setBookList(QStringList);
    /**
     * @brief getNumberOfChaptersInBooks
     * @return
     */
    QHash<QString, int> getNumberOfChaptersInBooks();
    /**
     * @brief setNumberOfChaptersInBooks
     */
    void setNumberOfChaptersInBooks(QHash<QString, int>);
    /**
     * @brief getValueChapterForBookFromModule
     * @param nameOfBook
     * @return
     */
    int getValueChapterForBookFromModule(QString nameOfBook);

//    void setStrongType(const QString state);
//    QString getStrongType();

private:
    QString m_moduleName;
    QString m_moduleShortName;
    QString m_modulePath;
    QStringList m_bookList;
//    QString m_strongType;
    int m_bookValue;
    QString m_moduleType;
    QHash<QString, int> m_numberOfChaptersInBook;

    void init();

};

#endif // QSopherimMODULE_H
