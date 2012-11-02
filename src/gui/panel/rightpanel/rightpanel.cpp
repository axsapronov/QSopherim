#include "rightpanel.h"
#include "ui_rightpanel.h"

#include "debughelper.h"
#include "config.h"
#include <QStandardItemModel>
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
void RightPanel::init()
{
    createConnect();
}
//------------------------------------------------------------------------------
void RightPanel::createConnect()
{
    connect(ui->ListViewBookmark, SIGNAL(activated(QModelIndex)),
            SLOT(openBookmark(QModelIndex)));
    connect(ui->pBDelete, SIGNAL(clicked()), SLOT(deleteBookmark()));
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
//------------------------------------------------------------------------------
