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
    QHash<int, QString> data = getNoteOfParams(curPath,
                                               curModule,
                                               curBook,
                                               curChapter,
                                               firstVerse);
    for (int i = 0; i < data.size(); i++)
    {
        QStandardItemModel *model = new QStandardItemModel();
        ui->ListViewNote->setModel(model);
        QStandardItem *item;
        item = new QStandardItem();
        item->setData( data[i], Qt::DisplayRole );
        item->setEditable( false );
        model->appendRow( item );
    }
}
//------------------------------------------------------------------------------
