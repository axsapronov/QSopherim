#include "moduleviewer.h"
#include "ui_moduleviewer.h"
#include "debughelper.h"
#include "cnode.h"
#include "filecommon.h"


#include <QMenu>
#include <QContextMenuEvent>
#include <QToolTip>
#include <QXmlStreamReader>

#include <QTextCursor>
#include <QTextBlock>
#include <QTextDocumentFragment>

static ModuleViewer *static_viewer = 0;

ModuleViewer::ModuleViewer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModuleViewer)
{
    ui->setupUi(this);
    init();
    //    debug();
}
//------------------------------------------------------------------------------
ModuleViewer::~ModuleViewer()
{
    delete act_cut;
    delete act_copy;
    delete act_paste;
    delete ui;
}
//------------------------------------------------------------------------------
//void ModuleViewer::contextMenuEvent(QContextMenuEvent *event)
//{
//    /// Добавить в контексное меню информацию о текущем расположении (Модуль:Книга:Глава:Номер стиха)

//    QMenu *menu = new QMenu(this);
//    menu->addAction(act_cut);
//    menu->addAction(act_copy);
//    menu->addAction(act_paste);

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
    act_cut = new QAction(tr("Cu&t"), this);
    act_cut->setShortcuts(QKeySequence::Cut);
    act_cut->setStatusTip(tr("Cut the current selection's contents to the "
                             "clipboard"));
    //    connect(act_cut, SIGNAL(triggered()), this, SLOT(cut()));

    act_copy = new QAction(tr("&Copy"), this);
    //    act_copy->setShortcuts(QKeySequence::Copy);
    //    act_copy->setStatusTip(tr("Copy the current selection's contents to the "
    //                             "clipboard"));
    //    //    connect(act_copy, SIGNAL(triggered()), this, SLOT(copy()));

    act_paste = new QAction(tr("&Paste"), this);
    //    act_paste->setShortcuts(QKeySequence::Paste);
    //    act_paste->setStatusTip(tr("Paste the clipboard's contents into the current "
    //                              "selection"));
    //    connect(act_paste, SIGNAL(triggered()), this, SLOT(paste()));
    act_addBookmarks = new QAction(tr("&Add bookmarks"), this);
    connect(act_addBookmarks, SIGNAL(triggered()), this, SLOT(addBookmark()));
}
//------------------------------------------------------------------------------
void ModuleViewer::showContextMenu(QPoint pt)
{
    //    QMenu *menu = ui->viewer->createStandardContextMenu();
    QMenu *menu = new QMenu(this);
    menu->addAction(act_cut);
    menu->addAction(act_copy);
    menu->addAction(act_paste);

    menu->addAction(act_addBookmarks);

    menu->addSeparator();
    //    QString str = m_curBook + ":" + m_curChapter;
    QAction *act = new QAction(QString(m_curModule
                                       + " : "
                                       + m_curBook
                                       + " : "
                                       + m_curChapter), this);

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
     *
     *
     *Для стронгов:
     *Запоминаем текст с числами
     *Убираем числа из текста и показываем.
     *Когда пользователь ведет мышь по строке n
     *Берем из сохранившего текста нужную строку и делаем в ней замену стронгов
     *По номеру колонки определяем нужное слово и показываем уже стронги
     */

    // брать параметр стронгов из файла конфигурации
    m_strong = false;

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
                        if (m_strong)
                        {
                            m_backupChapter = str;
                            //                            str.replace(",", ", ")
                            //                                    .replace(".", ". ");
                            //                            str = fillStrongList(str);
                        }
                        ui->viewer->setText(str);
                    }
                    xmlReader.readNext();
                }
            }
        }
        xmlReader.readNext();
    }
    m_curBook = nameBook;
    m_curPath = pathToFile;
    m_curChapter = QString::number(numberchapter);
    ui->LAStatus->setText(m_curModule + " : " + m_curBook + " : " + m_curChapter );

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
    //    ui->viewer->setMouseTracking(true);
    //    ui->viewer->viewport()->setMouseTracking(true);

    ui->viewer->viewport()->installEventFilter(this);



    //    setMouseTracking(true);
    loadViewSettings();


    connect(ui->toolClose, SIGNAL(clicked()), ui->frameFind, SLOT(hide()));
    connect(ui->toolPrevious, SIGNAL(clicked()), this, SLOT(findPrevious()));
    connect(ui->toolNext, SIGNAL(clicked()), this, SLOT(findNext()));
    connect(ui->LEEditFind, SIGNAL(returnPressed()), this, SLOT(findNext()));
    connect(ui->LEEditFind, SIGNAL(textEdited(const QString&)), this, SLOT(find(QString)));
    ui->frameFind -> setVisible(false);
    ui->LAWrapped -> setVisible(false);

    autoHideTimer = new QTimer(this);
    autoHideTimer -> setInterval(5000);
    autoHideTimer -> setSingleShot(true);
    QObject::connect(autoHideTimer, SIGNAL(timeout()), ui->frameFind, SLOT(hide()));

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
    m_curModule = newModule;
}
//------------------------------------------------------------------------------
QString ModuleViewer::getModuleName()
{
    return m_curModule;
}
//------------------------------------------------------------------------------
void ModuleViewer::setBookName(QString newBook)
{
    m_curBook = newBook;
}
//------------------------------------------------------------------------------
QString ModuleViewer::getBookName()
{
    return m_curBook;
}
//------------------------------------------------------------------------------
void ModuleViewer::setChapterValue(QString newChap)
{
    m_curChapter = newChap;
}
//------------------------------------------------------------------------------
QString ModuleViewer::getChapterValue()
{
    return m_curChapter;
}
//------------------------------------------------------------------------------
void ModuleViewer::setPath(QString newPath)
{
    m_curPath = newPath;
}
//------------------------------------------------------------------------------
QString ModuleViewer::getPath()
{
    return m_curPath;
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
    QString path = m_curPath;
    path.replace("text.xml", "notes.xml");
    emit SIGNAL_ShowNoteList(m_curModule,
                             m_curBook,
                             m_curChapter,
                             path,
                             QString::number(lastSelectLineFirst));

}
//------------------------------------------------------------------------------
//bool ModuleViewer::event(QEvent *e)
//{
//    if(e->type() == QEvent::ToolTip)
//    {
//        QHelpEvent *tipEvent = static_cast<QHelpEvent*>(e);
//        QTextCursor wordCursor = ui->viewer->cursorForPosition(tipEvent->pos());
//        wordCursor.movePosition(QTextCursor::StartOfWord);

