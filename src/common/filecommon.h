#ifndef __FILECOMMON__H
#define __FILECOMMON__H



#include <QString>
#include <QProcess>
#include <QDir>
#include <QTextCodec>

#include <QHash>
#include <QDirIterator>
#include <QXmlStreamReader>

#include <QStringList>

#include <QDebug>
#include "book.h"
#include "qsopherimmodule.h" /// QSopherimModuleInfo



typedef struct WordDictList
{
    QString word;
    QString text;
} WordDictList;
/**
  \brief
  @function
  Auto detect encoding file
  @param filepath  QString of file path
  @param language  QString of language, default = russian
  @return encoding  QString encoding
  */
QString getEncodingFromFile(QString file, QString language="russian");

/**
  @function
  Return codec from string
  @param encoding(String)
  @return encoding(Codec)
   */
QTextCodec* getCodecOfEncoding(QString encoding); // получает строку с названием кодировки и возвращает кодес с этй кодировкой ( написана для уменьшения дублирования кода)
/**
  @fucnction
  Return list of lang
  @retun list
  */
QStringList getFillLang();
/**
    @fucnction
    Return list of type dict
    @return list
    */
QStringList getFillType();
/**
  @function
  Return list words from dict
  @param path_to_file
  @return list_of_words
  */
QStringList getListWord(QString);


/**
  @function
  Create empty html file,
  @param file_path
  @param title
  @return bool
  */
bool createEmptyHtml(QString fileName, QString title);

/**
  @function
  Create empty html file with text,
  @param file_path
  @param title
  @param text
  @return bool
  */
bool createEmptyHtml(QString fileName, QString title, QString text);
/**
  @function
  Create empty file with text,
  @param file_path
  @param text
  @return bool
  */
bool createEmpty(QString fileName, QString text);
/**
  @function
  Retrun text from <body> </body>
  @param file_path
  @return text
  */
QString getTextFromHtmlFile(QString fileName);
/**
  @function
  Retrurn description from <body> </body>
  @param file_path
  @return text
  */
QString getDescriptionFromHtmlFile(QString fileName);
/**
  @function
  Replace text in file
  @param file_path
  @param old_text
  @param new_text
  */
void replaceStrInFile(QString filepath, QString old, QString newstr);
/**
  @function
  Return info from dict input file
  Return list(QStringList)
  @param file_path
  @return info
  */
QStringList getInfoFromFile(QString file_path);
/**
  @function
  Return param from dict file
  Example:
  Input <meta name="Author" content="TEXT"> , Author
  Output TEXT
  @param str
  @param param
  @return param
  */
QString getParamInfo(QString *inputstr, QString param);
/**
  @function
  Function for find string
  @param file
  @param text_to_find
  @return str_to_pos
  */
QString findPosWord(QString file, QString text);
/**
  \brief
  @function
  Create empty xml file.
  @param file_path
  @return bool
  */
bool createEmptyXML(QString fileName);
/**
 * @brief addBookToXML
 * @function
 * Function for add book to xml
 * @param fileName
 * @param namebook
 * @param mbook
 * @return
 */
bool addBookToXML(QString fileName, QString namebook, Book mbook);
/**
 * @brief endXML
 * @param fileName
 * @return
 */
bool endXML(QString fileName);
/**
 * @brief getModuleInfo
 * @param fileName
 * @return
 */
QSopherimModuleInfo getModuleInfo(QString fileName);
/**
 * @brief getParamModule
 * @param filename
 * @param param
 * @return
 */
QString getParamModule(QString filename, QString param); // возвращает параметр из файла. Вид файла    "PARAM = VALUE"
/**
 * @brief getBookList
 * @param filaPath
 * @return
 */
QStringList getBookList(QString filaPath);
/**
 * @brief getNumberOfChaptersInBook
 * @param filename
 * @return
 */
QHash<QString, int> getNumberOfChaptersInBook(QString filename);

/**
 * @brief getListModulesFromPath
 * @param path
 * @param format
 * @return
 */
QStringList getListModulesFromPath(QString path, QString format=".ini");
/**
 * @brief recursiveFind
 * @param directory
 * @return
 */
QStringList recursiveFind(QString directory);

/**
 * @brief getNoteOfParams
 * @param curPath
 * @param curModule
 * @param curBook
 * @param curChapter
 * @param firstVerse
 * @return
 */
QHash<int, QString> getNoteOfParams(QString curPath,
                                    QString curModule,
                                    QString curBook,
                                    QString curChapter,
                                    QString firstVerse);
/**
 * @brief getVerseNumberFromNote
 * @param line
 * @return
 */
QString getVerseNumberFromNote(QString* line);

/**
 * @brief getDescriptionForWordFromDict
 * @param pathToFile
 * @param word
 * @return
 */
QString getDescriptionForWordFromDict(QString pathToFile, QString word);

/**
 * @brief getBookmarks
 * return list of bookmarks from file
 * @param pathToFile
 * @return
 */
QStringList getBookmarks(QString pathToFile);
#endif // __FILECOMMON__H
