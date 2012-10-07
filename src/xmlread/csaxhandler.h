#ifndef CSAXHANDLER_H
#define CSAXHANDLER_H

#include <QXmlDefaultHandler>
#include <QStack>

//----------------------------------------------------------------------
// обработчики для SAX-парсера
//----------------------------------------------------------------------

class CNode;

class CSaxHandler : public QXmlDefaultHandler
{
private:
    CNode* doc;               // указатель на объект
    QStack<CNode*> nodeStack; // стек обрабатываемых элементов
    QString textElement;      // буфер содержимого текстового элемента
    QString encoding;         // кодировка документа
public:
    CSaxHandler();
    CSaxHandler(CNode* node);
    virtual ~CSaxHandler();

    void setDocument(CNode* node);
    void reset();	             // очистить стек и буферы

    // обработчики
    bool startElement(const QString &namespaceURI, const QString &localName, const QString &qName, const QXmlAttributes &attributes);
    bool characters(const QString &str);
    bool endElement(const QString &namespaceURI, const QString &localName, const QString &qName);
};
//----------------------------------------------------------------------

#endif // CSAXHANDLER_H
