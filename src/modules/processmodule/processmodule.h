#ifndef __PROCESSMODULE__H
#define __PROCESSMODULE__H
#include <QObject>

#include "biblequote.h"
#include <QString>


class ProcessModule: public QObject
{
    Q_OBJECT

public:
    explicit ProcessModule(QString pathToModule, int typeModule);
    explicit ProcessModule();

    ~ProcessModule();

    bool processing(QString pathToModule, int type);
signals:
    void signal_processOk();
private slots:
    void createFolderForModule(QString shortname);
private:
    BibleQuoteModule* m_biblequote;
    void createConnects();
    void init();
    QString p_pathToModule;
};


#endif // __PROCESSMODULE__H
