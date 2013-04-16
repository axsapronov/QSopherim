#ifndef ABSTRACTMODULE_H
#define ABSTRACTMODULE_H

#include <QObject>
#include <QFile>
#include <QMap>
#include "src/model/modelstatic/moduleinfo.h"

class AbstractModule: public QObject
{
    Q_OBJECT

public:
    AbstractModule();

    virtual ~AbstractModule();

    virtual int loadBibleData(const int moduleID, const QString &path);
    virtual ModuleInfo readInfo(QFile &file);

    virtual QMap<int, int> minMaxVerse(int bookID, int chapterID);

    virtual bool hasIndex() const;
    virtual void buildIndex();

    virtual int moduleID() const;
    virtual QString modulePath() const;
    virtual QString moduleName(bool preferShortName = false) const;

    virtual QString uid() const;
    virtual void clear();
    virtual void clearData();

    virtual void parseModule(QString pathToModule);
};

#endif // ABSTRACTMODULE_H
