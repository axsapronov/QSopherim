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
    m_listBookmark << str;
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
            + "/bookmarks.xml";
    QStringList m_listBookmark = getBookmarks(pathToFileBookmarks);

    QStandardItemModel * modelBookmarks = new QStandardItemModel;
    for (int i = 0; i < m_listBookmark.size(); i++)
    {
        modelBookmarks->setItem(i, 0, new QStandardItem(m_listBookmark.at(i)));
    }

    ui->ListViewBookmark->setModel(modelBookmarks);
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
