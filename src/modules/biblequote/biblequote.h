#ifndef __BIBLEQUOTE__H
#define __BIBLEQUOTE__H

#include "biblemodule.h"

#include <QString>

class BibleModule;

class BibleQuoteModule: public BibleModule
{
public:
    BibleQuoteModule(QString pathToModule);
    BibleQuoteModule();
    virtual ~BibleQuoteModule();

    MetaInfo readInfo(QFile &file);
    MetaInfo readInfo(const QString &fileName);

    void parseModule(QString pathToModule);

private:
    inline QString formatFromIni(QString input);
    QString indexPath() const;
    int m_moduleID;
    QString m_verseSign;
    QString m_chapterSign;
    QString m_removeHtml;
    QTextCodec *m_codec;
    QString m_uid;

////    Book m_book;
    QString m_modulePath;
    QString m_moduleName;
    QString m_moduleShortName;
    bool m_chapterZero;


    QStringList m_bookPath;
};

#endif // __BIBLEQUOTE__H
