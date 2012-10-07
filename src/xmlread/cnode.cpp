
#include "cnode.h"

#include "cnode.h"
#include "csaxhandler.h"
#include <QFile>
#include <QBuffer>
#include <QXmlStreamWriter>
//------------------------------------------------------------------------------

QString CNode::encoding       = "UTF-8";
bool    CNode::autoFormatting = true;
//------------------------------------------------------------------------------

CNode::CNode(){
}
//------------------------------------------------------------------------------
// интерфейсные методы
//------------------------------------------------------------------------------
void CNode::setRequisites(const QString &name,const QXmlAttributes &attributes)
{
     // ничего не делается - для типов, не содержащих реквизиты
}
//------------------------------------------------------------------------------
// указатель на узел элемент
CNode* CNode::getNode(const QString &name)
{
    if(name==nodeName)
        return this;
    else
        return 0;
}
//------------------------------------------------------------------------------
// проверка, является ли элемент текстовым
bool CNode::isTextElement(const QString &name)
{
    return false;
}
//------------------------------------------------------------------------------
bool CNode::writeNode(QXmlStreamWriter& writer,const QString& nsUri)
{
    return true;
}
//------------------------------------------------------------------------------
// запись необязательных реквизитов ЭС
//------------------------------------------------------------------------------

void CNode::writeAttribute(QXmlStreamWriter& writer,
                           const QString& name,
                           const QString& value)
{
    if(!value.isEmpty())
        writer.writeAttribute(name, value);
}

void CNode::writeTextElement(QXmlStreamWriter& writer,
                             const QString& nsUri,
                             const QString& name,
                             const QString& text)
{
    if(!text.isEmpty())
        writer.writeTextElement(nsUri,name,text);
}
//------------------------------------------------------------------------------
// чтение из XML (при совпадении типов)
//------------------------------------------------------------------------------
bool CNode::readDocument(const QString &fileName)
{
    QFile device(fileName);
    return readFromDevice(&device);
}
//------------------------------------------------------------------------------
bool CNode::readDocument(QByteArray* array)
{
    QBuffer device(array);
    return readFromDevice(&device);
}
//------------------------------------------------------------------------------
bool CNode::readFromDevice(QIODevice* device)
{
    if(!device->open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QXmlInputSource xmlInputSource(device);
    CSaxHandler handler(this);

    QXmlSimpleReader reader;
    reader.setContentHandler(&handler);
    bool ok=reader.parse(xmlInputSource);

    device->close();
    return true;
}
//------------------------------------------------------------------------------
// запись в XML
//------------------------------------------------------------------------------
bool CNode::writeDocument(const QString &fileName)
{
    QFile device(fileName);
    return writeToDevice(&device);
}
//------------------------------------------------------------------------------
bool CNode::writeDocument(QByteArray* array)
{
    array->clear();
    QBuffer device(array);
    return writeToDevice(&device);
}
//------------------------------------------------------------------------------
bool CNode::writeToDevice(QIODevice* device)
{
    QXmlStreamWriter writer(device);

    if(!device->open(QIODevice::WriteOnly))
        return false;

    writer.setAutoFormatting(autoFormatting);

    // формирование ЭС
    writer.setCodec(encoding.toAscii().data());
    writer.writeStartDocument();
    if(!nodeNamespace.isEmpty())
        writer.writeNamespace(nodeNamespace, nodePrefix);
    writeNode(writer,nodeNamespace);
    writer.writeEndDocument();

    device->close();
    return true;
}
//------------------------------------------------------------------------------
