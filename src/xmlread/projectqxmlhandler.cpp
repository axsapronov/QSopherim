#include "projectqxmlhandler.h"
#include "debughelper.h"

ProjectQXMLHandler::ProjectQXMLHandler()
{

}
//------------------------------------------------------------------------------
bool ProjectQXMLHandler::startElement(const QString & namespaceURI,
                                      const QString & localName,
                                      const QString & qName,
                                      const QXmlAttributes & atts )
{
    myDebug() << "Read Start Tag : " << localName << endl;
    myDebug() << "Tag Attributes: " << endl;


    for(int index = 0 ; index < atts.length(); index++)
    {
        myDebug() << atts.type(index) << "="
                  << atts.value(index) << endl;
    }

    myDebug() << "------------------------" << endl;
    return true;
};
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
