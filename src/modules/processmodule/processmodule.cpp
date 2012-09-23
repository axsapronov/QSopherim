
#include "processmodule.h"
#include "moduledefinition.h"


#include "debughelper.h"
#include <QString>

//------------------------------------------------------------------------------
ProcessModule::ProcessModule()
{

}
//------------------------------------------------------------------------------
ProcessModule::ProcessModule(QString pathToModule, int typeModule)
{
//    myDebug() << processing(pathToModule, typeModule);
    processing(pathToModule, typeModule);
}
//------------------------------------------------------------------------------
ProcessModule::~ProcessModule()
{

}
//------------------------------------------------------------------------------
bool ProcessModule::processing(QString pathToModule, int type)
{
//    myDebug() << pathToModule << type;
    switch (type)
    {
    case OBVCore::Type_BibleQuoteModule:
//        myDebug() << "this is biblequote module";
        m_biblequote = BibleQuoteModule(pathToModule);
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
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
