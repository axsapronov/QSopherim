#include "strongcommon.h"
#include "filecommon.h"
#include "stringcommon.h"

#include "config.h"


//-------------------------------------------------------------------------------
QVector<StrongList> getListStrongs(QString pathToFile)
{
    QVector<StrongList> list;

    //QXmlStreamReader xmlReader;
    //xmlReader.addData(getTextFromHtmlFile(pathToFile));
//    while(!xmlReader.atEnd())
//    {
//        if(xmlReader.isStartElement())
//        {
//            StrongList t_list;
//            QXmlStreamAttributes attrs = xmlReader.attributes();
//            if (xmlReader.name().toString() == "strong")
//            {
//                t_list.number = attrs.value("number").toString().toInt();
//                QString str = xmlReader.readElementText();
//                str.remove("    ");
//                t_list.text = str;
//            }
//            list.push_back(t_list);
//        }
//        xmlReader.readNext();
//    }


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
        }
        list.push_back(t_strong);
    }
    return list;
}
//-------------------------------------------------------------------------------
void createListStrongs(QString f_path)
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
    writeXmlStrongFile(&strong);
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
            ///    <strong number='value'> text </strong>
            StrongList t_list = strong->value(i);
            ts << tab
               << "<strong number=\""
               << t_list.number
               << "\">"
               << t_list.text
               << tab << "</strong>"
               << endl;
        }
        ts << "</xml>" << endl;
    }
}
//-------------------------------------------------------------------------------
void writeXmlStrongFile(QHash<int, StrongList> *strong)
{
    QString path;
    path = Config::configuration()->getStrongDir() + "strong";

    do
    {
        path.append("0");
    } while ( QFile(path + ".xml" ).exists());
    path.append(".xml");

    QFile file(path);
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
            ///    <strong number='value'> text </strong>
            StrongList t_list = strong->value(i);
            ts << tab
               << "<strong number=\""
               << t_list.number
               << "\">"
               << t_list.text
               << tab << "</strong>"
               << endl;
        }
        ts << "</xml>" << endl;
    }
}

