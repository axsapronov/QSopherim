#include "moduleviewer.h"
#include "ui_moduleviewer.h"

#include <QMenu>
#include <QContextMenuEvent>


ModuleViewer::ModuleViewer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModuleViewer)
{
    ui->setupUi(this);
    createActions();
    ui->viewer->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->viewer, SIGNAL(customContextMenuRequested(QPoint)),
            this,SLOT(showContextMenu(QPoint)));
}
///-----------------------------------------------------------------------------
ModuleViewer::~ModuleViewer()
{
    delete ui;
}
///-----------------------------------------------------------------------------
void ModuleViewer::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.addAction(cutAct);
    menu.addAction(copyAct);
    menu.addAction(pasteAct);
    menu.exec(event->globalPos());
}
///-----------------------------------------------------------------------------
void ModuleViewer::createActions()
{
    cutAct = new QAction(tr("Cu&t"), this);
    cutAct->setShortcuts(QKeySequence::Cut);
    cutAct->setStatusTip(tr("Cut the current selection's contents to the "
                            "clipboard"));
//    connect(cutAct, SIGNAL(triggered()), this, SLOT(cut()));

    copyAct = new QAction(tr("&Copy"), this);
    copyAct->setShortcuts(QKeySequence::Copy);
    copyAct->setStatusTip(tr("Copy the current selection's contents to the "
                             "clipboard"));
//    connect(copyAct, SIGNAL(triggered()), this, SLOT(copy()));

    pasteAct = new QAction(tr("&Paste"), this);
    pasteAct->setShortcuts(QKeySequence::Paste);
    pasteAct->setStatusTip(tr("Paste the clipboard's contents into the current "
                              "selection"));
//    connect(pasteAct, SIGNAL(triggered()), this, SLOT(paste()));
}
///-----------------------------------------------------------------------------
void ModuleViewer::showContextMenu(QPoint pt)
{
//    QMenu *menu = ui->viewer->createStandardContextMenu();
    QMenu menu(this);
    menu.addAction(cutAct);
    menu.exec(ui->viewer->mapToGlobal(pt));
//    delete menu;
}
///-----------------------------------------------------------------------------

///-----------------------------------------------------------------------------
///-----------------------------------------------------------------------------
