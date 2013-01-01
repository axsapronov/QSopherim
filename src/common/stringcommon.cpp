#include "stringcommon.h"
#include "filecommon.h"

QString getBookNameFromStr(QString * str)
{
    QString r_str = *str;

    r_str.remove("<book name=\"")
            .remove("\">")
            .remove("    ");


    return r_str;
}
//------------------------------------------------------------------------------
QString getChapterNameFromStr(QString * str)
{
    QString r_str = *str;

    r_str.remove("<chapter number=\"")
            .remove("\">")
            .remove("    ");

    return r_str;
}
//------------------------------------------------------------------------------
QString getFileNameAbs(const QString file)
{
    QStringList list;
    list << file.split("/");
    QString str = list.last();
    list = str.split(".");
    str = list.first();
    return str;
}
//------------------------------------------------------------------------------
QString getFileName(const QString file)
{
    QStringList list;
    list << file.split("/");
    QString str = list.last();
    return str;
}
//------------------------------------------------------------------------------
QString absolutifyFileName(QString fn, QString path)
{
    QString afn;
    if (!fn.isEmpty()){
        QDir dir(path);
        afn = dir.cleanPath( dir.absoluteFilePath(fn) );
    }
    return afn;
}
//------------------------------------------------------------------------------
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
//-------------------------------------------------------------------------------
QStringList removeEmptyQStringFromQStringList(QStringList *list)
{
    QStringList listn;
    for(int i = 0; i < list->size(); i++)
    {
        if(!list->at(i).isEmpty()
                && list->at(i) != ""
                && list->at(i) != " ")
        {
            listn << list->at(i);
        }
    }
    //    myDebug() << listn;
    return listn;
}
//-------------------------------------------------------------------------------
QString getClearText(QString *text)
{
    QString clearText = *text;
    QRegExp rx("(<[^>]*>)");
    //    QRegExp rxp("(<[Pp].*?>)");
    //    QRegExp rxi("( [a-zA-Z:]+=)|(\"[^\"]*\")");
    //    QRegExp regP("(<[a-zA-Z]+) [^>]*");  // убирает атрибуты у p Тега
    //    // html атрибуты  (?:[\w]*) *= *"(?:(?:(?:(?:(?:\\\W)*\\\W)*[^"]*)\\\W)*[^"]*")
    //    // все теги </?\w+((\s+\w+(\s*=\s*(?:".*?"|'.*?'|[^'">\s]+))?)+\s*|\s*)/?>+(.*?|[\s\S]*?)+</?\w+((\s+\w+(\s*=\s*(?:".*?"|'.*?'|[^'">\s]+))?)+\s*|\s*)/?>
    //    </?\w+((\s+\w+(\s*=\s*(?:".*?"|'.*?'|[^'">\s]+))?)+\s*|\s*)/?>+(.*?|[\s\S]*?)+</?\w+((\s+\w+(\s*=\s*(?:".*?"|'.*?'|[^'">\s]+))?)+\s*|\s*)/?>
    clearText.remove(rx);
    QString tab = "    ";
    clearText.remove(tab);
    //    myDebug() << clearText;


    return clearText;

}
//-------------------------------------------------------------------------------
QString getEndOfTag(QString tag)
{
    QString newtag = tag;
    if(newtag[newtag.length() - 1] != QChar(62))
    {
        //        myDebug() << newtag[newtag.length()-1];
        newtag = newtag + "><";
    }
    return newtag;
}
//-------------------------------------------------------------------------------
QString getCoolLine(QString str)
{
    QString t_str = getClearText(&str);

    QStringList list;
    list << t_str.split("\n");
    list = removeEmptyQStringFromQStringList(&list);
    //    myDebug() << list;
    QString tab = "    ";
    t_str = "";
    for (int i = 0; i < list.size(); i++)
    {
        if (!list.at(i).isEmpty())
        {
            //            myDebug() << list.at(i);
            t_str.append(QString(tab + tab + list.at(i)));
        }
    }
    return t_str;
}
//-------------------------------------------------------------------------------
QString getNextWord(QString str, int pos)
{
    /// translate to hindi
    QString t_str = "";
    bool flag1 = false;
    bool flag2 = false;

    str.append(" ");

    if (pos == 0)
    {
        flag1 = true;
    }
    else
    {
        int j = 0;
        while (str.at(pos + j) != ' ' and str.length() >= pos + j )
        {
            j++;
        }
        pos += j + 1;
        flag1 = true;
    }

    for (int i = pos; i < str.length(); i++)
    {
        if (str.at(i) != ' ')
            t_str.append(str.at(i));

        if (str.at(i) == ' ' && flag1 && !flag2)
            flag2 = true;

        if (flag2 && flag1)
            break;
    }

    return t_str;
}
//-------------------------------------------------------------------------------
QString getShortLang(QString str)
{
    if (str == "Russian")
        return "ru";
    if (str == "English")
        return "en";
    if (str == "Deutch")
        return "de";
    if (str == "Français")
        return "fr";

    return "ru";
}
//-------------------------------------------------------------------------------
