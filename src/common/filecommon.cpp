#include "filecommon.h"
#include "stringcommon.h"

#include "debughelper.h"


//------------------------------------------------------------------------------
QString getEncodingFromFile(QString file, QString language)
{
    QProcess pr;

#ifdef Q_OS_WIN
    pr.start("enca.exe -L " +language + " \""  + file + "\"");
#endif
#ifdef Q_OS_LINUX
    pr.start("enca -L " + language + " \""  + file + "\"");
#endif
    //    pr.start("pwd");

    QString encoding = "";
    if (pr.waitForFinished() == true)
    {
        QByteArray b = pr.readAll();
        encoding = QString(b);
    }
    if (encoding.indexOf("Universal transformation format 8 bits;") >= 0 ) encoding = "UTF-8";
    if (encoding.indexOf("Universal transformation format 16 bits;") >= 0 ) encoding = "UTF-16";
    if (encoding.indexOf("Universal transformation format 32 bits;") >= 0 ) encoding = "UTF-32";
    if (encoding.indexOf("Universal character set 2 bytes; UCS-2; BMP") >= 0) encoding = "UCS-2";
    if (encoding.indexOf("MS-Windows code page 1251") >= 0) encoding = "Windows-1251";
    if (encoding.indexOf("MS-Windows code page 1252") >= 0) encoding = "Windows-1252";
    if (encoding.indexOf("MS-Windows code page 1253") >= 0) encoding = "Windows-1253";
    if (encoding.indexOf("MS-Windows code page 1254") >= 0) encoding = "Windows-1254";
    if (encoding.indexOf("MS-Windows code page 1255") >= 0) encoding = "Windows-1255";
    if (encoding.indexOf("MS-Windows code page 1256") >= 0) encoding = "Windows-1256";
    if (encoding.indexOf("MS-Windows code page 1257") >= 0) encoding = "Windows-1257";
    if (encoding.indexOf("MS-Windows code page 1258") >= 0) encoding = "Windows-1258";
    if (encoding.indexOf("7bit ASCII characters") >= 0) encoding = "ASCII";
    if (encoding.indexOf("KOI8-R Cyrillic") >= 0) encoding = "KOI8-R";
    if (encoding.indexOf("KOI8-U Cyrillic") >= 0) encoding = "KOI8-U";
    if (encoding.indexOf("Unrecognized encoding") >= 0) encoding = "UTF-8";
    //    qDebug() << "encoding = " << encoding;
    return encoding;
}

//------------------------------------------------------------------------------
QTextCodec * getCodecOfEncoding(QString encoding)
{
    //    encoding = encoding.toUpper ();
    QTextCodec * codec = QTextCodec::codecForName("UTF-8");
    if (encoding.toUpper ()== "UTF-8")        codec = QTextCodec::codecForName("UTF-8");
    if (encoding.toUpper ()== "UTF-16")       codec = QTextCodec::codecForName("UTF-16");
    if (encoding.toUpper ()== "UTF-16BE")       codec = QTextCodec::codecForName("UTF-16BE");
    if (encoding.toUpper ()== "UTF-16LE")       codec = QTextCodec::codecForName("UTF-16LE");
    if (encoding.toUpper ()== "UTF-32")       codec = QTextCodec::codecForName("UTF-32");
    if (encoding.toUpper ()== "UTF-32BE")       codec = QTextCodec::codecForName("UTF-32BE");
    if (encoding.toUpper ()== "UTF-32LE")       codec = QTextCodec::codecForName("UTF-32LE");
    if (encoding == "Windows-1251") codec = QTextCodec::codecForName("Windows-1251");
    if (encoding == "Windows-1252") codec = QTextCodec::codecForName("Windows-1252");
    if (encoding == "Windows-1253") codec = QTextCodec::codecForName("Windows-1253");
    if (encoding == "Windows-1254") codec = QTextCodec::codecForName("Windows-1254");
    if (encoding == "Windows-1255") codec = QTextCodec::codecForName("Windows-1255");
    if (encoding == "Windows-1256") codec = QTextCodec::codecForName("Windows-1256");
    if (encoding == "Windows-1257") codec = QTextCodec::codecForName("Windows-1257");
    if (encoding == "Windows-1258") codec = QTextCodec::codecForName("Windows-1258");
    if (encoding.toUpper ()== "KOI8-R")       codec = QTextCodec::codecForName("KOI8-R");
    if (encoding.toUpper ()== "KOI8-U")       codec = QTextCodec::codecForName("KOI8-U");

    //        qDebug() << " encoding = " << encoding;
    return codec;
}
//------------------------------------------------------------------------------
QStringList getFillLang()
{
    QStringList items;
    items << QString ("rus")
          << QString ("eng")
          << QString ("ukr")
          << QString ("he-rus")
          << QString ("gr-rus")
          << QString ("he");
    return items;
}
//------------------------------------------------------------------------------
QStringList getFillType()
{
    //    Dictionary/Справочник
    //   Encyclopedia/Энциклопедия
    //   Glossary/Глоссарий
    //   Lexicon/Симфония
    //   Thesaurus/Тезаурус
    //   Vocabulary/Толковый
    //   Wordbook/Словарь
    QStringList items;
    items << QString::fromUtf8( ("Dictionary/Справочник"))
          << QString::fromUtf8( ("Encyclopedia/Энциклопедия"))
          << QString::fromUtf8( ("Glossary/Глоссарий"))
          << QString::fromUtf8( ("Lexicon/Симфония"))
          << QString::fromUtf8( ("Thesaurus/Тезаурус"))
          << QString::fromUtf8( ("Vocabulary/Толковый"))
          << QString::fromUtf8( ("Wordbook/Словарь"));
    return items;
}
//------------------------------------------------------------------------------
QStringList getListWord(QString filename)
{
    QStringList r_list;
    QXmlStreamReader xmlReader;
    xmlReader.addData(getTextFromHtmlFile(filename));

    while(!xmlReader.atEnd())
    {
        if(xmlReader.isStartElement())
        {
            QStringList sl;
            sl << xmlReader.name().toString();
            QXmlStreamAttributes attrs = xmlReader.attributes();
            //         myDebug() << attrs.value("name").toString();
            r_list.append(attrs.value("name").toString());
        }

        //        if (xmlReader.isEndElement())
        //        {

        //        }
        xmlReader.readNext();
    }
    r_list = removeEmptyQStringFromQStringList(&r_list);
    return r_list;
}

