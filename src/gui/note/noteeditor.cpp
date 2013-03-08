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
    if (m_edit)
    {
        replaceNote(ui->textEditor->toPlainText(), m_oldText);
        m_edit = false;
    }
    else
    {
        addTextNotes(ui->textEditor->toPlainText());
    }

    m_verse = "";
    m_moduleName = "";
    m_bookName = "";
    m_chapterValue = "";
    ui->textEditor->clear();

    emit SIGNAL_HideNotes();

    QWidget::hide();
}
//------------------------------------------------------------------------------
void NoteEditor::init()
{
    m_edit = false;
    createConnects();
}
//------------------------------------------------------------------------------
void NoteEditor::createConnects()
{
    connect(ui->buttonBox, SIGNAL(accepted()), SLOT(saveNote()));
    connect(ui->buttonBox, SIGNAL(rejected()), SLOT(rejectNote()));
}
//------------------------------------------------------------------------------
void NoteEditor::setModuleName(const QString moduleName)
{
    m_moduleName = moduleName;
    setTextToLabel();
}
//------------------------------------------------------------------------------
void NoteEditor::setBookName(const QString bookname)
{
    m_bookName = bookname;
    setTextToLabel();
}
//------------------------------------------------------------------------------
void NoteEditor::setChapterValue(const QString chapter)
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
void NoteEditor::setPath(const QString name)
{
    m_path = name;
//    m_path.replace("text" + GL_FORMAT_TEXT, "notes" + GL_FORMAT_NOTES);
}
//------------------------------------------------------------------------------
void NoteEditor::addTextNotes(const QString text)
{
    QFile file(m_path);

    QString tab = "    ";
    QString noteText = tab
                    + "<note module=\"" + m_moduleName
                    + "\" book=\"" + m_bookName
                    + "\" chapter=\"" + m_chapterValue
                    + "\">"
                    + text
                    + "</note>\n"
                    + "</xml>";

    if(file.exists())
    {
        QString textFile = getTextFromHtmlFile(m_path);
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
            stream << "<xml>" << endl;
            stream << noteText;
        }
    }
}
//------------------------------------------------------------------------------
void NoteEditor::replaceNote(const QString f_newText, const QString f_oldText)
{
    replaceStrInFile(m_path, f_oldText, f_newText);
}
//------------------------------------------------------------------------------
void NoteEditor::setVerse(const QString first)
{
    m_verse = first;
}
//------------------------------------------------------------------------------
void NoteEditor::editNote(const QString text)
{
    m_edit = true;
    m_oldText = text;
    ui->textEditor->setPlainText(text);
    show();
}
//------------------------------------------------------------------------------
void NoteEditor::retranslate()
{
    ui->retranslateUi(this);
}
//------------------------------------------------------------------------------
void NoteEditor::deleteNote(QString f_module, QString f_book, QString f_chapter, QString f_path, QString f_text)
{
    QString noteText = "<note module=\"" + f_module
            + "\" book=\"" + f_book
            + "\" chapter=\"" + f_chapter
            + "\">"
            + f_text
            + "</note>\n";
    replaceStrInFile(f_path, noteText, "");
}
//------------------------------------------------------------------------------
void NoteEditor::rejectNote()
{
    m_edit = false;
}
//------------------------------------------------------------------------------
void NoteEditor::sUpdateGUIDayMode()
{
    QPalette p = ui->textEditor->palette();
    if (Config::configuration()->getDayMode())
    {
        p.setColor(QPalette::Base, GL_COLOR_DAY);
    }
    else
    {
        p.setColor(QPalette::Base, GL_COLOR_NIGHT);
    }
    ui->textEditor->setPalette(p);
}
//------------------------------------------------------------------------------
