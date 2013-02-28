#include "rightpanel.h"
#include "ui_rightpanel.h"

#include "debughelper.h"
#include "config.h"
#include "defines.h"
#include "filecommon.h"

RightPanel::RightPanel(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::RightPanel)
{
    ui->setupUi(this);
    init();
}
//------------------------------------------------------------------------------
RightPanel::~RightPanel()
{
    delete ui;
}
//------------------------------------------------------------------------------
void RightPanel::init()
{
    m_data.clear();
    GUI_NoteEditor = new NoteEditor(this);

    ui->ListNotes->setFont(Config::configuration()->getGUIMapFont()["FontNotes"]);
    createConnect();
    sUpdateGUIDayMode();

    fillModulesList();
}
//------------------------------------------------------------------------------
void RightPanel::createConnect()
{
    connect(ui->ListViewBookmark, SIGNAL(activated(QModelIndex)), SLOT(openBookmark(QModelIndex)));
    connect(ui->pBDelete, SIGNAL(clicked()), SLOT(deleteBookmark()));

    connect(ui->ListNotes, SIGNAL(clicked(QModelIndex)), SLOT(sEditNote(QModelIndex)));
    connect(ui->pBLoad, SIGNAL(clicked()), SLOT(sLoadNotes()));
    connect(ui->pBDeleteNote, SIGNAL(clicked()), SLOT(sDeleteNote()));
    connect(ui->pBEditNote, SIGNAL(clicked()), SLOT(sEditNote()));
    connect(ui->pBNewNote, SIGNAL(clicked()), SLOT(sNewNote()));
}
//------------------------------------------------------------------------------
void RightPanel::retranslate()
{
    ui->retranslateUi(this);
}
//------------------------------------------------------------------------------
void RightPanel::addNewBookmark(QString str)
{
    m_listBookmark.append(str);
    QStandardItemModel * modelBookmarks = new QStandardItemModel;

    for (int i = 0; i < m_listBookmark.size(); i++)
    {
        modelBookmarks->setItem(i, 0, new QStandardItem(m_listBookmark.at(i)));
    }

    ui->ListViewBookmark->setModel(modelBookmarks);
    /// add bookmarks to file
    // and load bookmars from file
}
//------------------------------------------------------------------------------
void RightPanel::loadBookmarks()
{
    QString pathToFileBookmarks = Config::configuration()->getAppDir()
            + "bookmarks.xml";
    m_listBookmark = getBookmarks(pathToFileBookmarks);

    QStandardItemModel * modelBookmarks = new QStandardItemModel;
    for (int i = 0; i < m_listBookmark.size(); i++)
    {
        modelBookmarks->setItem(i, 0, new QStandardItem(m_listBookmark.at(i)));
    }

    ui->ListViewBookmark->setModel(modelBookmarks);
}
//------------------------------------------------------------------------------
void RightPanel::saveBookmarks()
{
    QString pathToFileBookmarks = Config::configuration()->getAppDir()
            + "bookmarks.xml";
    QFile file(pathToFileBookmarks);
    if (file.exists())
        file.remove();

    if(file.open(QIODevice::WriteOnly))
    {
        QString tab = "    ";
        QTextStream ts(&file);
        ts.setCodec(getCodecOfEncoding("UTF-8"));
        ts << "<xml>" << endl;

        m_listBookmark.removeDuplicates();
        for (int i = 0; i < m_listBookmark.size(); i++)
        {
            ///    <strong number='value'> text </strong>
            ts << tab
               << "<bookmark name=\""
               << m_listBookmark.at(i)
               << "\">"
               << "</bookmark>"
               << endl;
        }
        ts << "</xml>" << endl;
    }
}
//------------------------------------------------------------------------------
void RightPanel::deleteBookmark()
{
    QString t_deleteBookmark = ui->ListViewBookmark->currentIndex().data(0).toString();
    m_listBookmark.removeOne(t_deleteBookmark);

    QStandardItemModel * modelBookmarks = new QStandardItemModel;
    for (int i = 0; i < m_listBookmark.size(); i++)
    {
        modelBookmarks->setItem(i, 0, new QStandardItem(m_listBookmark.at(i)));
    }

    ui->ListViewBookmark->setModel(modelBookmarks);
}
//------------------------------------------------------------------------------
void RightPanel::openBookmark(QModelIndex ind)
{
    QString str = ind.data(0).toString();

    int pos = str.indexOf(" : ");
    QString moduleName = QString(str).mid(0, pos);
    str.remove(moduleName + " : ");
    pos = str.indexOf(" : ");
    QString bookName = QString(str).mid(0, pos);
    str.remove(bookName + " : ");
    QString chapterValue = str;

    emit SIGNAL_OpenBookmark(moduleName, bookName, chapterValue);
}
//------------------------------------------------------------------------------
void RightPanel::showNoteList(QString curModule,
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
        ui->ListNotes->setModel(model);

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
        ui->ListNotes->setModel(new QStandardItemModel());
    }
}
//------------------------------------------------------------------------------
void RightPanel::sEditNote(QModelIndex ind)
{
    GUI_NoteEditor->setModuleName(m_curModule);
    GUI_NoteEditor->setBookName(m_curBook);
    GUI_NoteEditor->setChapterValue(m_curChapter);
    GUI_NoteEditor->setPath(m_curPath);
    GUI_NoteEditor->setVerse(m_verse);
    GUI_NoteEditor->editNote(m_data[ind.row()]);
}
//------------------------------------------------------------------------------
void RightPanel::sUpdateGUIDayMode()
{
    QPalette p = ui->ListNotes->palette();
    if (Config::configuration()->getDayMode())
    {
        p.setColor(QPalette::Base, GL_COLOR_DAY);
    }
    else
    {
        p.setColor(QPalette::Base, GL_COLOR_NIGHT);
    }

    ui->ListNotes->setPalette(p);
    ui->comBBooks->setPalette(p);
    ui->comBModules->setPalette(p);
    ui->sBChapter->setPalette(p);
    ui->ListViewBookmark->setPalette(p);
}
//------------------------------------------------------------------------------
void RightPanel::fillModulesList()
{
    QStringList t_listModules;
    QStringList files;
    files = recursiveFind(Config::configuration()->getAppDir());

    for(int i = 0; i < files.size(); i++)
    {
        if(files.at(i).indexOf(GL_FORMAT_NOTES) >= 0)
        {
            // hindi
            // get type module and module name
            QStringList t_list = QStringList
                    (
                        QString(files.at(i)).remove(Config::configuration()->getAppDir())
                        .split("/")
                        );
            m_notes[t_list.at(1)] == t_list.at(0);
            t_listModules << t_list.at(1);
        }
    }

    // получить список модулей в папках которых есть заметки
    // добавить в combobox
    // для текущего модуля загружать заметки, если нет, то показывать пустой список

    ui->comBModules->setModel(new QStringListModel(t_listModules, this));
}
//------------------------------------------------------------------------------
void RightPanel::sLoadNotes()
{

}
//------------------------------------------------------------------------------
void RightPanel::sNewNote()
{

}
//------------------------------------------------------------------------------
void RightPanel::sDeleteNote()
{

}
//------------------------------------------------------------------------------
void RightPanel::sEditNote()
{
    sEditNote(ui->ListNotes->currentIndex());
}
//------------------------------------------------------------------------------
