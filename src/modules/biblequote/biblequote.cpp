#include "biblequote.h"
#include "debughelper.h"
#include "filecommon.h"
#include "moduledefinition.h"
#include "config.h"

#include <QTextCodec>
#include <QString>
BibleQuoteModule::BibleQuoteModule(QString pathToModule)
{
    //        DEBUG_FUNC_NAME;
    parseModule(pathToModule);
}
//------------------------------------------------------------------------------
BibleQuoteModule::BibleQuoteModule()
{

}
//------------------------------------------------------------------------------
BibleQuoteModule::~BibleQuoteModule()
{

}
//------------------------------------------------------------------------------
void BibleQuoteModule::parseModule(QString pathToModule)
{
    //    myDebug() << "Parse module: " << pathToModule;
    MetaInfo parseInfo = readInfo(pathToModule);
    loadBibleData(1, pathToModule);
    //    myDebug() << readInfo(pathToModule).name() << readInfo(pathToModule).shortName();

    // добавить еще обработку типа
    QDir d(Config::configuration()->getAppDir() + "bible/" + parseInfo.shortName());
    if (!d.exists())
    {
        emit createFolderForModule(parseInfo.shortName());
        if (createIniFile(parseInfo))
        {
            createBookFiles(pathToModule);
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
MetaInfo BibleQuoteModule::readInfo(QFile &file)
{
    bool useShortName = false;
    m_moduleName.clear();
    m_moduleShortName.clear();
    int countlines = 0;

    QString encoding = getEncodingFromFile(file.fileName());
    m_codec = QTextCodec::codecForName(encoding.toStdString().c_str());

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
        }
        else
        {
            continue;
        }

        if(line.contains("BibleName", Qt::CaseInsensitive) and m_moduleName.isEmpty())
        {
            m_moduleName = formatFromIni(line.
                                         remove(QRegExp("BibleName(\\s*)=(\\s*)",
                                                        Qt::CaseInsensitive)));
            if(m_moduleName.isEmpty())
            {
                useShortName = true;
            }
            if(useShortName && !m_moduleShortName.isEmpty())
            {
                break;
            }
            /// what is ?
            //            else if(!useShortName)
            //            {
            //                break;
            //            }
        }
        if(line.contains("BibleShortName", Qt::CaseInsensitive) and m_moduleShortName.isEmpty())
        {
            m_moduleShortName = formatFromIni(line.
                                              remove(QRegExp("BibleShortName(\\s*)=(\\s*)",
                                                             Qt::CaseInsensitive)));
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

    MetaInfo ret;
    ret.setName(m_moduleName);
    ret.setShortName(m_moduleShortName);
    ret.type = OBVCore::Type_BibleQuoteModule;
    return ret;
    return MetaInfo();
}
//------------------------------------------------------------------------------
MetaInfo BibleQuoteModule::readInfo(const QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly))
        return MetaInfo();
    return readInfo(file);
    return MetaInfo();
}
//------------------------------------------------------------------------------
QString BibleQuoteModule::formatFromIni(QString input)
{
    return input.trimmed();
}
//------------------------------------------------------------------------------
bool BibleQuoteModule::createIniFile(MetaInfo info)
{
    /// добавить обработку типа
    QString text =
            "////Module for projectQ"
            "\nModuleName = " + info.name() +
            "\nModuleShortName = " + info.shortName() +
            "\nModuleLanguage = " + info.language +
            "\nBooksValue = " + m_bookCount +
            "\nModuleVerseSign = " + m_verseSign +
            "\nModuleChapterSign = " + m_chapterSign +
            "\nModuleChapterZero = " + m_chapterZero +
            "\nPathToModule = " + "bible/" + info.shortName() + "/module.ini";

    text.append("\nBookList = ");
    for(int i = 0; i < m_bookList.size(); i++)
    {
        text.append(m_bookList.at(i) + ":");
    }

    text.append("\nNumberChapter = ");
    for(int i = 0; i < m_bookList.size(); i++)
    {
        QString str = m_bookList.at(i) + "^" + QString::number(m_bookCountSize[i])
                + "::" ;
        //        QString str = m_bookList.at(i) + "^" + QString::number(m_bookList.at(i).size()) + "::";
        text.append(str);
    }

    //    myDebug() << m_bookPath;
    QString t_pathToIniFile = QString(Config::configuration()->getAppDir() + "bible/" +
                                      info.shortName() + "/module.ini");
    if (QFile::exists(t_pathToIniFile))
    {
        QFile::remove(t_pathToIniFile);
    }
    return createEmpty(Config::configuration()->getAppDir() + "bible/" +
                       info.shortName() + "/module.ini", text);

    return false;
}
//------------------------------------------------------------------------------
bool BibleQuoteModule::createBookFiles(QString pathToFiles)
{
    Q_UNUSED (pathToFiles)
    QString t_pathToXmlFile = QString(Config::configuration()->getAppDir() + "bible/" +
                                      m_moduleShortName + "/text.xml");

    if (QFile::exists(t_pathToXmlFile))
    {
        QFile::remove(t_pathToXmlFile);
    }
    createEmptyXML(t_pathToXmlFile);
    for (int i = 0; i < m_bookPath.size(); i++)
    {
        readBook(i);
    }
    endXML(t_pathToXmlFile);
    return false;
}
//------------------------------------------------------------------------------
int BibleQuoteModule::moduleID() const
{
    return m_moduleID;
}
//------------------------------------------------------------------------------
QString BibleQuoteModule::modulePath() const
{
    return m_modulePath;
}
//------------------------------------------------------------------------------
QString BibleQuoteModule::moduleName(bool preferShortName) const
{
    Q_UNUSED (preferShortName)
    return m_moduleName;
}
//------------------------------------------------------------------------------
QString BibleQuoteModule::uid() const
{
    return m_uid;
}
//------------------------------------------------------------------------------
int BibleQuoteModule::loadBibleData(const int bibleID, const QString &path)
{
    QStringList bookFullName;
    QList<QStringList> bookShortName;
    QMap<int, int> bookCount;

    m_moduleID = bibleID;
    m_bookPath.clear();
    m_moduleName = "";
    m_chapterSign = "";
    m_removeHtml = "";
    m_verseSign = "";
    m_bookCount = "";
    m_chapterZero = false;
    m_bookList.clear();

    m_uid = path;

    int lastPos = path.lastIndexOf("/");
    QString path_ = path;
    m_modulePath = path_.remove(lastPos, path.size());
    bool started = false;
    bool started2 = false;
    int count = 0;

    QFile file;
    file.setFileName(path);
    QString encoding;
    //    ModuleSettings *settings = m_settings->getModuleSettings(m_moduleID);
    //    if(settings->encoding == "Default" || settings->encoding.isEmpty()) {
    //        encoding = m_settings->encoding;
    //    } else {
    //        encoding = settings->encoding;
    //    }
    m_codec = getCodecOfEncoding(getEncodingFromFile(path));
    QTextDecoder *decoder = m_codec->makeDecoder();
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        int i = 0;
        while(!file.atEnd()) {
            const QByteArray byteline = file.readLine();
            QString line = decoder->toUnicode(byteline);

            if(line.startsWith("//")) {//it is a comment
                continue;
            }

            if(line.contains("BibleName", Qt::CaseInsensitive)) {
                m_moduleName = formatFromIni(line.remove(QRegExp("BibleName(\\s*)=(\\s*)", Qt::CaseInsensitive)));
            }
            if(line.contains("BibleShortName", Qt::CaseInsensitive)) {
                m_moduleShortName = formatFromIni(line.remove(QRegExp("BibleShortName(\\s*)=(\\s*)", Qt::CaseInsensitive)));
            }
            if(line.contains("ChapterSign", Qt::CaseInsensitive))
            {
                m_chapterSign = formatFromIni(line.remove(QRegExp("ChapterSign(\\s*)=(\\s*)", Qt::CaseInsensitive)));
            }
            if(line.contains("HTMLFilter", Qt::CaseInsensitive)) {
                m_removeHtml = formatFromIni(line.remove(QRegExp("HTMLFilter(\\s*)=(\\s*)", Qt::CaseInsensitive)));
            }
            if(line.contains("VerseSign", Qt::CaseInsensitive)) {
                m_verseSign = formatFromIni(line.remove(QRegExp("VerseSign(\\s*)=(\\s*)", Qt::CaseInsensitive)));
            }
            if(line.contains("ChapterZero", Qt::CaseInsensitive)) {
                const QString zero = formatFromIni(line.remove(QRegExp("ChapterZero(\\s*)=(\\s*)", Qt::CaseInsensitive)));
                if(zero.compare("Y", Qt::CaseInsensitive) == 0) {
                    m_chapterZero = true;
                } else {
                    m_chapterZero = false;
                }
            }

            if(started == false && line.contains("BookQty", Qt::CaseInsensitive))
            {
                m_bookCount = formatFromIni(line.remove(QRegExp("BookQty(\\s*)=(\\s*)", Qt::CaseInsensitive)));
                started = true;
            }
            if(started == true)
            {
                if(started2 == true)
                {
                    if(line.contains("ChapterQty", Qt::CaseInsensitive))
                    {
                        bookCount[i] = formatFromIni(line.remove(QRegExp("ChapterQty(\\s*)=(\\s*)", Qt::CaseInsensitive))).toInt();
                        i++;
                        started2 = false;
                    }
                    else if(line.contains("FullName", Qt::CaseInsensitive))
                    {
                        bookFullName << formatFromIni(line.remove(QRegExp("FullName(\\s*)=(\\s*)", Qt::CaseInsensitive)));

                    }
                    else if(line.contains("ShortName", Qt::CaseInsensitive))
                    {
                        const QString s = formatFromIni(line.remove(QRegExp("ShortName(\\s*)=(\\s*)", Qt::CaseInsensitive)));
                        bookShortName.append(s.split(" "));

                    }
                }
                else if(line.contains("PathName", Qt::CaseInsensitive))
                {
                    count++;
                    started2 = true;
                    m_bookPath << formatFromIni(line.remove(QRegExp("PathName(\\s*)=(\\s*)", Qt::CaseInsensitive)));

                }
            }

        }
    }
    //    m_versification = settings->loadVersification();
    //    if(settings->noV11N()) {
    //        myDebug() << "load new versification";
    //        m_versification = QSharedPointer<Versification>(new Versification_BibleQuote(bookFullName, bookShortName, bookCount));
    //        settings->v11n = m_versification.toWeakRef();
    //        settings->versificationName = "";
    //        settings->versificationFile = m_settings->v11nFile(path);

    //    }
    //    settings->getV11n()->extendedData.setHasChapterZeor(m_chapterZero);
    m_bookCountSize = bookCount;
    m_bookList = bookFullName;
    return 0;
}

