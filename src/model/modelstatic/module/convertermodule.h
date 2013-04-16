#ifndef CONVERTERMODULE_H
#define CONVERTERMODULE_H

#include <QObject>

#include "src/model/modelstatic/moduleinfo.h"

class ConverterModule : public QObject
{
    Q_OBJECT
public:
    explicit ConverterModule(QObject *parent = 0);

    void addModuleToListConvert(QString t_modulePath);
    void removeModuleFromListConvert(QString t_modulePath);

signals:
    void SIGNAL_ConvertFinish();

public slots:
    void sStartConvert();

private:
    QList<ModuleInfo> m_modulesToConvert;

    ModuleInfo* getModuleInfoOfPath(QString t_modulePath);
};

#endif // CONVERTERMODULE_H
