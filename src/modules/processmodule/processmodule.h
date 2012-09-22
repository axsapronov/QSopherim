#ifndef __PROCESSMODULE__H
#define __PROCESSMODULE__H

#include <QString>

#include "biblequote.h"


class ProcessModule
{

public:
    explicit ProcessModule(QString pathToModule, int typeModule);
    explicit ProcessModule();

    ~ProcessModule();

    bool processing(QString pathToModule, int type);
private:
    BibleQuoteModule m_biblequote;
};


#endif // __PROCESSMODULE__H