//------------------------------------------------------------------------------
bool createEmptyHtml(QString fileName, QString title, QString text)
{
    bool ret = true;
    QFile file(fileName);
    if (!file.exists())
    {
        //create file if it's not exist
        if (file.open(QIODevice::ReadWrite))
        {
            //try to open or create file
            QTextStream ts(&file);
            ts.setCodec("UTF-8");
            ts << "<html>\n<head>" << endl;
            ts << "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\" />" << endl;
            ts << "<title>" << title <<"</title>" << endl;
            ts << "</head>\n<body>\n" << text << "\n</body>\n</html>" << endl;
            file.close();
        }
        else
        {
            ret = false;
        }
    }
    return ret;
}
//------------------------------------------------------------------------------
bool createEmpty(QString fileName, QString text)
{
    bool ret = false;
    QFile file(fileName);
    if (!file.exists())
    {
        //create file if it's not exist
        if (file.open(QIODevice::ReadWrite))
        {
            //try to open or create file
            QTextStream ts(&file);
            ts.setCodec("UTF-8");
            ts << text;
            file.close();
            ret = true;
        }
        else
        {
            ret = false;
        }
    }
    return ret;
}
//------------------------------------------------------------------------------
bool createEmptyHtml(QString fileName, QString title)
{
    bool ret = true;
    QFile file(fileName);
    if (!file.exists())
    {
        //create file if it's not exist
        if (file.open(QIODevice::ReadWrite))
        {
            //try to open or create file
            QTextStream ts(&file);
            ts.setCodec("UTF-8");
            ts << "<html>\n<head>" << endl;
            ts << "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\" />" << endl;
            ts << "<title>" << title <<"</title>" << endl;
            ts << "</head>\n<body>\n</body></html>" << endl;
            file.close();
        }
        else
        {
            ret = false;
        }
    }
    return ret;
}
//------------------------------------------------------------------------------
void replaceStrInFile(QString filepath, QString old, QString newstr)
{
    QFile file(filepath);
    QString str;
    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);
        stream.setCodec(getCodecOfEncoding("UTF-8"));
        str = stream.readAll();
        str.replace(old, newstr);
    }
    else
    {
        qDebug() << "Error: not open file (replacestrinfile):" << filepath;
    }
    file.close();

    if(file.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&file);
        stream.setCodec(getCodecOfEncoding("UTF-8"));
        stream << str;
        file.close();
    }
    else
    {
        qDebug() << "Error: not open file (replacestrinfile write):" << filepath;
    }

}
//------------------------------------------------------------------------------
QString getTextFromHtmlFile(QString filePath)
{
    QString str = "";
    QFile file(filePath);
    //    qDebug() << filePath;
    file.close();
    if (file.exists())
    {
        if (file.open(QIODevice::ReadOnly))
        {
            QTextStream stream(&file);
            stream.setCodec(getCodecOfEncoding(getEncodingFromFile(filePath)));
            str = stream.readAll();
            //        //        qDebug() << "str = " << str;
            //        int body = QString("<body>").length();
            //        int posBegin = str.indexOf("<body>");

            //        int posEnd = str.indexOf("</body>");
            //        str = str.mid(posBegin + body,
            //                      posEnd - posBegin - body);
            file.close();
        }
        else
        {
            myDebug() << "Error: not open file(getTextFromHtmlFile):" << filePath;
        }
    }

    return str;
}
//------------------------------------------------------------------------------
QStringList getInfoFromFile(QString file_path)
{
    QStringList list;
    if(QFile::exists(file_path))
    {
        QString encoding = getEncodingFromFile(file_path);
        QFile file(file_path);
        QString str;
        QString info[7];
        if(file.open(QIODevice::ReadOnly))
        {
            QTextStream stream(&file);
            stream.setCodec(getCodecOfEncoding(encoding));
            do
            {
                str = stream.readLine();
                if (str.indexOf("<meta name=\"Author\"") != -1)
                    info[0] = getParamInfo(&str, "Author");
                if (str.indexOf("<meta name=\"Revision\"") != -1)
                    info[1] = getParamInfo(&str, "Revision");
                if (str.indexOf("<meta name=\"Language\"") != -1)
                    info[2] = getParamInfo(&str, "Language");
                if (str.indexOf("<meta name=\"Type\"") != -1)
                    info[3] = getParamInfo(&str, "Type");
                if (str.indexOf("<meta name=\"Description\"") != -1)
                    info[4] = getParamInfo(&str, "Description");
                if (str.indexOf("<meta name=\"Rights\"") != -1)
                    info[5] = getParamInfo(&str, "Rights");
                if (str.indexOf("<meta name=\"Numbering\"") != -1)
                    info[6] = getParamInfo(&str, "Numbering");
            } while(!stream.atEnd());
            file.close();

            for (int i = 0; i < 7; i++)
            {
                list << info[i];
            }
        }
        else
        {
            qDebug() << "Error: not open file for read(get info from file):"
                     << file_path;
        }
    }

    return list;
}
//------------------------------------------------------------------------------
QString getParamInfo(QString *inputstr, QString param)
{
    QString str = *inputstr;
    QString remove = "<meta name=\"" + param + "\" content=\"";
    str.remove(remove)
            .remove("\">");
    str = removeSpaces(str);

    if (str == "RU")
        str = "rus";

    if (str == "En")
        str = "eng";

    return str;
}
//-------------------------------------------------------------------------------
QString findPosWord(QString file, QString text)
{
    QString t_output_str = "";
    if(QFile::exists(file))
    {
        QString t_text = getTextFromHtmlFile(file);
        QStringList t_list = t_text.split("\n");

        QString t_find_text = text;
        bool flag = true;
        do
        {
            for (int i = 0; i < t_list.size(); i++)
            {
                if (QString(t_list.at(i)).indexOf(t_find_text) != -1)
                {
                    t_output_str = t_list.at(i);
                    flag = false;
                    break;
                }
            }
            t_find_text.remove(t_find_text.length() -1, 1);
        } while(flag and
                !t_find_text.isEmpty());
    }
    return t_output_str;
}
//------------------------------------------------------------------------------
bool createEmptyXML(QString fileName)
{
    bool ret = false;
    QFile file(fileName);
    if (!file.exists())
    {
        //create file if it's not exist
        if (file.open(QIODevice::ReadWrite))
        {
            //try to open or create file
            QTextStream ts(&file);
            ts.setCodec("UTF-8");
//            ts << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;
//            ts << "<!DOCTYPE xbel>" << endl;
//            ts << "<xbel version=\"1.0\">" << endl;
            ts << "<xml>" << endl;
//            ts << "</xml>" << endl;
            file.close();
            ret = true;
        }
        else
        {
            ret = false;
        }
    }
    return ret;
}
//------------------------------------------------------------------------------
bool addBookToXML(QString fileName, QString namebook, Book mbook)
{
    bool ret = false;
    //    myDebug() << getTextFromHtmlFile(fileName);
    //    myDebug() << "\n\n\n\n";
    QFile file(fileName);
    if (file.exists())
    {
        //create file if it's not exist
        if (file.open(QIODevice::Append))
        {
            //try to open or create file
            QString tab = "    ";
            QTextStream ts(&file);
            ts.setCodec(getCodecOfEncoding(getEncodingFromFile(fileName)));
            ts << tab << "<book name=\"" << namebook << "\">" << endl;
            for (int i = 0; i < mbook.size(); i++)
            {

                ts << tab << tab << "<chapter number=\"" << i + 1
                   << "\">" << endl;
                for (int j = 0; j < mbook.getChapter(i).verseCount(); j++)
                {
                    QString text = mbook.getChapter(i).data().value(j).data();

                    QString str = getClearText(&text);
                    ts << tab << tab << tab << str;
                }

                ts  << tab << tab << "</chapter>" << endl;
            }

            ts << tab << "</book>" << endl;
            file.close();
            ret = true;
        }
        else
        {
            ret = false;
        }
    }
    return ret;
}
//------------------------------------------------------------------------------
bool endXML(QString fileName)
{
    bool ret = false;
    QFile file(fileName);
    if (file.exists())
    {
        //create file if it's not exist
        if (file.open(QIODevice::Append))
        {
            //try to open or create file
            QTextStream ts(&file);
            ts.setCodec("UTF-8");
//            ts << "</xbel>" << endl;
            ts << "</xml>" << endl;
            file.close();
            ret = true;
        }
        else
        {
            ret = false;
        }
    }
    return ret;
}
//------------------------------------------------------------------------------
QSopherimModuleInfo getModuleInfo(QString fileName)
{

    QSopherimModuleInfo list;
    list.moduleName = getParamModule(fileName, "ModuleName");
    list.moduleShortName = getParamModule(fileName, "ModuleShortName");
    //    list.append(getParamModule(fileName, "ModuleLanguage"));
    list.bookValue = getParamModule(fileName, "BooksValue").toInt();
    list.modulePath = getParamModule(fileName, "PathToModule");
    list.moduleType = getParamModule(fileName, "TypeModule");

    list.bookList = getBookList(fileName);

    list.numberOfChaptersInBook = getNumberOfChaptersInBook(fileName);
    //    myDebug() << list.numberOfChaptersInBook.size();
    //    myDebug() << list.bookList.size();
    //    list.append(getParamModule(fileName, "ModuleShortName"));

    return list;
}
//------------------------------------------------------------------------------
QString getParamModule(QString filename, QString param)
{
    // translate to hindi
    QString str = "";
    QString line;
    QString parama = param + " = ";
    QFile file(filename);
    file.close();
    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream stream( &file );
        do {
            line = stream.readLine();
            if (line.indexOf(parama) >= 0)
            {
                str = line.remove(parama);
            }
        } while (str.isEmpty() and !line.isNull());
        file.close();
    }
    else
    {
        qDebug() << "Error";
    }
    return str;
}
//------------------------------------------------------------------------------
QStringList getBookList(QString file)
{
    QStringList bookList;
    QString param = "BookList";
    // translate to hindi
    QString str = getParamModule(file, param);
    bookList << str.split(":");
    bookList = removeEmptyQStringFromQStringList(&bookList);
    return bookList;
}
//------------------------------------------------------------------------------
QHash<QString, int> getNumberOfChaptersInBook(QString filename)
{

    QStringList bookList;
    QString param = "NumberChapter";
    //     translate to hindi
    QString str = getParamModule(filename, param);
    bookList << str.split("::");
    bookList = removeEmptyQStringFromQStringList(&bookList);
    QHash<QString, int> list;

    for (int i = 0; i < bookList.size(); i++)
    {
        QStringList test;
        test << bookList.at(i).split("^");
        //        myDebug() <<  bookList.at(i) << test.size();

        list[test.at(0)] = test.at(1).toInt();
    }
    return list;
}