//        QString str;
//        /* хотел сделать что-то наподобие такого:

//                while(wordCursor.currentChar() != ' ')
//                         str.append(wordCursor.currentChar());
//                         wordCursor.movePosition(QTextCursor::NextCharacter);
//                но подобной currentChar() функции не нашел...
//                */

//        QTextBlock block     = wordCursor.block();
//        const QString sText  = block.text();
//        //            if (!sText.size())
//        //                return 0;
//        int nCurCharPos = wordCursor.position() - block.position();
////        return sText[nCurCharPos];  // символ за курсором
//        str = sText[nCurCharPos];



//        myDebug() << str;
//        if(!str.isEmpty())
//        {
//            QToolTip::showText(tipEvent->globalPos(), str);
//        }
//        else QToolTip::hideText();
//    }

//        if (event->type() == QEvent::MouseMove)
//        {
//            /// Добавить задержку
//            QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
//            QPoint pt = mouseEvent->pos();

//    //        QMouseEvent *e = new QMouseEvent(QEvent::MouseButtonDblClick, pt, Qt::LeftButton, Qt::NoButton,
//    //                                         Qt::NoModifier);
//    //                QApplication::postEvent(ui->viewer->viewport(), e);

//    //        QTextCursor cursor = ui->viewer->textCursor();
//    //        cursor.select(QTextCursor::WordUnderCursor);
//    //        setCurLine();

//    //        e = new QMouseEvent(QEvent::MouseButtonRelease, pt, Qt::LeftButton, Qt::NoButton,
//    //                                         Qt::NoModifier);
//    //                QApplication::postEvent(ui->viewer->viewport(), e);

//    //        myDebug() << cursor.blockNumber() << cursor.columnNumber();
//            return true;
//        }


//    //    return ui->viewer->event(e);
//    return QObject::eventFilter(ui->viewer, e);
//}
//------------------------------------------------------------------------------
bool ModuleViewer::event(QEvent* event)
{
    if (event->type() == QEvent::ToolTip)
    {
        QHelpEvent* helpEvent = static_cast<QHelpEvent*>(event);
        QTextCursor cursor = ui->viewer->cursorForPosition(helpEvent->pos() - ui->viewer->pos());
//        QTextCursor cursor = ui->viewer->cursor();

        cursor.select(QTextCursor::WordUnderCursor);
        if (!cursor.selectedText().isEmpty())
        {
//            myDebug() << helpEvent->pos() << cursor.selectedText();
            QToolTip::showText(helpEvent->globalPos(), cursor.selectedText());
        }
        else
        {
            QToolTip::hideText();
        }
        return true;
    }
    return QObject::eventFilter(ui->viewer, event);
    //    return QTextEdit::event(event);
}
//------------------------------------------------------------------------------
//bool ModuleViewer::eventFilter(QObject *obj, QEvent *event)
//{


////    if(e->type() == QEvent::ToolTip)
////    {
////               QHelpEvent *tipEvent = static_cast<QHelpEvent*>(e);
////               QTextCursor wordCursor = cursorForPosition(tipEvent->pos());
////               wordCursor.movePosition(QTextCursor::StartOfWord);
////               /* хотел сделать что-то наподобие такого:
////               QString str;
////               while(wordCursor.currentChar() != ' ')
////                        str.append(wordCursor.currentChar());
////                        wordCursor.movePosition(QTextCursor::NextCharacter);
////               но подобной currentChar() функции не нашел...
////               */
////               if(!str.isEmpty())
////               {
////                                  QToolTip::showText(tipEvent->globalPos(), str);
////        }
////               else QToolTip::hideText();
////    }
////    return QTextEdit::event(e);


