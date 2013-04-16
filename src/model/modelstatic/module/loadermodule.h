#ifndef LOADERMODULE_H
#define LOADERMODULE_H

#include <QObject>
#include "src/model/modelstatic/moduleinfo.h"
#include "src/model/modelstatic/module/abstractmodule.h"

class LoaderModule : public QObject
{
    Q_OBJECT
public:
    explicit LoaderModule(QObject *parent = 0);

    void addToListLoad(QString t_nameModule);
    void removeFromListLoad(QString t_nameModule);

signals:
    void SIGNAL_LoadFinish();

public slots:
    void sStartLoadModules();
    void sLoadModule(QString m_moduleName);

private:
    ModuleInfo* getModuleInfoOfName(QString t_nameModule);

    QList<QString> m_modulesToLoad; // path

};

#endif // LOADERMODULE_H
