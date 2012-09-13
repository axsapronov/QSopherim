#ifndef __PROCESSMODULE__H
#define __PROCESSMODULE__H

#include <QString>

class ProcessModule
{

public:
    explicit ProcessModule(QString pathToModule, QString typeModule);
    explicit ProcessModule();

    ~ProcessModule();

    bool processing(QString pathToModule, QString type);
};


#endif // __PROCESSMODULE__H
