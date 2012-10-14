#include "moduleviewer.h"
#include "ui_moduleviewer.h"
#include "debughelper.h"
#include "cnode.h"
#include "filecommon.h"


#include <QMenu>
#include <QContextMenuEvent>
#include <QXmlStreamReader>

#include <QTextCursor>
#include <QTextDocumentFragment>

static ModuleViewer *static_viewer = 0;

ModuleViewer::ModuleViewer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModuleViewer)
{

    ui->setupUi(this);
    //    setMouseTracking(true);
    ui->viewer->viewport()->setMouseTracking(true);
    //    setMouseTracking(true);
    //    ui->viewer->viewport()->installEventFilter(this);
    init();
    //    debug();

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
    QAction *act = new QAction(QString(curModule
                                       + " : "
                                       + curBook
                                       + " : "
                                       + curChapter), this);

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

    /* если есть стронги,
     *то надо их при чтении xml'я
     *обрабатыванит и приписывать соответств слову
     */

    bool strong = true;

    bool flag = false;
    while(!xmlReader.atEnd() and !flag)
    {
        if(xmlReader.isStartElement())
        {
            QStringList sl;
            sl << xmlReader.name().toString();
            QXmlStreamAttributes attrs = xmlReader.attributes();
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
                        if (strong)
                        {
                            //                            str.replace(",", ", ")
                            //                                    .replace(".", ". ");
                            str = fillStrongList(str);
                        }
                        ui->viewer->setText(str);
                    }
                    xmlReader.readNext();
                }
            }
        }
        xmlReader.readNext();
    }
    curBook = nameBook;
    curPath = pathToFile;
    curChapter = QString::number(numberchapter);
    ui->LAStatus->setText(curModule + " : " + curBook + " : " + curChapter );
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

    //    setMouseTracking(true);
    loadViewSettings();
}
//------------------------------------------------------------------------------
void ModuleViewer::createConnects()
{
    connect(ui->viewer, SIGNAL(customContextMenuRequested(QPoint)),
            this,SLOT(showContextMenu(QPoint)));
    connect(ui->viewer, SIGNAL(selectionChanged()), SLOT(setCurLine()));
    //    connect(ui->viewer, SIGNAL(textChanged()), SLOT(setCurLine()));
}
//------------------------------------------------------------------------------
void ModuleViewer::loadViewSettings()
{
    ui->viewer->setFontFamily(Config::configuration()->getFontFamily());
    ui->viewer->setFontPointSize(Config::configuration()->getFontSize());
}
//------------------------------------------------------------------------------
void ModuleViewer::setModuleName(QString newModule)
{
    curModule = newModule;
}
//------------------------------------------------------------------------------
QString ModuleViewer::getModuleName()
{
    return curModule;
}
//------------------------------------------------------------------------------
void ModuleViewer::setBookName(QString newBook)
{
    curBook = newBook;
}
//------------------------------------------------------------------------------
QString ModuleViewer::getBookName()
{
    return curBook;
}
//------------------------------------------------------------------------------
void ModuleViewer::setChapterValue(QString newChap)
{
    curChapter = newChap;
}
//------------------------------------------------------------------------------
QString ModuleViewer::getChapterValue()
{
    return curChapter;
}
//------------------------------------------------------------------------------
void ModuleViewer::setPath(QString newPath)
{
    curPath = newPath;
}
//------------------------------------------------------------------------------
QString ModuleViewer::getPath()
{
    return curPath;
}
//------------------------------------------------------------------------------
void ModuleViewer::setCurLine()
{
    /// count select lines
    //    QTextCursor cursor = ui->viewer->textCursor();
    //    int selectedLines = 0; //<--- this is it
    //    if(!cursor.selection().isEmpty())
    //    {
    //        QString str = cursor.selection().toPlainText();
    //        selectedLines = str.count("\n")+1;
    //    }

    //    myDebug() << selectedLines;

    /// current line
    //    QTextCursor cursor      = ui->viewer->textCursor();
    ////     Current line text
    ////    QString cur_line_text   = cursor.block().text().trimmed();

    //    // Current line
    //    int     cur_line_number = cursor.blockNumber();

    //    // Current column
    //    int     cur_line_column = cursor.columnNumber();

    //    myDebug() << cur_line_number << cur_line_column;


    QTextCursor cursor = ui->viewer->textCursor();
    int start = cursor.selectionStart();
    int end = cursor.selectionEnd();

    if(!cursor.hasSelection())
        return; // No selection available

    cursor.setPosition(start);
    /// first line is empty
    lastSelectLineFirst = cursor.blockNumber();
    cursor.setPosition(end, QTextCursor::KeepAnchor);
    lastSelectLineLast = cursor.blockNumber();

    showNoteList();
    //    showStrong();
    //    myDebug() << "start: " << firstLine << " end: " << lastLine;
}
////------------------------------------------------------------------------------
//int ModuleViewer::getLastSelectLineFirst()
//{
//    return lastSelectLineFirst;
//}
////------------------------------------------------------------------------------
//int ModuleViewer::getLastSelectLineLast()
//{
//    return lastSelectLineLast;
//}
//------------------------------------------------------------------------------
QString ModuleViewer::getLastSelectLineFirst()
{
    return QString::number(lastSelectLineFirst);
}
//------------------------------------------------------------------------------
QString ModuleViewer::getLastSelectLineLast()
{
    return QString::number(lastSelectLineLast);
}
//------------------------------------------------------------------------------
void ModuleViewer::setLastSelectLineFirst(int firstlast)
{
    lastSelectLineFirst = firstlast;
}
//------------------------------------------------------------------------------
void ModuleViewer::setLastSelectLineLast(int firstlast)
{
    lastSelectLineLast = firstlast;
}
//------------------------------------------------------------------------------
void ModuleViewer::showNoteList()
{
    /* по названию модуля
     * книги
     *главы
     *и номера начального стиха
     *получаем список заметок
     *создаем лист для каждой из заметок
     *в элемент листа пишем по 50 первых символов
     *при нажатии на элемент листа
     *открываем диалог с редактированием заметки
     */
    QString path = curPath;
    path.replace("text.xml", "notes.xml");
    emit showNoteList(curModule,
                      curBook,
                      curChapter,
                      path,
                      QString::number(lastSelectLineFirst));

}
//------------------------------------------------------------------------------
bool ModuleViewer::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type() == QEvent::MouseMove)
    {
        //        QMouseEvent *mEvent = static_cast<QMouseEvent*>(event);
        //        myDebug() << mEvent->pos();
        setCurLine();
        return true;
    }
    if (event->type() == QEvent::MouseButtonPress)
    {
        setCurLine();
        return true;
    }
    if (event->type() == QEvent::MouseButtonRelease)
    {
        setCurLine();
        return true;
    }
    //    if (event->type() == QEvent::MouseTrackingChange)
    //    {
    //        setCurLine();
    //        return true;
    //    }
    else return QObject::eventFilter(obj, event);
}
//------------------------------------------------------------------------------
//void ModuleViewer::mouseMoveEvent(QMouseEvent *ev)
//{
//    myDebug() << ev->pos();
//}
//------------------------------------------------------------------------------
void ModuleViewer::showStrong()
{

    /* по слову
     *получаем список стронгов
     * добавляем текст в label
     */

    QString path = curPath;
    //        fileName << "/home/files/Documents/Bible/unrar/my/BIBLEQT.INI";
    //    QString path = "/home/files/Documents/Bible/strong/strong/"
    //    QString path = curPath;
    //    path.replace("text.xml", "notes.xml");


    //    emit showNoteList(curModule,
    //                      curBook,
    //                      curChapter,
    //                      path,
    //                      QString::number(lastSelectLineFirst));
}
//------------------------------------------------------------------------------
void ModuleViewer::setStrongList(QString path)
{
    m_list = getListStrongs(path);
    int i = 5;
    //    myDebug() << m_list.size() << m_list.at(i).number
    //                 << m_list.at(i).text;
}
//------------------------------------------------------------------------------
//QHash<int, QHash<QString, QString> > ModuleViewer::getListStrongWord(QString word)
//{
////    int count = 0;
//    QHash<int, QString> list;
////    for(int i = 0; i < m_list.size(); i++)
////    {
////        list[count] = m_list[i][word];
////    }

