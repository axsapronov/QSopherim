#ifndef PROJECTQXMLHANDLER_H
#define PROJECTQXMLHANDLER_H

#include <QXmlDefaultHandler>
#include <QString>

class ProjectQXMLHandler : public QXmlDefaultHandler
{
public:
    explicit ProjectQXMLHandler();

    virtual bool startElement(const QString & namespaceURI,
                              const QString & localName,
                              const QString & qName,
                              const QXmlAttributes & atts );


public:

};

#endif // PROJECTQXMLHANDLER_H
