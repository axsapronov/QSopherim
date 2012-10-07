#ifndef CNODE_H
#define CNODE_H

#include <QString>

//----------------------------------------------------------------------
// CNode - узел объекта
// Интерфейсный класс, обеспечивающий взаимодействие объекта и XML
//----------------------------------------------------------------------

// Forward Decls
class QXmlAttributes;
class QXmlStreamWriter;
class QIODevice;

class CNode
{
private:
    // вспомогательные методы работы с устройствами записи/чтения
    bool writeToDevice(QIODevice* device);
    bool readFromDevice(QIODevice* device);
protected:
    // пространство имен и префикс
    QString nodeNamespace;
    QString nodePrefix;

    // методы для записи в XML необязательных реквизитов
    void writeAttribute(QXmlStreamWriter& writer,const QString& name, const QString& value);
    void writeTextElement(QXmlStreamWriter& writer,const QString& nsUri,const QString& name,const QString& text);

    // интерфейсные методы - используются для чтения из XML SAX-парсером
    friend class CSaxHandler;
    virtual void setRequisites(const QString &name,const QXmlAttributes &attributes);
    virtual CNode* getNode(const QString &name);
    virtual bool isTextElement(const QString &name);

    // интерфейсный метод - запись объекта в XML
    virtual bool writeNode(QXmlStreamWriter& writer,const QString& nsUri);
public:
    CNode();

    // наименование узла
    QString nodeName;

    // чтение объекта из XML - из файла или символьного массива
    bool readDocument(const QString &fileName);
    bool readDocument(QByteArray* array);

    // запись объекта в XML - в файл или символьный массив
    bool writeDocument(const QString &fileName);
    bool writeDocument(QByteArray* array);

    // флаги, используемые при записи
    static QString encoding;	   // кодировка, используемая при записи
    static bool autoFormatting; // флаг форматирования XML при записи
};
//----------------------------------------------------------------------

#endif // CNODE_H
