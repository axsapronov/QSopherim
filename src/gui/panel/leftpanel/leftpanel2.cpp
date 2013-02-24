#include "leftpanel2.h"
#include "ui_leftpanel2.h"

#include "filecommon.h"
#include "debughelper.h"
#include "strongcommon.h"

#include "defines.h"

// panel for info:
// strongs , journal, and other

LeftPanel2::LeftPanel2(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::LeftPanel2)
{
    ui->setupUi(this);
    init();
    createConnects();
}
//------------------------------------------------------------------------------
LeftPanel2::~LeftPanel2()
{
    delete m_modelNotes;
    delete GUI_NoteEditor;
    delete ui;
}
//------------------------------------------------------------------------------
void LeftPanel2::init()
{
    m_data.clear();
    GUI_NoteEditor = new NoteEditor(this);

    //    QString path = m_curPath;
    if (Config::configuration()->getStrongHebrew().isEmpty())
    {
        m_strongHebrew_on = false;
    }
    else
    {
        getMapStrongs(Config::configuration()->getStrongHebrew(), m_mapStrongHebrew);
        m_strongHebrew_on = true;
    }

    if (Config::configuration()->getStrongGreek().isEmpty())
    {
        m_strongGreek_on = false;
    }
    else
    {
        getMapStrongs(Config::configuration()->getStrongGreek(), m_mapStrongGreek);
        m_strongGreek_on = true;
    }

    sUpdateGUIDayMode();

    ui->ListViewJournal->setFont(Config::configuration()->getGUIMapFont()["FontJournal"]);
    ui->ListViewNote->setFont(Config::configuration()->getGUIMapFont()["FontNotes"]);
}
//------------------------------------------------------------------------------
void LeftPanel2::createConnects()
{
    connect(ui->ListViewNote, SIGNAL(clicked(QModelIndex)),
            SLOT(editNote(QModelIndex)));

    connect(ui->ListViewJournal, SIGNAL(clicked(QModelIndex)),
            SLOT(showChapterFromJournal(QModelIndex)));
}
//------------------------------------------------------------------------------
void LeftPanel2::editNote(QModelIndex ind)
{
    GUI_NoteEditor->setModuleName(m_curModule);
    GUI_NoteEditor->setBookName(m_curBook);
    GUI_NoteEditor->setChapterValue(m_curChapter);
    GUI_NoteEditor->setPath(m_curPath);
    GUI_NoteEditor->setVerse(m_verse);
    //    myDebug() << ind.row() << m_data[ind.row()];
    //    QString str = *(m_data[ind.row()]);
    GUI_NoteEditor->editNote(m_data[ind.row()]);

}
//------------------------------------------------------------------------------
void LeftPanel2::retranslate()
{
    ui->retranslateUi(this);
}
//------------------------------------------------------------------------------
void LeftPanel2::addRecordToJournal(QString modulename,
                                    QString bookname,
                                    QString chaptervalue)
{

    QString t_record =
            modulename + ":" +
            bookname + ":" +
            chaptervalue;

    QStandardItemModel *model = new QStandardItemModel(m_journalList.size(), 0);
    model->clear();
    ui->ListViewJournal->setModel(model);

    QStringList t_list;
    t_list << t_record;

    int count = 10;

    for (int i = 0; i < count - 1 && i < m_journalList.size(); i++)
    {
        t_list << m_journalList.at(i);
        // add to model
        model->appendRow( new QStandardItem(t_list.at(i)));
    }
    //add to model last elem
    model->appendRow( new QStandardItem(t_list.at(t_list.size() - 1)));

    // or this - this is add to model
    //    for (int i = 0; i < count && i < t_list.size(); i++)
    //    {
    //        model->appendRow( new QStandardItem(t_list.at(i)));
    //    }

    m_journalList = t_list;
    Config::configuration()->setJournalHistory(&m_journalList);
}
//------------------------------------------------------------------------------
void LeftPanel2::showChapterFromJournal(QModelIndex ind)
{
    //    GUI_NoteEditor->setModuleName(m_curModule);
    //    GUI_NoteEditor->setBookName(m_curBook);
    //    GUI_NoteEditor->setChapterValue(m_curChapter);
    //    GUI_NoteEditor->setPath(m_curPath);


    // parse journal item
    // get module name, book name, chapter value
    QString str = ui->ListViewJournal->model()->data(ind).toString();
    int pos = str.indexOf(":");

    QString moduleName = QString(str).mid(0, pos);
    str.remove(moduleName + ":");
    pos = str.indexOf(":");
    QString bookName = QString(str).mid(0, pos);
    str.remove(bookName + ":");
    QString chapterValue = str;

    emit SIGNAL_ShowChapterFromJournal(moduleName, bookName, chapterValue);
}
//------------------------------------------------------------------------------
void LeftPanel2::showNoteList(QString curModule,
                              QString curBook,
                              QString curChapter,
                              QString curPath,
                              QString firstVerse)
{
    m_data = getNoteOfParams(curPath,
                             curModule,
                             curBook,
                             curChapter,
                             firstVerse);

    m_curModule = curModule;
    m_curBook = curBook;
    m_curChapter = curChapter;
    m_curPath = curPath;
    m_verse = firstVerse;

    if (m_data.size() != 0)
    {
        QStandardItemModel *model = new QStandardItemModel(m_data.size(), 0);
        model->clear();
        ui->ListViewNote->setModel(model);

        for (int i = 0; i < m_data.size(); i++)
        {
            QStandardItem *item = new QStandardItem();
            QString first50Simbols = m_data[i].mid(0, 50);
            item->setData(first50Simbols, Qt::DisplayRole );
            item->setEditable( false );
            model->appendRow( item );
        }

    }
    else
    {
        // reset
        ui->ListViewNote->setModel(new QStandardItemModel());
    }
}
//------------------------------------------------------------------------------
void LeftPanel2::showStrong(QString number)
{
    if (getTypeStrong() == "Hebrew"
            and m_strongHebrew_on)
    {
        ui->textBrStrong->setFont(Config::configuration()->getGUIMapFont()["FontStrongsHebrew"]);
        QString str =
                tr("Strong number: ")
                + "<b>" + number + "</b>"
                + "\n<br>"
                + m_mapStrongHebrew[number.toInt()].text;
        ui->textBrStrong->setHtml(str);
    }

    if (getTypeStrong() == "Greek"
            and m_strongHebrew_on)
    {
        ui->textBrStrong->setFont(Config::configuration()->getGUIMapFont()["FontStrongsGreek"]);
        QString str =
                tr("Strong number: ")
                + "<b>" + number + "</b>"
                + "\n<br>"
                + m_mapStrongGreek[number.toInt()].text;
        ui->textBrStrong->setHtml(str);
    }
}
//------------------------------------------------------------------------------
void LeftPanel2::sSetStrongHebrew(QString path)
{
    getMapStrongs(path, m_mapStrongHebrew );
    m_strongHebrew_on = true;
}
//------------------------------------------------------------------------------
void LeftPanel2::sSetStrongGreek(QString path)
{
    getMapStrongs(path, m_mapStrongGreek);
    m_strongGreek_on = true;
}
//------------------------------------------------------------------------------
void LeftPanel2::loadJournal()
{
    m_journalList = *(Config::configuration()->getJournalHistory());

    QStandardItemModel *model = new QStandardItemModel(m_journalList.size(), 0);
    model->clear();
    ui->ListViewJournal->setModel(model);

    int count = 10;
    for (int i = 0; i < count && i < m_journalList.size(); i++)
    {
        // add to model
        model->appendRow( new QStandardItem(m_journalList.at(i)));
    }
}
//------------------------------------------------------------------------------
void LeftPanel2::sUpdateGUIDayMode()
{
    QPalette p = ui->ListViewJournal->palette();
    if (Config::configuration()->getDayMode())
    {
        p.setColor(QPalette::Base, GL_COLOR_DAY);
    }
    else
    {
        p.setColor(QPalette::Base, GL_COLOR_NIGHT);
    }
    ui->ListViewJournal->setPalette(p);
    ui->ListViewNote->setPalette(p);
    ui->textBrStrong->setPalette(p);
}
//------------------------------------------------------------------------------
