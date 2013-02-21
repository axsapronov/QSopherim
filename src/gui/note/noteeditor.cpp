#include "noteeditor.h"
#include "ui_noteeditor.h"
#include "debughelper.h"
#include "filecommon.h"
#include "defines.h"

#include "config.h"

NoteEditor::NoteEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NoteEditor)
{
    ui->setupUi(this);
    setWindowTitle(QString(tr("Note editor") + " | %1 - %2").arg(GL_PROG_NAME).arg(GL_PROG_VERSION_STR));
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
    QString textNote = ui->textEditor->toPlainText();
    addTextNotes(textNote);

    m_verse = "";
    m_moduleName = "";
    m_bookName = "";
    m_chapterValue = "";
    ui->textEditor->clear();

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
    name.replace("text" + GL_FORMAT_TEXT, "notes.xml");
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
                + "\" verse=\"" + m_verse
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
                   << "\" verse=\"" + m_verse
                   << "\">"
                   << text
                   << "</note>" << endl
                   << "</xml>";
        }
    }
}
//------------------------------------------------------------------------------
void NoteEditor::setVerse(QString first)
{
    m_verse = first;
}
//------------------------------------------------------------------------------
void NoteEditor::editNote(QString text)
{
    ui->textEditor->setPlainText(text);
    show();
}
//------------------------------------------------------------------------------
void NoteEditor::retranslate()
{
    ui->retranslateUi(this);
}
//------------------------------------------------------------------------------