//-------------------------------------------------------------------------------
QStringList getListModulesFromPath(QString path, QString format)
{
    QStringList files = recursiveFind(path);
    QStringList list;
    for(int i = 0; i < files.size(); i++)
    {
        if(files.at(i).indexOf(format) >= 0
                or files.at(i).indexOf(format.toUpper()) >= 0)
        {
            list << files.at(i);
        }
    }
    return list;
}
//-------------------------------------------------------------------------------
QStringList recursiveFind(QString directory)
{
    //// подумать, нужен ли чистый рекурсивный поиск
    //// если нет, то сюда вставить обработку getModuleFilesList
    QStringList list;
    QDirIterator iterator (directory, QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);
    while(iterator.hasNext())
    {
        iterator.next();
        list << iterator.fileInfo().absoluteFilePath();
    }
    return list;
}
//-------------------------------------------------------------------------------
QHash<int, QString> getNoteOfParams(QString curPath,
                                    QString curModule,
                                    QString curBook,
                                    QString curChapter,
                                    QString firstVerse)
{
    QHash<int, QString> hash;
    Q_UNUSED (firstVerse)

    QString text = getTextFromHtmlFile(curPath);
    QStringList list;
    int count = 0;
    text.remove("<xml>").remove("</xml>");

    list << text.split("</note>");
    list = removeEmptyQStringFromQStringList(&list);
    for (int i = 0; i < list.size(); i++)
    {
        QString str1 = "module=\"" + curModule + "\"";
        QString str2 = "book=\"" + curBook + "\"";
        QString str3 = "chapter=\"" + curChapter + "\"";
        QString line = list.at(i);
        if (line.contains(str1) &&
                line.contains(str2) &&
                line.contains(str3) &&
                getVerseNumberFromNote(&line) == firstVerse)
        {
            //            QString text = "<note " + str1 + str2 + str3;
            //            hash[count] = strat.remove(text).remove("</note>");
//            myDebug() << getVerseBeginNumberFromNote(&line) << getVerseEndNumberFromNote(&line);

            /// remove tag before text
            int pos = line.indexOf(">");
            line.remove(0, pos + 1);
            hash[count] = line;
            count++;
        }
    }
    return hash;
}

