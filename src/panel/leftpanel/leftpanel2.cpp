#include "leftpanel2.h"
#include "ui_leftpanel2.h"

#include "filecommon.h"
#include "debughelper.h"

#include <QStandardItem>
#include <QStandardItemModel>

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
    delete ui;
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
    m_firstVerse = firstVerse;

    if (m_data.size() != 0)
    {
        for (int i = 0; i < m_data.size(); i++)
        {
            QStandardItemModel *model = new QStandardItemModel();
            model->clear();
            ui->ListViewNote->setModel(model);
            QStandardItem *item;
            item = new QStandardItem();
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
void LeftPanel2::init()
{
    m_data.clear();
    GUI_NoteEditor = new NoteEditor(this);
}
//------------------------------------------------------------------------------
void LeftPanel2::createConnects()
{
    connect(ui->ListViewNote, SIGNAL(clicked(QModelIndex)),
            SLOT(editNote(QModelIndex)));
}
//------------------------------------------------------------------------------
void LeftPanel2::editNote(QModelIndex ind)
{
    GUI_NoteEditor->setModuleName(m_curModule);
    GUI_NoteEditor->setBookName(m_curBook);
    GUI_NoteEditor->setChapterValue(m_curChapter);
    GUI_NoteEditor->setPath(m_curPath);
    GUI_NoteEditor->setFirstVerse(m_firstVerse);
    GUI_NoteEditor->setLastVerse(m_firstVerse);
//    myDebug() << ind.row() << m_data[ind.row()];
//    QString str = *(m_data[ind.row()]);
    GUI_NoteEditor->editNote(m_data[ind.row()]);

}
//------------------------------------------------------------------------------
