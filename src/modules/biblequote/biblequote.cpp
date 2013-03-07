#include "biblequote.h"
#include "debughelper.h"
#include "stringcommon.h"
#include "filecommon.h"
#include "moduledefinition.h"
#include "config.h"
#include "defines.h"

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

    QDir d;
    d = QDir(QString(Config::configuration()->getAppDir() + GL_MODULE_PATH +  "%1/" + parseInfo.shortName()).arg(m_typeModule.toLower()));

    if (!d.exists())
    {
        //        emit SIGNAL_CreateFolderForModule(parseInfo.shortName());
        QDir dir;
        dir.mkpath(QString(Config::configuration()->getAppDir() + GL_MODULE_PATH + "%1/" + parseInfo.shortName()).arg(m_typeModule.toLower()));

        if (createIniFile(parseInfo))
        {
            createBookFiles(pathToModule);

            if (!m_bibleType)
            {
                addToListBookModule(parseInfo.shortName());
            }
            else
            {
                addToListBibleModule(parseInfo.shortName());
            }
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

    if (m_typeModule == "Apocrypha")
        ret.type = OBVCore::Type_BibleQuoteApocrypha;

    if (m_typeModule == "Comments")
        ret.type = OBVCore::Type_BibleQuoteComments;

    if (m_typeModule == "Bible")
        ret.type = OBVCore::Type_BibleQuoteModule;

    if (m_typeModule == "Book")
        ret.type = OBVCore::Type_BibleQuoteBook;

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
            "////Module for QSopherim"
            "\nModuleName = " + info.name() +
            "\nModuleShortName = " + info.shortName() +
            "\nModuleLanguage = " + info.language +
            "\nBooksValue = " + m_bookCount +
            "\nModuleVerseSign = " + m_verseSign +
            "\nModuleChapterSign = " + m_chapterSign +
            "\nModuleChapterZero = " + m_chapterZero +
            "\nStrongNumber = " + m_strongOption +
            "\nTypeModule = " + m_typeModule;


    text.append(QString("\nPathToModule = %1/%2/module%3")
                .arg(m_typeModule.toLower())
                .arg(info.shortName())
                .arg(GL_FORMAT_MODULE));

    text.append("\nBookList = ");
    for(int i = 0; i < m_bookList.size(); i++)
    {
        text.append(m_bookList.at(i) + "[*:*]");
    }

    text.append("\nNumberChapter = ");
    for(int i = 0; i < m_bookList.size(); i++)
    {
        QString str = m_bookList.at(i) + "^" + QString::number(m_bookCountSize[i])
                + GL_SYMBOL_SPLIT_CHAPTER ;
        text.append(str);
    }

    //    myDebug() << m_bookPath;
    QString t_pathToIniFile = QString(QString(Config::configuration()->getAppDir() + GL_MODULE_PATH + "%1/" +
                                                                info.shortName() + "/module" + GL_FORMAT_MODULE).arg(m_typeModule.toLower()));

    if (QFile::exists(t_pathToIniFile))
    {
        QFile::remove(t_pathToIniFile);
    }



    QString r_str = QString(Config::configuration()->getAppDir() + GL_MODULE_PATH + "%1/" +
                           info.shortName() + "/module" + GL_FORMAT_MODULE)
                       .arg(m_typeModule.toLower());

    return createEmpty(r_str, text);

    return false;
}
//------------------------------------------------------------------------------
bool BibleQuoteModule::createBookFiles(QString pathToFiles)
{
    Q_UNUSED (pathToFiles)
    QString t_pathToXmlFile = QString(QString(Config::configuration()->getAppDir() + GL_MODULE_PATH + "%1/" +
                                              m_moduleShortName + "/text" + GL_FORMAT_TEXT).arg(m_typeModule.toLower()));

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
    m_strongOption = false;
    m_typeModule = m_typeModule;
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

            if(line.contains("BibleName", Qt::CaseInsensitive))
            {
                m_moduleName = getParamFromStr(&line, "BibleName");
            }
            if(line.contains("BibleShortName", Qt::CaseInsensitive))
            {
                m_moduleShortName = getParamFromStr(&line, "BibleShortName");
            }
            if(line.contains("ChapterSign", Qt::CaseInsensitive))
            {
                m_chapterSign = getParamFromStr(&line, "ChapterSign");
            }
            if(line.contains("HTMLFilter", Qt::CaseInsensitive))
            {
                m_removeHtml = getParamFromStr(&line, "HTMLFilter");
            }
            if(line.contains("Copyright", Qt::CaseInsensitive))
            {
                m_copyright = getParamFromStr(&line, "Copyright");
            }
            if(line.contains("VerseSign", Qt::CaseInsensitive))
            {
                m_verseSign = getParamFromStr(&line, "VerseSign");
            }
            if(line.contains("ChapterZero", Qt::CaseInsensitive))
            {
                const QString zero = getParamFromStr(&line, "ChapterZero");
                m_chapterZero  = zero.compare("Y", Qt::CaseInsensitive) == 0;
            }
            if(line.contains("Bible ", Qt::CaseInsensitive))
            {
                const QString bible = getParamFromStr(&line, "Bible");
                m_bibleType = bible.compare("Y", Qt::CaseInsensitive) == 0;

                //                if (m_typeModule != "Comments")
                //                    if (!m_bibleType)
                //                        m_typeModule = "Book";
            }
            if(line.contains("Apocrypha", Qt::CaseInsensitive))
            {
                const QString bible = getParamFromStr(&line, "Apocrypha");
                m_apocrypha = bible.compare("Y", Qt::CaseInsensitive) == 0;
            }
            if(line.contains("OldTestament", Qt::CaseInsensitive))
            {
                const QString bible = getParamFromStr(&line, "OldTestament");
                m_oldTestament = bible.compare("Y", Qt::CaseInsensitive) == 0;
            }
            if(line.contains("NewTestament", Qt::CaseInsensitive))
            {
                const QString bible = getParamFromStr(&line, "NewTestament");
                m_newTestament = bible.compare("Y", Qt::CaseInsensitive) == 0;
            }
            if(line.contains("Greek", Qt::CaseInsensitive))
            {
                const QString bible = getParamFromStr(&line, "Greek");
                m_greek = bible.compare("Y", Qt::CaseInsensitive) == 0;

            }

            if(line.contains("StrongNumbers", Qt::CaseInsensitive))
            {
                const QString zero = getParamFromStr(&line, "StrongNumbers");
                m_strongOption = zero.compare("Y", Qt::CaseInsensitive) == 0;
            }

            if(started == false && line.contains("BookQty", Qt::CaseInsensitive))
            {
                m_bookCount = getParamFromStr(&line, "BookQty");
                started = true;
            }
            if(started == true)
            {
                if(started2 == true)
                {
                    if(line.contains("ChapterQty", Qt::CaseInsensitive))
                    {
                        bookCount[i] = getParamFromStr(&line, "ChapterQty").toInt();
                        i++;
                        started2 = false;
                    }
                    else if(line.contains("FullName", Qt::CaseInsensitive))
                    {
                        bookFullName << getParamFromStr(&line, "FullName");

                    }
                    else if(line.contains("ShortName", Qt::CaseInsensitive))
                    {
                        const QString s = getParamFromStr(&line, "ShortName");
                        bookShortName.append(s.split(" "));

                    }
                }
                else if(line.contains("PathName", Qt::CaseInsensitive))
                {
                    count++;
                    started2 = true;
                    m_bookPath << getParamFromStr(&line, "PathName");

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

    //QString tab = "    ";

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

            //            line.remove("&nbsp;");
            line.replace("&nbsp;", " ");
//            line.remove(QRegExp("\\s\\d+"));
            line.remove("^&к").remove("&");
            out2 += line;
            if(chapterstarted == false && line.contains(m_chapterSign))
            {
                chapterstarted = true;
            }
            if(chapterstarted == true && line.contains(m_chapterSign))
            {
                ccount2++;
                out = line;
            }
            else if(chapterstarted == true)
            {
                out += line;
            }
        }
        //  chapter_tag is ANAME
        if (m_chapterSign != getEndOfTag(m_chapterSign))
            out2.remove(QRegExp("=\\d+>")); // hindi remove text =NUMBERCHAPTER>
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
        for(int j = 0; j < rawVerseList.size() - 1; j++)
        {
            // split removes versesign but it is needed
            QString verseText = rawVerseList.at(j + 1);


            //            // strong
            //            QRegExp rx("(\\d+)");
            //            verseText.replace(rx, "<sup>%1</sup>");
            //            int pos = 0;

            //            while ((pos = rx.indexIn(verseText, pos)) != -1)
            //            {
            ////                myDebug() << "yes";
            //                verseText.replace(rx.cap(1), "<sup>" + rx.cap(1) + "</sup>");
            //                pos += rx.matchedLength() + 11;
            //            }

            //            if (!verseText.contains(m_verseSign))
            //                verseText = "";
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

    QString t_pathToXmlFile =  QString(Config::configuration()->getAppDir() + GL_MODULE_PATH + "%1/" +
                                       m_moduleShortName + "/text" + GL_FORMAT_TEXT).arg(m_typeModule.toLower());
    //    myDebug() << t_pathToXmlFile;
    //    qDebug() << m_book.size();
    /// надо брать название книги, а не путь к ней
    m_bookList << m_bookPath.at(id);
    addBookToXML(t_pathToXmlFile, m_bookList.at(id), m_book);
    file.close();
    return 0;
}
//------------------------------------------------------------------------------
void BibleQuoteModule::setTypeModule(const QString f_type)
{
    m_typeModule = f_type;
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