////    if (obj == ui->LEEditFind)
////    {
////        if (event -> type() == QEvent::FocusIn && autoHideTimer -> isActive())
////            autoHideTimer -> stop();
////    }
////    else if (event -> type() == QEvent::KeyPress && ui->frameFind -> isVisible())
////    {
////        QKeyEvent *ke = static_cast<QKeyEvent *>(event);
////        if (ke -> key() == Qt::Key_Space)
////        {
////            keyPressEvent(ke);
////            return true;
////        }
////    }

//    if (event->type() == QEvent::MouseMove)
//    {
//        /// Добавить задержку
//        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
//        QPoint pt = mouseEvent->pos();

//        QMouseEvent *e = new QMouseEvent(QEvent::MouseButtonDblClick, pt, Qt::LeftButton, Qt::NoButton,
//                                         Qt::NoModifier);
//                QApplication::postEvent(ui->viewer->viewport(), e);

//        QTextCursor cursor = ui->viewer->textCursor();
//        cursor.select(QTextCursor::WordUnderCursor);
//        setCurLine();

//        e = new QMouseEvent(QEvent::MouseButtonRelease, pt, Qt::LeftButton, Qt::NoButton,
//                                         Qt::NoModifier);
//                QApplication::postEvent(ui->viewer->viewport(), e);

//        myDebug() << cursor.blockNumber() << cursor.columnNumber();
//        return true;
//    }

//    return QObject::eventFilter(obj, event);

//}
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

    QString path = m_curPath;
    //        fileName << "/home/files/Documents/Bible/unrar/my/BIBLEQT.INI";
    //    QString path = "/home/files/Documents/Bible/strong/strong/"
    //    QString path = m_curPath;
    //    path.replace("text.xml", "notes.xml");


    //    emit showNoteList(m_curModule,
    //                      m_curBook,
    //                      m_curChapter,
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
void ModuleViewer::retranslate()
{
    ui->retranslateUi(this);
}
//------------------------------------------------------------------------------
void ModuleViewer::updateFontSettings()
{
    loadViewSettings();
    showChapter(m_curPath, m_curBook, m_curChapter.toInt());

    //    ui->viewer->reload();
    //    ui->viewer->update();
}
//------------------------------------------------------------------------------
void ModuleViewer::addBookmark()
{
    QString bookm = m_curModule + " : "
            + m_curBook + " : "
            + m_curChapter;
    emit SIGNAL_AddNewBookmark(bookm);
}
//------------------------------------------------------------------------------
void ModuleViewer::findNext()
{
    find(ui->LEEditFind-> text(), true, false);
}
//------------------------------------------------------------------------------
void ModuleViewer::findPrevious()
{
    find(ui->LEEditFind -> text(), false, true);
}
//------------------------------------------------------------------------------
void ModuleViewer::find()
{
    ui->frameFind -> show();
    ui->LEEditFind -> setFocus(Qt::ShortcutFocusReason);
    ui->LEEditFind -> selectAll();
    autoHideTimer -> stop();
}
//------------------------------------------------------------------------------
void ModuleViewer::find(QString ttf, bool forward, bool backward)
{
    QTextDocument *doc = ui->viewer->document();
    QString oldText = ui->LEEditFind -> text();
    QTextCursor c = ui->viewer->textCursor();
    QTextDocument::FindFlags options;
    QPalette p = ui->LEEditFind -> palette();
    p.setColor(QPalette::Active, QPalette::Base, Qt::white);

    if (c.hasSelection())
        c.setPosition(forward ? c.position() : c.anchor(), QTextCursor::MoveAnchor);

    QTextCursor newCursor = c;

    if (!ttf.isEmpty())
    {
        if (backward)
            options |= QTextDocument::FindBackward;

        if (ui->checkCase -> isChecked())
            options |= QTextDocument::FindCaseSensitively;

        if (ui->checkWholeWords -> isChecked())
            options |= QTextDocument::FindWholeWords;

        newCursor = doc -> find(ttf, c, options);
        ui->LAWrapped -> hide();

        if (newCursor.isNull())
        {
            QTextCursor ac(doc);
            ac.movePosition(options & QTextDocument::FindBackward
                            ? QTextCursor::End : QTextCursor::Start);
            newCursor = doc -> find(ttf, ac, options);
            if (newCursor.isNull())
            {
                p.setColor(QPalette::Active, QPalette::Base, QColor(255, 102, 102));
                newCursor = c;
            } else
                ui->LAWrapped -> show();
        }
    }

    if (!ui->frameFind -> isVisible())
        ui->frameFind -> show();
    ui->viewer-> setTextCursor(newCursor);
    ui->LEEditFind -> setPalette(p);
    if (!ui->LEEditFind -> hasFocus())
        autoHideTimer -> start();
}
//------------------------------------------------------------------------------
