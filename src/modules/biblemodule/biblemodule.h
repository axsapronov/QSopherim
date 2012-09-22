#ifndef __BIBLEMODULE__H
#define __BIBLEMODULE__H

#include <QString>
#include <QSharedPointer>
#include <QFile>

#include "metainfo.h"
class BibleModule
{
public:
    BibleModule();
    virtual ~BibleModule();

    virtual int loadBibleData(const int moduleID, const QString &path);
    virtual MetaInfo readInfo(QFile &file);

//    virtual TextRange rawTextRange(int bookID, int chapterID, int startVerse, int endVerse);
    virtual std::pair<int, int> minMaxVerse(int bookID, int chapterID);

//    virtual void search(const SearchQuery &query, SearchResult *res) const;
    virtual bool hasIndex() const;
    virtual void buildIndex();

    virtual int moduleID() const;
    virtual QString modulePath() const;
    virtual QString moduleName(bool preferShortName = false) const;

//    virtual QSharedPointer<Versification> versification() const;
    virtual QString uid() const;
    virtual void clear();
    virtual void clearData();

    virtual void parseModule(QString pathToModule);
signals:
    void createFolderForModule(QString shortname);
protected:
//    QSharedPointer<Versification> m_versification;


};

#endif // __BIBLEMODULE__H
