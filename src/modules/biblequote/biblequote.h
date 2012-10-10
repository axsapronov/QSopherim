#ifndef __BIBLEQUOTE__H
#define __BIBLEQUOTE__H

#include "biblemodule.h"


#include "src/core/verse/chapter.h"
#include "book.h"

#include <QString>
#include <QObject>

class BibleModule;


class BibleQuoteModule: public BibleModule
{
    Q_OBJECT

public:
    BibleQuoteModule(QString pathToModule);
    BibleQuoteModule();
    ~BibleQuoteModule();

    MetaInfo readInfo(QFile &file);
    MetaInfo readInfo(const QString &fileName);
    int loadBibleData(const int moduleID, const QString &path);
    int readBook(const int id);

    void parseModule(QString pathToModule);

    int moduleID() const;
    QString modulePath() const;
    QString moduleName(bool preferShortName = false) const;
    QString uid() const;

signals:
    void createFolderForModule(QString shortname);

private:
    inline QString formatFromIni(QString input);
    QString indexPath() const;
    int m_moduleID;
    QString m_verseSign;
    QString m_bookCount;
    QString m_chapterSign;
    QMap<int, int> m_bookCountSize;
    QString m_removeHtml;
    QTextCodec *m_codec;
    QString m_uid;

    Book m_book;
    QStringList m_bookList;
    QString m_modulePath;
    QString m_moduleName;
    QString m_moduleShortName;
    bool m_chapterZero;

    QStringList m_bookPath;

    bool createIniFile(MetaInfo info);
    bool createBookFiles(QString pathToFiles);
};

#endif // __BIBLEQUOTE__H
