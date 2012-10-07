
#include "csaxhandler.h"
#include "cnode.h"

//----------------------------------------------------------------------
CSaxHandler::CSaxHandler()
{
    reset();
}
//------------------------------------------------------------------------------
CSaxHandler::CSaxHandler(CNode* node)
{
    setDocument(node);
}
//------------------------------------------------------------------------------
CSaxHandler::~CSaxHandler()
{
    // doc не удаляем (владелец - внешняя программа)!
    textElement.clear();
    nodeStack.clear();
}
//------------------------------------------------------------------------------
void CSaxHandler::reset()
{
    doc = 0;
    textElement.clear();
    nodeStack.clear();
}
//------------------------------------------------------------------------------
void CSaxHandler::setDocument(CNode* node)
{
    reset();
    doc = node;

    // корневой элемент
    nodeStack.push(doc);
}
//------------------------------------------------------------------------------
bool CSaxHandler::startElement(const QString &namespaceURI,
                               const QString &localName,
                               const QString &qName,
                               const QXmlAttributes &attributes)
{

    if(nodeStack.isEmpty())
        return false;

    // текущий элемент
    CNode* node=nodeStack.top();

    // обрабатываемый элемент
    if(node)
        node=node->getNode(localName);

    // инициализация реквизитов
    if(node)
        node->setRequisites(localName, attributes);

    // сделаем его текущим
    nodeStack.push(node);
    textElement.clear();
    return true;
}
//------------------------------------------------------------------------------
bool CSaxHandler::characters(const QString &str)
{
    textElement += str;
    return true;
}
//------------------------------------------------------------------------------

bool CSaxHandler::endElement(const QString &namespaceURI,
                             const QString &localName,
                             const QString &qName)
{
    if(nodeStack.isEmpty())
        return false;

    CNode* node = nodeStack.top();

    // инициализация текстовых элементов
    if(node && node->isTextElement(localName))
    {
        QXmlAttributes textAttr;
        textAttr.append(localName, "", "", textElement);
        node->setRequisites(localName, textAttr);
    }

    // элемент обработан
    nodeStack.pop();
    return true;
}
//------------------------------------------------------------------------------
