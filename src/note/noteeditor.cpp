#include "noteeditor.h"
#include "ui_noteeditor.h"
#include "debughelper.h"
#include "filecommon.h"

#include "config.h"

NoteEditor::NoteEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NoteEditor)
{
    ui->setupUi(this);
    init();
}
//------------------------------------------------------------------------------
NoteEditor::~NoteEditor()
{
    delete ui;
}
//------------------------------------------------------------------------------
void NoteEditor::saveNote()
{
    //    myDebug() << "saveNote";

    QString textNote = ui->textEditor->toPlainText();
    //    myDebug() << textNote;
    //    myDebug() << m_path;
    addTextNotes(textNote);

    m_verseFirst = "";
    m_verseLast = "";
    m_moduleName = "";
    m_bookName = "";
    m_chapterValue = "";

    QWidget::hide();
}
//------------------------------------------------------------------------------
void NoteEditor::init()
{
    createConnects();
}
//------------------------------------------------------------------------------
void NoteEditor::createConnects()
{
    connect(ui->buttonBox, SIGNAL(accepted()), SLOT(saveNote()));
}
//------------------------------------------------------------------------------
void NoteEditor::setModuleName(QString moduleName)
{
    m_moduleName = moduleName;
    setTextToLabel();
}
//------------------------------------------------------------------------------
void NoteEditor::setBookName(QString bookname)
{
    m_bookName = bookname;
    setTextToLabel();
}
//------------------------------------------------------------------------------
void NoteEditor::setChapterValue(QString chapter)
{
    m_chapterValue = chapter;
    setTextToLabel();
}
//------------------------------------------------------------------------------
void NoteEditor::setTextToLabel()
{
    ui->LACur->setText(m_moduleName + " : " +
                       m_bookName + " : " +
                       m_chapterValue);
}
//------------------------------------------------------------------------------
void NoteEditor::setPath(QString name)
{
    name.replace("text.xml", "notes.xml");
    m_path = name;
}
//------------------------------------------------------------------------------
void NoteEditor::addTextNotes(QString text)
{
    QFile file(m_path);
    if(file.exists())
    {
        QString tab = "    ";
        QString textFile = getTextFromHtmlFile(m_path);
        QString noteText = tab + "<note module=\"" + m_moduleName
                + "\" book=\"" + m_bookName
                + "\" chapter=\"" + m_chapterValue
                + "\" versebegin=\"" + m_verseFirst
                + "\" verseend=\"" + m_verseLast
                + "\">"
                + text
                + "</note>\n"
                + "</xml>";
        textFile.replace("</xml>", noteText);
        file.remove();

        if(file.open(QIODevice::WriteOnly))
        {
            QTextStream stream(&file);
            stream.setCodec(getCodecOfEncoding(getEncodingFromFile(m_path)));
            /// <note module="RST" book="Бытие" chapter="3" versebegin="2" verseend="5"> text note </note>
            stream << textFile;
        }
    }
    else
    {
        if(file.open(QIODevice::WriteOnly))
        {
            QTextStream stream(&file);
            stream.setCodec(getCodecOfEncoding("UTF-8"));
            QString tab = "    ";
            stream << "<xml>" << endl;
            stream << tab
                   << "<note module=\"" << m_moduleName
                   << "\" book=\"" << m_bookName
                   << "\" chapter=\"" << m_chapterValue
                   << "\" versebegin=\"" + m_verseFirst
                   << "\" verseend=\"" + m_verseLast
                   << "\">"
                   << text
                   << "</note>" << endl
                   << "</xml>";
        }
    }
}
//------------------------------------------------------------------------------
void NoteEditor::setFirstVerse(QString first)
{
    m_verseFirst = first;
}
//------------------------------------------------------------------------------
void NoteEditor::setLastVerse(QString last)
{
    m_verseLast = last;
}
//------------------------------------------------------------------------------
void NoteEditor::editNote(QString text)
{
    ui->textEditor->setPlainText(text);
    show();
}
//------------------------------------------------------------------------------
