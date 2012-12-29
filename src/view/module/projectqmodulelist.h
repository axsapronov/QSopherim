#ifndef PROJECTQMODULELIST_H
#define PROJECTQMODULELIST_H

#include "projectqmodule.h"
class ProjectQModule;
#include <QVector>

class ProjectQModuleList
{

public:
    explicit ProjectQModuleList();

    /**
     * @brief getNextModule
     * @return
     */
    ProjectQModule* getNextModule();
    /**
     * @brief getModule
     * @param id
     * @return
     */
    ProjectQModule* getModule(int id);

    /**
     * @brief addModule
     */
    void addModule(ProjectQModule*);

    /**
     * @brief deleteModule
     * @param nameModule
     */
    void deleteModule(QString nameModule);
    /**
     * @brief hideModule
     * @param nameModule
     */
    void hideModule(QString nameModule);

    void showModule(QString nameModule);

    /**
     * @brief getCurNumberModule
     * @return
     */
    int getCurNumberModule();

    /**
     * @brief refreshList
     */
    void refreshList(QString = "bible/");
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
    ProjectQModule* getModuleWithName(QString name);
    /**
     * @brief getModuleBooks
     * @return
     */
    QStringList getModuleBooks(QString);

    void clearList();

private:
    QVector<ProjectQModule*> moduleList;
    int cur_int;
    void init();
    void findModules(QString dir);
    QStringList getModuleFilesList(QStringList files);
    //
};

#endif // PROJECTQMODULELIST_H
