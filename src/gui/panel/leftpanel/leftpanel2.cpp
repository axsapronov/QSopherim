#include "leftpanel2.h"
#include "ui_leftpanel2.h"

#include "filecommon.h"
#include "debughelper.h"
#include "strongcommon.h"


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
    GUI_NoteEditor->deleteLater();
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
        m_listStrongHebrew = getListStrongs(Config::configuration()->getStrongHebrew());
        m_strongHebrew_on = true;
    }

    if (Config::configuration()->getStrongGreek().isEmpty())
    {
        m_strongGreek_on = false;
    }
    else
    {
        m_listStrongGreek = getListStrongs(Config::configuration()->getStrongGreek());
        m_strongGreek_on = true;
    }

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

    QStringList t_list;
    m_journalList << t_record;
    QStandardItemModel *model = new QStandardItemModel(m_journalList.size(), 0);
    model->clear();
    ui->ListViewJournal->setModel(model);

    int i = m_journalList.size();
    int count = 10;  // last 10 chapters to history
    while(i > 0 and count != 0)
    {
        QStandardItem *item = new QStandardItem();
        item->setData(m_journalList.at(i -1 ), Qt::DisplayRole );
        item->setEditable( false );
        model->appendRow( item );
        t_list << m_journalList.at(i-1);
        i--;
        count--;
    }
    m_journalList = t_list;
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
        for (int i = 0; i < m_data.size(); i++)
        {
            QStandardItemModel *model = new QStandardItemModel();
            model->clear();
            ui->ListViewNote->setModel(model);
            QStandardItem *item = new QStandardItem();
            QString first50Simbols = m_data[i].mid(0, 50);
            item->setData(first50Simbols, Qt::DisplayRole );
            item->setEditable( false );
            model->appendRow( item );
        }
    }
    else
    {
        /// reset
        ui->ListViewNote->setModel(new QStandardItemModel());
    }
}
//------------------------------------------------------------------------------
void LeftPanel2::showStrong(QString number)
{
    // добавить вывод сразу и гречески и иврит
    if (m_strongGreek_on)
    {
        //    myDebug() << m_listStrong.size();
        int i = 0;
        do
        {
            if (m_listStrongGreek.at(i).number == number.toInt())
            {
                QString str =
                        tr("Strong number ")
                        + number
                        + "\n"
                        + m_listStrongGreek.at(i).text;
                ui->textBrStrong->setPlainText(str);
            }
            i++;
        } while (i < m_listStrongGreek.size());
    }
}
//------------------------------------------------------------------------------
void LeftPanel2::sSetStrongHebrew(QString path)
{
    m_listStrongHebrew = getListStrongs(path);
    m_strongHebrew_on = true;
}
//------------------------------------------------------------------------------
void LeftPanel2::sSetStrongGreek(QString path)
{
    m_listStrongGreek = getListStrongs(path);
    m_strongGreek_on = true;
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
