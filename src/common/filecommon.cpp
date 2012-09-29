#include "filecommon.h"

#include "debughelper.h"


///----------------------------------------------------------------------------
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
///----------------------------------------------------------------------------
QString getFileNameAbs(const QString file)
{
    QStringList list;
    list << file.split("/");
    QString str = list.last();
    list = str.split(".");
    str = list.first();
    return str;
}
///----------------------------------------------------------------------------
QString getFileName(const QString file)
{
    QStringList list;
    list << file.split("/");
    QString str = list.last();
    return str;
}
///----------------------------------------------------------------------------
QString absolutifyFileName(QString fn, QString path)
{
    QString afn;
    if (!fn.isEmpty()){
        QDir dir(path);
        afn = dir.cleanPath( dir.absoluteFilePath(fn) );
    }
    return afn;
}
///----------------------------------------------------------------------------
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
///----------------------------------------------------------------------------
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
///----------------------------------------------------------------------------
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
///----------------------------------------------------------------------------
QStringList getListWord(QString filename)
{
    QStringList list;
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream streamInput(&file);
        streamInput.setCodec(getCodecOfEncoding(getEncodingFromFile(filename)));
        QString line;

        /// split bad string
        do
        {
            line = streamInput.readLine() + "\r\n";
        }
        while (line.indexOf("<h4>") == -1
               and !streamInput.atEnd());
        int count;
        QString str, str2;
        do
        {
            /// edit to standart
            /// replace tag to standart
            //            line.replace(tagBegin, "<h4>");
            //            line.replace(tagEnd, "</h4>");

            int h4 = QString("<h4>").length();

            int posH4_1 = line.indexOf("<h4>");
            int posH4_2 = line.indexOf("<h4>", posH4_1);

            /// split text  mid <h4> and <h4>
            /// if the text in multiple lines
            while ((posH4_2 == -1 or posH4_1 == posH4_2)
                   and !streamInput.atEnd())
            {
                line.append(streamInput.readLine() + "\r\n");
                posH4_2 = line.indexOf("<h4>", posH4_1 + h4);
            }
            str = line.mid(posH4_1,
                           posH4_2 - posH4_1);

            int posBegin = str.indexOf("<h4>");
            int posEnd = str.indexOf("</h4>");
            str2 = line.mid(posBegin + QString("<h4>").length(),
                            posEnd - posBegin - QString("<h4>").length());
            if (!str.isEmpty())
            {
                //                streamDict << str;
            }

            if (!str2.isEmpty())
            {
                int count2;
                if (count %2 != 0)
                    count++;

                count2 = count;
                //                streamIdx << str2 << "\r\n" << QString::number(count2) + "\r\n";
            }
            count += (str.length()) *2;
            list << QString(str).remove("\r\n");
            line.remove(str);
            //            QString sttt = str2 + "<|>" + str;

            line.append(streamInput.readLine() + "\r\n");
            line.remove("</body>")
                    .remove("</html>")
                    .remove("<body>");
        } while (!streamInput.atEnd());
        file.close();
    }
    else
    {
        qDebug() << "Error: not open file for read word list:" << filename;
    }
    return list;
}

///----------------------------------------------------------------------------
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
///----------------------------------------------------------------------------
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
///----------------------------------------------------------------------------
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
///----------------------------------------------------------------------------
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
///----------------------------------------------------------------------------
QString getTextFromHtmlFile(QString filePath)
{
    QString str = "";
    QFile file(filePath);
    //    qDebug() << filePath;
    file.close();
    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);
        QString encoding = getEncodingFromFile(filePath);
        stream.setCodec(getCodecOfEncoding(encoding));
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
        qDebug() << "Error: not open file(getTextFromHtmlFile):" << filePath;
    }

    return str;
}
///----------------------------------------------------------------------------
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
///----------------------------------------------------------------------------
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

///----------------------------------------------------------------------------
QString removeSpaces(QString str)
{
    /// translate to hindi
    /// bad work
    /// str.simplified()
    /// remove after word
    bool flag = true;
    int i = 0;
    do
    {
        if(str.at(i) == ' ')
        {
            str.remove(i,1);
            i--;
        }
        else
        {
            flag = false;
        }

        i++;
    } while(flag);

    /// remove before word
    i = 1;
    flag = true;
    do
    {
        if(str.at(str.length()-i) == ' ')
        {
            str.remove(str.length()-i,1);
            i++;
        }
        else
        {
            flag = false;
        }

        i--;
    } while(flag);

    return str;
}
///----------------------------------------------------------------------------
void deleteWordFromDict(QString filePath, QString word, QString description)
{
    QString text = getTextFromHtmlFile(filePath);
    text.remove(QString("<h4>%1</h4>").arg(word))
            .remove(description);
    QFile::remove(filePath);
    createEmpty(filePath, text);
}
///----------------------------------------------------------------------------
void addWordToDict(QString filePath, QString word, QString description)
{
    QString text = getTextFromHtmlFile(filePath);

    QString oldPos = findPosWord(filePath, word);
    QString newText = QString("<h4>%1</h4> %2")
            .arg(word)
            .arg(description) + "\r\n" + oldPos;
    text.replace(oldPos, newText);

    QFile::remove(filePath);
    createEmpty(filePath, text);
}
///----------------------------------------------------------------------------
QString getDescriptionFromHtmlFile(QString filePath)
{
    QString str = "";
    QFile file(filePath);
    //    qDebug() << filePath;
    file.close();
    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);
        QString encoding = getEncodingFromFile(filePath);
        stream.setCodec(getCodecOfEncoding(encoding));
        str = stream.readAll();
        //        qDebug() << "str = " << str;
        int body = QString("<body>").length();
        int posBegin = str.indexOf("<body>");

        int posEnd = str.indexOf("</body>");
        str = str.mid(posBegin + body,
                      posEnd - posBegin - body);
        str.remove("\n")
                .remove("\r");
        file.close();
    }
    else
    {
        qDebug() << "Error: not open file(getTextFromHtmlFile):" << filePath;
    }

    return str;
}
///----------------------------------------------------------------------------
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
///----------------------------------------------------------------------------
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
            ts << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;
            ts << "<!DOCTYPE xbel>" << endl;
            ts << "<xbel version=\"1.0\">" << endl;
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
///----------------------------------------------------------------------------
bool addBookToXML(QString fileName, QString namebook, QStringList textchapter)
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

            //                  <?xml version="1.0" encoding="UTF-8"?>
            //                  <!DOCTYPE xbel>
            //                  <xbel version="1.0">
            //                      <book name="Name of book" shortname="ShortName">
            //                          <chapter number="1">Text _\/_ (br) </chapter>
            //                          <chapter number="*"> text</chapter>
            //                      </book>
            //                      <book name="Name of book" shortname="ShortName">
            //                          <chapter ...?>
            //                       </book>
            //                  </xbel>
            ts << tab << "<book name=\"" << namebook << "\">" << endl;
            for (int i = 0; i < textchapter.size(); i++)
            {
                ts << tab << tab << "<chapter number=\"" << i
                   << "\">" << textchapter.at(i) << "</chapter>"
                   << endl;
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
///----------------------------------------------------------------------------
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
            ts << "</xbel>" << endl;
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
///----------------------------------------------------------------------------
