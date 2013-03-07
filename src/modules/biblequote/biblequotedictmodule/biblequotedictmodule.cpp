#include "biblequotedictmodule.h"

#include "defines.h"

#include "debughelper.h"
#include "stringcommon.h"

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
    pathToModule.replace(".idx", ".htm");
    //    myDebug() << "Parse module: " << pathToModule;
    QStringList params = getInfoFromFile(pathToModule);
    //    myDebug() << params;

    m_author = params.at(0);
    m_revision = params.at(1);
    m_language = params.at(2);
    m_type = params.at(3);
    m_description = params.at(4);
    m_numbering = params.at(6);
    m_copyright = params.at(5);
    m_path = pathToModule;

    QString name  = QString(pathToModule).split("/").last();
    name = QString(name).split(".").first();
    m_name = name;

    QDir d(Config::configuration()->getDictDir()+ name);
    if (!d.exists())
    {

        QDir dir;
        dir.mkpath(Config::configuration()->getDictDir() + name);

        if (createIniFile())
        {
            createDictFile(pathToModule);
        }
        else
        {
            myWarning() << "this module is created";
        }
    }
    else
    {
//        myDebug() << "This module is exist";
    }
}
//------------------------------------------------------------------------------
bool BibleQuoteDictModule::createIniFile()
{
    m_type = "Dictionary";
    /// добавить обработку типа
    QString text =
            "////Module for QSopherim"
            "\nModuleName = " + m_name +
            "\nAuthor = " + m_author +
            "\nRevision = " + m_revision +
            "\nLanguage = " + m_language+
            "\nType = " + m_type +
            "\nDescription = " + m_description +
            "\nRight = " + m_copyright +
            "\nNumbering= " + m_numbering +
            "\nPathToModule = " + "dictionary/" +  m_name + "/module" + GL_FORMAT_MODULE;
    //    myDebug() << m_bookPath;
    QString t_pathToIniFile = QString(Config::configuration()->getDictDir() +
                                      m_name + "/module" + GL_FORMAT_MODULE);
    if (QFile::exists(t_pathToIniFile))
    {
        QFile::remove(t_pathToIniFile);
    }
    return createEmpty(Config::configuration()->getDictDir() +
                       m_name + "/module" + GL_FORMAT_MODULE, text);
    return false;
}
//------------------------------------------------------------------------------
void BibleQuoteDictModule::createDictFile(QString path)
{
    QString text = getTextFromHtmlFile(path);
    QStringList list;

    QHash<int, WordDictList> wordList;
    list = text.split("<h4>");

    for (int i = 0; i < list.size() - 1; i++)
    {
        QString line = list.at(i + 1);
        QStringList t_word;
        t_word = line.split("</h4>");
//        t_word.replace('"', "");
        WordDictList t_list;
        t_list.word = t_word.at(0);

        t_word = t_word.at(1).split("\n");
        for (int j = 0; j < t_word.size(); j++)
        {
            t_list.text.append(getCoolLine(t_word.at(j)) + "\n");
        }
        wordList[i] = t_list;
    }
    writeDictFile(&wordList);
}
//------------------------------------------------------------------------------
void BibleQuoteDictModule::writeDictFile(QHash<int, WordDictList> *wordList)
{
    QString path;
    path = QString(Config::configuration()->getDictDir() + m_name + "/dict" + GL_FORMAT_TEXT);
    QFile file(path);
    if (file.exists())
        file.remove();

    if(file.open(QIODevice::WriteOnly))
    {
        QString tab = "    ";
        QTextStream ts(&file);
        ts.setCodec(getCodecOfEncoding("UTF-8"));
        ts << "<xml>" << endl;

        for (int i = 0; i < wordList->size(); i++)
        {
            WordDictList t_list = wordList->value(i);
            ts << tab
               << "<word name=\""
               << t_list.word
               << "\">"
               << t_list.text
               << tab << "</word>"
               << endl;
        }
        ts << "</xml>" << endl;
    }
}
//------------------------------------------------------------------------------
