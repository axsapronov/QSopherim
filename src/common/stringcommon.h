#ifndef __STRINGCOMMON__H
#define __STRINGCOMMON__H

#include <QString>

/**
 * @brief getBookNameFromStr
 * @param str
 * @return
 */
QString getBookNameFromStr(QString * str);

/**
 * @brief getChapterNameFromStr
 * @param str
 * @return
 */
QString getChapterNameFromStr(QString * str);

/**
  @function
  Retun name of file
  Example:
  /home/warmonger/develop/other/file.ru  return file
  @return name_file
  */
QString getFileNameAbs(const QString file);
/**
  @function
  Retun name of file
  Example:
  /home/warmonger/develop/other/file.ru  return file.ru
  @param filepath
  @return name_file
  */
QString getFileName(const QString file);
/**
  @function
  Returns absolute file path
  @param filepath
  @param folder
  @return filename
  */
QString absolutifyFileName(QString fn, QString path);
/**
  @function
  Hindi function for remove spaces
  dont use QString::simplified()
  used while :)
  @param text
  */
QString removeSpaces(QString str);
/**
 * @brief removeEmptyQStringFromQStringList
 * @param list
 * @return
 */
QStringList removeEmptyQStringFromQStringList(QStringList *list);

/**
 * @brief getClearText
 * @param text
 * @return
 */
QString getClearText(QString *text);
/**
 * @brief getEndOfTag
 * @param tag
 * @return
 */
QString getEndOfTag(QString tag);
/**
 * @brief getCoolLine
 * @param str
 * @return
 */
QString getCoolLine(QString str);
/**
 * @brief getNextWord
 * @param str
 * @param pos
 * @return
 */
QString getNextWord(QString str, int pos);
/**
 * @brief getShortLang
 * @param str
 * @return
 */
QString getShortLang(QString str);


#endif // __STRINGCOMMON__H