//    return list;
//}
//------------------------------------------------------------------------------
QString ModuleViewer::fillStrongList(QString str)
{
    int r = 0;
    QString t_str = "";

    //    str.remove("\n").remove("\r");
    bool flag = false;
    //    bool flag2 = false;
    bool flag3 = false;
    int count;
    int precount;
    QVector<int> vect;

    //    str.replace(QRegExp("\d,"))
    str.replace(",", " ,");
    str.replace(".", " .");
    str.replace(":", " :");
    QString ret = str;

    while (str.length() > r)
    {
        flag = false;
        t_str = getNextWord(str, r);
        r += t_str.length();

        if (t_str.isEmpty())
            break;

        count = t_str.toInt(&flag);
        if(flag and count != precount)
        {
            ret.remove(t_str);
            vect.push_back(count);
            precount = count;
            flag3 = true;
        }

        if(flag3 && !flag)
        {
            m_strongs[t_str] = vect;
//            myDebug() << vect.size() << t_str;
            vect.clear();
            flag3 = false;
        }
    }

    ret.replace("  ", " ");
    return ret;
}
//------------------------------------------------------------------------------
void ModuleViewer::debug()
{
    //    QString str =
    QString str;
    //        str = "сотворил 01254 0333 0332 Бог ";
    str = "В начале 07225 сотворил 01254 08804 0853 Бог 0430 небо 08064 и 0853 землю 0776.";

    fillStrongList(str);
}
//------------------------------------------------------------------------------
