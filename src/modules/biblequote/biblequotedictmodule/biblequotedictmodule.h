#ifndef BIBLEQUOTEDICTMODULE_H
#define BIBLEQUOTEDICTMODULE_H

#include "biblemodule.h"

#include "filecommon.h"

class BibleQuoteDictModule : public BibleModule
{
    Q_OBJECT
public:
    BibleQuoteDictModule(QString pathToModule);
    BibleQuoteDictModule();

    void parseModule(QString pathToModule);
signals:
    void createFolderForDict(QString);

public slots:

private:
    QString m_author;
    QString m_copyright;
    QString m_revision;
    QString m_language;
    QString m_description;
    QString m_numbering;
    QString m_type;
    QString m_path;
    QString m_name;

    /**
     * @brief createDictFile
     * @function for create projectQ dict module from bible qt module
     * @param path
     */
    void createDictFile(QString path);
    /**
     * @brief writeDictFile
     * @function for create file dict module
     * @param wordList
     */
    void writeDictFile(QHash<int, WordDictList>* wordList);

    /**
     * @brief createIniFile
     * create folder for dict module
     * @return
     */
    bool createIniFile();
};

#endif // BIBLEQUOTEDICTMODULE_H
