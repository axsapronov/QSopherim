#include "biblequotedictmodule.h"

#include "debughelper.h"

BibleQuoteDictModule::BibleQuoteDictModule(QString pathToModule)
{
    parseModule(pathToModule);
}
//------------------------------------------------------------------------------
BibleQuoteDictModule::BibleQuoteDictModule()
{

}
//------------------------------------------------------------------------------
void BibleQuoteDictModule::parseModule(QString pathToModule)
{
        myDebug() << "Parse module: " << pathToModule;
//    MetaInfo parseInfo = readInfo(pathToModule);
//    loadBibleData(1, pathToModule);
//    //    myDebug() << readInfo(pathToModule).name() << readInfo(pathToModule).shortName();

//    // добавить еще обработку типа
//    QDir d(Config::configuration()->getAppDir() + "bible/" + parseInfo.shortName());
//    if (!d.exists())
//    {
//        emit SIGNAL_CreateFolderForModule(parseInfo.shortName());
//        if (createIniFile(parseInfo))
//        {
////            createBookFiles(pathToModule);
//        }
//        else
//        {
////            myWarning() << "this module is created";
//        }
//    }
//    else
//    {
////        myDebug() << "This module is exist";
//    }
}
//------------------------------------------------------------------------------
