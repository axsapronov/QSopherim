
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
    m_BibleQuote->deleteLater();
    delete m_BibleQuoteDictModule;
    delete m_BibleQuoteComments;
}
//------------------------------------------------------------------------------
void ProcessModule::createConnects()
{
    connect(m_BibleQuote, SIGNAL(SIGNAL_CreateFolderForModule(QString)), SLOT(createFolderForModule(QString)));
    connect(m_BibleQuoteComments, SIGNAL(SIGNAL_CreateFolderForModule(QString)), SLOT(createFolderForModule(QString)));
    connect(m_BibleQuoteApocrypha, SIGNAL(SIGNAL_CreateFolderForModule(QString)), SLOT(createFolderForModule(QString)));
}
//------------------------------------------------------------------------------
void ProcessModule::init()
{
    m_BibleQuote = new BibleQuoteModule();
    m_BibleQuoteDictModule = new BibleQuoteDictModule();
    m_BibleQuoteComments = new BibleQuoteModule();
    m_BibleQuoteApocrypha = new BibleQuoteModule();
}
//------------------------------------------------------------------------------
bool ProcessModule::processing(QString pathToModule, int type)
{
    p_pathToModule = pathToModule;
    //    myDebug() << pathToModule << type;
    switch (type)
    {
    case OBVCore::Type_BibleQuoteModule:
        m_BibleQuote->parseModule(p_pathToModule);
        break;
    case OBVCore::Type_BibleQuoteDictModule:
        m_BibleQuoteDictModule->parseModule(p_pathToModule);
        break;
    case OBVCore::Type_BibleQuoteComments:
        m_BibleQuoteComments->setTypeModule("Comments");
        m_BibleQuoteComments->parseModule(p_pathToModule);
        break;
    case OBVCore::Type_BibleQuoteApocrypha:
        m_BibleQuoteApocrypha->setTypeModule("Apocrypha");
        m_BibleQuoteApocrypha->parseModule(p_pathToModule);
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
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
