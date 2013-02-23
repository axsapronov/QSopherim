#include "strongcommon.h"
#include "filecommon.h"
#include "stringcommon.h"

#include "config.h"

#include "debughelper.h"


//-------------------------------------------------------------------------------
void getMapStrongs(const QString pathToFile, QMap<int, StrongList> &r_map)
{
    QString t_text = getTextFromHtmlFile(pathToFile);
    QStringList t_list = t_text.split("\n");

    for (int i = 0; i < t_list.size(); i++)
    {
        StrongList t_strong;
        if (t_list.at(i).contains("strong"))
        {
            int pos1 = t_list.at(i).indexOf("number='") + 8; // 8 length
            int pos2 = t_list.at(i).indexOf("'", pos1);
            t_strong.number = t_list.at(i).mid(pos1, pos2 - pos1).toInt();

            QString str = t_list.at(i).mid(pos2 + 3, t_list.at(i).length() - pos2 - 3 - 9 ); // 9 - length </strong>
            str.remove("    ");
            t_strong.text = str;
            r_map[t_strong.number] = t_strong;
        }
    }
}
//-------------------------------------------------------------------------------
void createListStrongs(QString f_path, QString f_nameStrong)
{
    QString text = getTextFromHtmlFile(f_path);
    QStringList list;
    QHash<int, StrongList> strong;
    list = text.split("<h4>");

    for (int i = 0; i < list.size() - 1; i++)
    {
        QString line = list.at(i + 1);
        QStringList t_strong;
        t_strong = line.split("</h4>");
        StrongList t_list;
        t_list.number = t_strong.at(0).toInt();
        t_list.text = getCoolLine(t_strong.at(1));
        strong[i] = t_list;
    }

    QString r_path = Config::configuration()->getStrongDir() + f_nameStrong + ".xml";
    writeXmlStrongFile(&strong, r_path);
}
//-------------------------------------------------------------------------------
void writeXmlStrongFile(QHash<int, StrongList> *strong, QString f_path)
{
    QFile file(f_path);
    if (file.exists())
        file.remove();

    if(file.open(QIODevice::WriteOnly))
    {
        QString tab = "    ";
        QTextStream ts(&file);
        ts.setCodec(getCodecOfEncoding("UTF-8"));
        ts << "<xml>" << endl;

        for (int i = 0; i < strong->size(); i++)
        {
            //    <strong number='value'> text </strong>
            StrongList t_list = strong->value(i);
            ts << tab
               << "<strong number=\'"
               << QString("%1").arg(t_list.number, 5, 10, QChar('0'))
               << "\'>"
               << t_list.text.remove("    ")
               << "</strong>"
               << endl;
        }
        ts << "</xml>" << endl;
    }
}
//-------------------------------------------------------------------------------
QString getTypeStrong()
{
    QString r_str = "";

    QString t_lastBook = Config::configuration()->getLastBook();
    int t_numberBook = getNumberOfBook(t_lastBook);

    if (t_numberBook <= 66 )
        r_str = "Hebrew";

    if (t_numberBook > 66 and t_numberBook <= 77)
        r_str = "Greek";

    return r_str;
}
//-------------------------------------------------------------------------------
int getNumberOfBook(const QString f_book)
{
    int r_number = 1;
    QString t_name = "numberBook.txt";

    QString t_text = getTextFromHtmlFile(Config::configuration()->getStrongDir() + t_name);
    QStringList t_list;
    t_list << t_text.split("\n");

    int i = 0;
    QString t_str;
    bool flag = false;
    do
    {
        t_str = getParamFromStr(&t_list.at(i), f_book);
        if (t_str != t_list.at(i))
        {
            r_number = t_str.toInt();
        }

        i++;
    } while (!flag and i < t_list.size() );

    return r_number;
}
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
