#ifndef __STRONGCOMMON__H
#define __STRONGCOMMON__H

#include <QVector>
#include <QString>
#include <QHash>
#include <QStringList>
#include <QXmlStreamReader>

typedef struct StrongList
{
    int number;
    QString text;
} StrongList;



/**
 * @brief getListStrongs
 * @param path
 * @return
 */
QVector<StrongList> getListStrongs(QString path);
/**
 * @brief createListStrongs
 * @param path
 */
void createListStrongs(QString f_path);
/**
 * @brief createListStrongs
 * @param path
 */
void createListStrongs(QString f_path, QString f_nameStrong);
/**
 * @brief writeXmlStrongFile
 * @param strong
 */
void writeXmlStrongFile(QHash<int, StrongList> *strong, QString f_path);
/**
 * @brief writeXmlStrongFile
 * @param strong
 */
void writeXmlStrongFile(QHash<int, StrongList> *strong);


#endif
