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
 * @brief getMapStrongs
 * @param pathToFile
 * @param r_map
 */
void getMapStrongs(QString pathToFile, QMap<int, StrongList>& r_map);

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

QString getTypeStrong();

int getNumberOfBook(const QString f_book);


#endif
