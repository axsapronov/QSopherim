#include "stringcommon.h"


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
