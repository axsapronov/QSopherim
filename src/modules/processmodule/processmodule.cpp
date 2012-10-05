
#include "processmodule.h"
#include "moduledefinition.h"
#include "debughelper.h"
#include "config.h"

#include <QObject>
#include <QDir>

//------------------------------------------------------------------------------
ProcessModule::ProcessModule()
{
    init();
    createConnects();
}
//------------------------------------------------------------------------------
ProcessModule::ProcessModule(QString pathToModule, int typeModule)
{
    //    myDebug() << processing(pathToModule, typeModule);
    init();
    createConnects();
    processing(pathToModule, typeModule);
}
//------------------------------------------------------------------------------
ProcessModule::~ProcessModule()
{

}
//------------------------------------------------------------------------------
void ProcessModule::createConnects()
{
    connect(m_biblequote, SIGNAL(createFolderForModule(QString)), SLOT(createFolderForModule(QString)));
}
//------------------------------------------------------------------------------
void ProcessModule::init()
{
    m_biblequote = new BibleQuoteModule();
    //    connect(m_biblequote, SIGNAL(createFolderForModule(QString)), SLOT(createFolderForModule(QString)));
}
//------------------------------------------------------------------------------
bool ProcessModule::processing(QString pathToModule, int type)
{
    //    myDebug() << pathToModule << type;
    switch (type)
    {
    case OBVCore::Type_BibleQuoteModule:
        //        myDebug() << "this is biblequote module";
        m_biblequote->parseModule(pathToModule);
        emit signal_processOk();
        break;
    case OBVCore::Type_SwordBibleModule:
        //        myDebug() << "this is sword module";
        break;
    default:
        //        myDebug() << "unknown module type";
        ;
    }
    return true;
}
//------------------------------------------------------------------------------
void ProcessModule::createFolderForModule(QString shortname)
{
//    myDebug() << shortname;
    /// create folder for module
    QDir dir;
    dir.mkpath(Config::configuration()->getAppDir() + "bible/" + shortname);
}
//------------------------------------------------------------------------------