//-------------------------------------------------------------------------------
QString getVerseNumberFromNote(QString* line)
{

    QString str = *line;
    QString t_str ="verse=\"";
    int pos = str.indexOf(t_str);
    int pos2 = str.indexOf("\"", pos + t_str.length());

    str = str.mid(pos + t_str.length(), pos2  - pos - t_str.length());
    return str;
}

//-------------------------------------------------------------------------------
QString getDescriptionForWordFromDict(QString t_pathToFile, QString word)
{
    QXmlStreamReader xmlReader;
    QString r_str;
    xmlReader.addData(getTextFromHtmlFile(t_pathToFile));
    while(!xmlReader.atEnd())
    {
        if(xmlReader.isStartElement())
        {
            QStringList sl;
            sl << xmlReader.name().toString();
            QXmlStreamAttributes attrs = xmlReader.attributes();
            if (attrs.value("name") == word)
            {
                r_str = xmlReader.readElementText();
                r_str.remove("    ");
                break;
            }
        }
//        if (xmlReader.isEndElement())
//        {

//        }
        xmlReader.readNext();
    }
    return r_str;
}
//-------------------------------------------------------------------------------
QStringList getBookmarks(QString pathToFile)
{
    QXmlStreamReader xmlReader;
//    QString r_str;
    QStringList r_list;
    xmlReader.addData(getTextFromHtmlFile(pathToFile));
    while(!xmlReader.atEnd())
    {
        if(xmlReader.isStartElement())
        {
            QStringList sl;
            sl << xmlReader.name().toString();
            QXmlStreamAttributes attrs = xmlReader.attributes();
            r_list  << attrs.value("name").toString();
        }
//        if (xmlReader.isEndElement())
//        {

//        }
        xmlReader.readNext();
    }
    r_list = removeEmptyQStringFromQStringList(&r_list);
    return r_list;
}
//-------------------------------------------------------------------------------
void addToListBookModule(const QString f_shortName)
{
    myDebug() << "apend book module " << f_shortName;
}
//-------------------------------------------------------------------------------
void addToListBibleModule(const QString f_shortName)
{
    myDebug() << "apend bible module " << f_shortName;
}
//-------------------------------------------------------------------------------
QString getModuleNameFromIni(const QString f_filePath)
{
    QString r_moduleName;
    if(QFile::exists(f_filePath))
    {
        QString encoding = getEncodingFromFile(f_filePath);
        QFile file(f_filePath);
        QString str;
        if(file.open(QIODevice::ReadOnly))
        {
            QTextStream stream(&file);
            stream.setCodec(getCodecOfEncoding(encoding));
            do
            {
                str = stream.readLine();
                if(str.contains("ModuleName", Qt::CaseInsensitive))
                {
                    r_moduleName = getParamFromStr(&str, "ModuleName");
                }

            } while(!stream.atEnd());
            file.close();
        }
        else
        {
            qDebug() << "Error: not open file for read(get info from file):"
                     << f_filePath;
        }
    }
    return r_moduleName;
}
//-------------------------------------------------------------------------------
