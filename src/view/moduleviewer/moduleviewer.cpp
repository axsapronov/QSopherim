#include "moduleviewer.h"
#include "ui_moduleviewer.h"
#include "debughelper.h"
#include "cnode.h"
#include "filecommon.h"


#include <QMenu>
#include <QContextMenuEvent>
#include <QXmlStreamReader>


static ModuleViewer *static_viewer = 0;

ModuleViewer::ModuleViewer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModuleViewer)
{

    ui->setupUi(this);
    init();

}
//------------------------------------------------------------------------------
ModuleViewer::~ModuleViewer()
{
    delete ui;
}
//------------------------------------------------------------------------------
//void ModuleViewer::contextMenuEvent(QContextMenuEvent *event)
//{
//    /// Добавить в контексное меню информацию о текущем расположении (Модуль:Книга:Глава:Номер стиха)

//    QMenu *menu = new QMenu(this);
//    menu->addAction(cutAct);
//    menu->addAction(copyAct);
//    menu->addAction(pasteAct);

//    menu->addSeparator();
//    QAction *act = new QAction(tr("YYYAAAAZ"), this);
//    menu->addAction(act);

//        QPoint lastPos = event->pos();
//        QTextCursor cursor = cursorForPosition(lastPos);
//        QString zeile = cursor.block().text();
//        int pos = cursor.columnNumber();
//        int end = zeile.indexOf(QRegExp("\\W+"), pos);
//        int begin = zeile.lastIndexOf(QRegExp("\\W+"), pos);
//        zeile = zeile.mid(begin + 1, end - begin - 1);
//        QStringList liste = getWordPropositions(zeile);
//        qDebug() << liste;
//        if (!liste.isEmpty())
//        {
//            menu -> addSeparator();
//            QAction *a;
//            //replace this  to TextEditBQella
//            a = menu->addAction(tr("Add .."), this, SLOT(slot_addWord(lastPos)));
//            a = menu->addAction(tr("Ignore .."), this, SLOT(slot_ignoreWord(lastPos)));
//            for (int i = 0; i < qMin(int(MaxWords), liste.size()); ++i)
//            {
//                misspelledWordsActs[i]->setText(liste.at(i).trimmed());
//                misspelledWordsActs[i]->setVisible(true);
//                menu -> addAction(misspelledWordsActs[i]);
//            }

//        } // if  misspelled


//    menu->exec(event->globalPos());
//}
//------------------------------------------------------------------------------
void ModuleViewer::createActions()
{
    cutAct = new QAction(tr("Cu&t"), this);
    cutAct->setShortcuts(QKeySequence::Cut);
    cutAct->setStatusTip(tr("Cut the current selection's contents to the "
                            "clipboard"));
    //    connect(cutAct, SIGNAL(triggered()), this, SLOT(cut()));

    copyAct = new QAction(tr("&Copy"), this);
//    copyAct->setShortcuts(QKeySequence::Copy);
//    copyAct->setStatusTip(tr("Copy the current selection's contents to the "
//                             "clipboard"));
//    //    connect(copyAct, SIGNAL(triggered()), this, SLOT(copy()));

    pasteAct = new QAction(tr("&Paste"), this);
//    pasteAct->setShortcuts(QKeySequence::Paste);
//    pasteAct->setStatusTip(tr("Paste the clipboard's contents into the current "
//                              "selection"));
    //    connect(pasteAct, SIGNAL(triggered()), this, SLOT(paste()));
}
//------------------------------------------------------------------------------
void ModuleViewer::showContextMenu(QPoint pt)
{
    //    QMenu *menu = ui->viewer->createStandardContextMenu();
    QMenu *menu = new QMenu(this);
    menu->addAction(cutAct);
    menu->addAction(copyAct);
    menu->addAction(pasteAct);

    menu->addSeparator();
//    QString str = curBook + ":" + curChapter;
    QAction *act = new QAction(QString(curBook + ":" + curChapter), this);

// bold text
//    QTextDocument *document = ui->viewer->document();
//      QTextCursor cursor(document);

//      for(int i = 0; i < 20 ; i++)
//      {
//      cursor.movePosition(QTextCursor::Down);
//      }
//      cursor.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);

//      QTextCharFormat format;
//      format.setFontWeight(QFont::Bold);

//      cursor.mergeCharFormat(format);



    menu->addAction(act);
    menu->exec(ui->viewer->mapToGlobal(pt));
    //    delete menu;
}
//------------------------------------------------------------------------------
ModuleViewer *ModuleViewer::viewer()
{
    Q_ASSERT( static_viewer );
    return static_viewer;
}
//------------------------------------------------------------------------------
void ModuleViewer::showChapter(QString pathToFile, QString nameBook, int numberchapter)
{
//    myDebug() << pathToFile << nameBook << numberchapter;

    QXmlStreamReader xmlReader;
    xmlReader.addData(getTextFromHtmlFile(pathToFile));

    bool flag = false;
    while(!xmlReader.atEnd() and !flag)
    {
        if(xmlReader.isStartElement())
        {
            QStringList sl;
            sl << xmlReader.name().toString();
            QXmlStreamAttributes attrs = xmlReader.attributes();
//            myDebug() << "yes0" << nameBook << attrs.value("name");
            if (attrs.value("name") == nameBook)
            {
                while(!xmlReader.atEnd() and !flag)
                {
                    if (xmlReader.attributes().value("number") ==
                            QString::number(numberchapter))
                    {
                        flag = true;
                        QString str = xmlReader.readElementText();
                        str.remove("    ");
                        ui->viewer->setText(str);
                    }
                    xmlReader.readNext();
                }
            }
        }
        xmlReader.readNext();
//        xmlReader.readNext();
    }
    curBook = nameBook;
    curChapter = QString::number(numberchapter);

}
//------------------------------------------------------------------------------
//void ModuleViewer::getTextChapter(QString pathToFile, QString nameBook, int numberchapter)
//{

//}
//------------------------------------------------------------------------------
void ModuleViewer::init()
{
    if( !static_viewer)
    {
        static_viewer = this;
    }
    else
    {
        qWarning( "Multiple viewers not allowed!" );
    }
    createActions();
    createConnects();

    ui->viewer->setContextMenuPolicy(Qt::CustomContextMenu);
    loadViewSettings();
}
//------------------------------------------------------------------------------
void ModuleViewer::createConnects()
{
    connect(ui->viewer, SIGNAL(customContextMenuRequested(QPoint)),
            this,SLOT(showContextMenu(QPoint)));

}
//------------------------------------------------------------------------------
void ModuleViewer::loadViewSettings()
{
    ui->viewer->setFontFamily(Config::configuration()->getFontFamily());
    ui->viewer->setFontPointSize(Config::configuration()->getFontSize());


}
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