//------------------------------------------------------------------------------
int BibleQuoteModule::readBook(const int id)
{
    m_book.clear();
    m_book.setID(id);
    if(id >= m_bookPath.size())
        return 1;
    const QString path = m_modulePath + "/" + m_bookPath.at(id);
    QFile file;
    file.setFileName(path);

    QString tab = "    ";

    QString out;
    QString out2;
    bool chapterstarted = false;
    int ccount2 = 0;
    QStringList chapterText;
    const QStringList removeHtml2 = m_removeHtml.split(" ");

    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextDecoder *decoder = m_codec->makeDecoder();
        while(!file.atEnd())
        {
            const QByteArray byteline = file.readLine();


            QString line = decoder->toUnicode(byteline);
            //            line.remove("\n").remove("\r");
            //            line.remove(m_verseSign);

            //filterout
            //            if(m_settings->getModuleSettings(m_moduleID)->biblequote_removeHtml == true && removeHtml2.size() > 0) {
            foreach(const QString & r, removeHtml2)
            {
                line = line.remove(r, Qt::CaseInsensitive);
            }
            //            line.replace(m_chapterSign, getEndOfTag(m_chapterSign));
            //            }
            out2 += line;
            if(chapterstarted == false && line.contains(m_chapterSign))
            {
                chapterstarted = true;
            }
            if(chapterstarted == true && line.contains(m_chapterSign))
            {
                ccount2++;
                //                                myDebug() << out;
                out = line;
            }
            else if(chapterstarted == true)
            {
                out += line;
            }
        }
        ///  chapter_tag is ANAME
        if (m_chapterSign != getEndOfTag(m_chapterSign))
            out2.remove(QRegExp("=\\d+>")); // hindi remove text =NUMBERCHAPTER>
        out2.remove("^&к");
        //        out2 = getClearText(&out2);
        chapterText << out2.split(m_chapterSign);
    }
    else
    {
        //becauce windows filename are case insensensitive
        //there are some filename typos in the ini files
        //and you cannot open this files on linux
        QFileInfo info(file.fileName());
        QDir d(info.absoluteDir());
        QStringList list = d.entryList();

        foreach(QString f, list)
        {
            QFileInfo info2(f);
            if(info2.baseName().compare(info.baseName(), Qt::CaseInsensitive) == 0)
            {
                m_bookPath.replace(id, f.remove(m_modulePath + "/"));
                return readBook(id);
            }
        }
        return 1;
    }
    if(ccount2 == 0)
    {
        chapterText << out2;
        ccount2 = 1;
    }

    //todo: its slow
    for(int i = 0; i < chapterText.size() - 1; i++)
    {
        Chapter c(i);
        const QStringList rawVerseList = chapterText.at(i + 1).split(m_verseSign);
        for(int j = 0; j < rawVerseList.size(); j++)
        {
            // split removes versesign but it is needed
            QString verseText = rawVerseList.at(j);
            //            myDebug() << verseText;

            if(verseText.contains("<p>") && !verseText.contains("</p>"))
                verseText.remove("<p>", Qt::CaseInsensitive);

            if(verseText.contains("</p>") || m_verseSign != "<p>")
                verseText.prepend(m_verseSign);

            const Verse v(j, verseText);
            c.addVerse(v);
        }
        m_book.addChapter(c);
    }
    //    myDebug() << chapterText;

    QString t_pathToXmlFile = QString(Config::configuration()->getAppDir() + "bible/" +
                                      m_moduleShortName + "/text.xml");
    //    myDebug() << t_pathToXmlFile;
    //    qDebug() << m_book.size();
    /// надо брать название книги, а не путь к ней
    m_bookList << m_bookPath.at(id);
    addBookToXML(t_pathToXmlFile, m_bookList.at(id), m_book);
    file.close();
    return 0;

}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
