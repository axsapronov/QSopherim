#ifndef QSopherimMODULELIST_H
#define QSopherimMODULELIST_H

#include "qsopherimmodule.h"
class QSopherimModule;
#include <QVector>

class QSopherimModuleList
{

public:
    explicit QSopherimModuleList();

    ~QSopherimModuleList();

    /**
     * @brief getNextModule
     * @return
     */
    QSopherimModule* getNextModule();
    /**
     * @brief getModule
     * @param id
     * @return
     */
    QSopherimModule* getModule(int id);

    /**
     * @brief addModule
     */
    void addModule(QSopherimModule*);

    /**
     * @brief deleteModule
     * @param nameModule
     */
    void deleteModule(const QString nameModule);
    /**
     * @brief hideModule
     * @param nameModule
     */
    void hideModule(const QString nameModule);

    void showModule(const QString nameModule);

    /**
     * @brief isExist
     * @param nameModule
     * @return
     */
    bool isExist(const QString nameModule);

    /**
     * @brief getCurNumberModule
     * @return
     */
    int getCurNumberModule();

    /**
     * @brief refreshList
     */
    void refreshList(const QString = "bible/");
    /**
     * @brief getSize
     * @return
     */
    int getSize();
    /**
     * @brief getModuleWithName
     * @param name
     * @return
     */
    QSopherimModule* getModuleWithName(const QString name);
    /**
     * @brief getModuleBooks
     * @return
     */
    QStringList getModuleBooks(const QString nameOfModule);

    void clearList();

private:
    QVector<QSopherimModule*> m_moduleList;
    int cur_int;
    void init();
    void findModules(QString dir);
    QStringList getModuleFilesList(QStringList files);
    //
};

#endif // QSopherimMODULELIST_H
