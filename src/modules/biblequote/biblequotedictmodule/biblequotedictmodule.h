#ifndef BIBLEQUOTEDICTMODULE_H
#define BIBLEQUOTEDICTMODULE_H

#include "biblemodule.h"

class BibleQuoteDictModule : public BibleModule
{
    Q_OBJECT
public:
    BibleQuoteDictModule(QString pathToModule);
    BibleQuoteDictModule();

    void parseModule(QString pathToModule);
signals:

public slots:

};

#endif // BIBLEQUOTEDICTMODULE_H
