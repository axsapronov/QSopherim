#include "biblequote.h"
#include <debughelper.h>
#include <QTextCodec>
#include <QString>
BibleQuoteModule::BibleQuoteModule(QString pathToModule)
{
    parseModule(pathToModule);

}
///-----------------------------------------------------------------------------
BibleQuoteModule::BibleQuoteModule()
{

}
///-----------------------------------------------------------------------------
BibleQuoteModule::~BibleQuoteModule()
{

}
///-----------------------------------------------------------------------------
void BibleQuoteModule::parseModule(QString pathToModule)
{
    myDebug() << "Parse module: " << pathToModule;
    //    emit createFolderForModule();
}
///-----------------------------------------------------------------------------
MetaInfo BibleQuoteModule::readInfo(QFile &file)
{
    bool useShortName = false;
    m_moduleName.clear();
    m_moduleShortName.clear();
    int countlines = 0;
//    ModuleSettings *settings = m_settings->getModuleSettings(m_moduleID);

    if(m_codec == NULL)
    {
//        QString encoding;
        QString encoding = "UTF-8";
//        if(settings == NULL)
//        {
//            encoding = m_settings->encoding;
//        }
//        else
//        {
//            if(settings->encoding == "Default" || settings->encoding.isEmpty())
//            {
//                encoding = m_settings->encoding;
//            }
//            else
//            {
//                encoding = settings->encoding;
//            }
//        }
        m_codec = QTextCodec::codecForName(encoding.toStdString().c_str());
    }

    QTextDecoder *decoder = m_codec->makeDecoder();
    while(!file.atEnd())
    {
        /*if (countlines > 50) { //wenn eine ini datei ungueltig ist soll damit nicht zuviel zeit verguedet werden
            break;
        }*/
        QByteArray byteline = file.readLine();
        QString line = decoder->toUnicode(byteline);
        if(!line.startsWith("//"))
        {
            countlines++;
        } else {
            continue;
        }
        if(line.contains("BibleName", Qt::CaseInsensitive))
        {
            m_moduleName = formatFromIni(line.remove(QRegExp("BibleName(\\s*)=(\\s*)", Qt::CaseInsensitive)));
            if(m_moduleName.isEmpty())
            {
                useShortName = true;
            }
            if(useShortName && !m_moduleShortName.isEmpty())
            {
                break;
            } else if(!useShortName)
            {
                break;
            }
        }
        if(line.contains("BibleShortName", Qt::CaseInsensitive))
        {
            m_moduleShortName = formatFromIni(line.remove(QRegExp("BibleShortName(\\s*)=(\\s*)", Qt::CaseInsensitive)));
            if(useShortName)
                break;
        }

    }
    file.close();
    if(useShortName)
    {
        m_moduleName = m_moduleShortName;
    }
    if(m_moduleName.isEmpty())
    {
        myWarning() << "invalid ini File " << file.fileName();
    }

    m_moduleName = "f";
    m_moduleShortName = "ff";
    MetaInfo ret;
    ret.setName(m_moduleName);
    ret.setShortName(m_moduleShortName);
    return ret;
    return MetaInfo();
}
///-----------------------------------------------------------------------------
MetaInfo BibleQuoteModule::readInfo(const QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly))
        return MetaInfo();
    return readInfo(file);
    return MetaInfo();
}
///-----------------------------------------------------------------------------
QString BibleQuoteModule::formatFromIni(QString input)
{
    return input.trimmed();
}
///-----------------------------------------------------------------------------
///-----------------------------------------------------------------------------
///-----------------------------------------------------------------------------
