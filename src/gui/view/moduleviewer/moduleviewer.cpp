#include "moduleviewer.h"
#include "ui_moduleviewer.h"
#include "debughelper.h"
#include "cnode.h"

#include "stringcommon.h"
#include "filecommon.h"
#include "defines.h"


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
    delete ui;
}
//------------------------------------------------------------------------------
void ModuleViewer::createActions()
{
    act_addBookmarks = new QAction(tr("&Add bookmarks"), this);
    connect(act_addBookmarks, SIGNAL(triggered()), this, SLOT(sAddBookmark()));


    act_addNote = new QAction(tr("&Add note"), this);
    connect(act_addNote, SIGNAL(triggered()), this, SLOT(sAddNote()));
}
//------------------------------------------------------------------------------
void ModuleViewer::sShowContextMenu(QPoint pt)
{
    QMenu *menu = ui->viewer->createStandardContextMenu();
    menu->addSeparator();
    menu->addAction(act_addBookmarks);
    menu->addAction(act_addNote);
    menu->addSeparator();


    if (!m_curBook.isEmpty())
    {
        QAction *act = new QAction(QString(m_curModule
                                           + " : "
                                           + m_curBook
                                           + " : "
                                           + m_curChapter), this);
        menu->addAction(act);
    }
    menu->exec(ui->viewer->mapToGlobal(pt));
}
//------------------------------------------------------------------------------
ModuleViewer *ModuleViewer::viewer()
{
    Q_ASSERT( static_viewer );
    return static_viewer;
}
//------------------------------------------------------------------------------
void ModuleViewer::showChapter(const QString f_module, const QString f_nameBook, const int f_numberchapter)
{
//    myDebug() << f_module << f_nameBook << f_numberchapter;
    QString pathToFile = Config::configuration()->getAppDir() +
            Config::configuration()->getListBibles()->getModuleWithName(f_module)->getModulePath();

    pathToFile.replace("module" + GL_FORMAT_MODULE
                       , "text" + GL_FORMAT_TEXT);
//    myDebug() << f_module << pathToFile << f_nameBook << f_numberchapter;

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
            if (attrs.value("name") == f_nameBook)
            {
                while(!xmlReader.atEnd() and !flag)
                {
                    if (xmlReader.attributes().value("number") ==
                            QString::number(f_numberchapter))
                    {
                        flag = true;
                        QString str = xmlReader.readElementText();
                        str.remove("    ");

                        // gen colors (divs)
                        if (Config::configuration()->getOptionChangeTextColor())
                            genInterchangeableColorsIntext(&str, 5);
                        else
                            genInterchangeableColorsIntext(&str, 1);

                        if (m_strong)
                        {
                            m_backupChapter = str;

                            ////                            myDebug() << "yes" << str;
                            //                            QRegExp rx("(\\d+)");
                            //                            int pos = 0;
                            //                            while ((pos = rx.indexIn(str, pos)) != -1)
                            //                            {
                            //                                //        list << rx.cap(1);
                            //                                myDebug() << "1";
                            //                                str.replace(rx.cap(1), "<sup>" + rx.cap(1) + "</sup>");
                            //                                pos += rx.matchedLength() + 11;
                            //                            }
                            //                            myDebug() << "yes";
                        }
                        ui->viewer->setText(str);
                    }
                    xmlReader.readNext();
                }
            }
        }
        xmlReader.readNext();
    }
    m_curBook = f_nameBook;
    m_curPath = pathToFile;
    m_curChapter = QString::number(f_numberchapter);

    if (!m_curBook.isEmpty())
    {
        ui->LAStatus->setText(m_curModule + " : " + m_curBook + " : " + m_curChapter );

        // make 3 in 1?
        Config::configuration()->setLastChapter(m_curChapter);
        Config::configuration()->setLastBook(m_curBook);
        Config::configuration()->setLastModule(m_curModule);
        Config::configuration()->setLastType(
                    Config::configuration()->getListBibles()->getModuleWithName(m_curModule)->getModuleType()
                    );
    }
    // todo
    emit SIGNAL_ShowChapterFinish();
}
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

    ui->viewer->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->viewer->viewport()->installEventFilter(this);

    setStyleSettings();

    connect(ui->toolClose, SIGNAL(clicked()), ui->frameFind, SLOT(hide()));
    connect(ui->toolPrevious, SIGNAL(clicked()), this, SLOT(findPrevious()));
    connect(ui->toolNext, SIGNAL(clicked()), this, SLOT(findNext()));
    connect(ui->LEEditFind, SIGNAL(returnPressed()), this, SLOT(findNext()));
    connect(ui->LEEditFind, SIGNAL(textEdited(const QString&)), this, SLOT(sFind(QString)));
    ui->frameFind -> setVisible(false);
    ui->LAWrapped -> setVisible(false);

    autoHideTimer = new QTimer(this);
    autoHideTimer -> setInterval(5000);
    autoHideTimer -> setSingleShot(true);
    QObject::connect(autoHideTimer, SIGNAL(timeout()), ui->frameFind, SLOT(hide()));

    connect(ui->viewer, SIGNAL(customContextMenuRequested(QPoint)),
            this,SLOT(sShowContextMenu(QPoint)));

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
    path.replace("text" + GL_FORMAT_TEXT, "notes.xml");
    emit SIGNAL_ShowNoteList(m_curModule,
                             m_curBook,
                             m_curChapter,
                             path,
                             QString::number(m_lastLine));

}
//------------------------------------------------------------------------------
bool ModuleViewer::event(QEvent* event)
{
    if (event->type() == QEvent::ToolTip)
    {
        QHelpEvent* helpEvent = static_cast<QHelpEvent*>(event);
        QTextCursor cursor = ui->viewer->cursorForPosition(helpEvent->pos() - ui->viewer->pos());
        cursor.select(QTextCursor::WordUnderCursor);
        if (!cursor.selectedText().isEmpty())
        {
            if (cursor.selectedText().indexOf("0") >= 0 )
            {
                //QToolTip::showText(helpEvent->globalPos(), cursor.selectedText());
                emit SIGNAL_ShowStrong(cursor.selectedText());
            }



            // show notes
            m_lastLine = cursor.blockNumber() + 1;
            showNoteList();
        }
        else
        {
            QToolTip::hideText();
        }

        return true;
    }
    return QObject::eventFilter(ui->viewer, event);
}
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
    setStyleSettings();
    if (!m_curChapter.isEmpty())
        showChapter(m_curModule, m_curBook, m_curChapter.toInt());
}
//------------------------------------------------------------------------------
void ModuleViewer::sAddBookmark()
{
    QString bookm = Config::configuration()->getLastModule() + " : "
            + Config::configuration()->getLastModule() + " : "
            + Config::configuration()->getLastChapter();
    emit SIGNAL_AddNewBookmark(bookm);
}
//------------------------------------------------------------------------------
void ModuleViewer::findNext()
{
    sFind(ui->LEEditFind-> text(), true, false);
}
//------------------------------------------------------------------------------
void ModuleViewer::findPrevious()
{
    sFind(ui->LEEditFind -> text(), false, true);
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
void ModuleViewer::sFind(QString ttf, bool forward, bool backward)
{
    QTextDocument *doc = ui->viewer->document();
    //    QString oldText = ui->LEEditFind -> text();
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
void ModuleViewer::sAddNote()
{
    emit SIGNAL_AddNote();
}
//------------------------------------------------------------------------------
QString ModuleViewer::getLastNumberLine()
{
    return QString::number(m_lastLine);
}
//------------------------------------------------------------------------------
void ModuleViewer::setStyleSettings()
{
    int sum = 25;
    // 5
    int counstyles = 1;
    if (Config::configuration()->getOptionChangeTextColor())
        counstyles = 5;

    QString sheet;

    bool t_italic = Config::configuration()->getFontItalic();
    bool t_underline = Config::configuration()->getFontUnderline();
    bool t_bold = Config::configuration()->getFontBold();
    int t_fontsize = Config::configuration()->getFontSize();
    QString t_font = Config::configuration()->getFontFamily();


    for (int i = 0; i < counstyles; i++)
    {
        QColor color(
                    Config::configuration()->getFontColor().red() + sum * i * 1.2
                    , Config::configuration()->getFontColor().green() + sum * i
                    , Config::configuration()->getFontColor().blue() + sum * i
                    );

        QString t_color = QString("div#verse%1 {color: %2; font-size: %3pt; font-family: %4; ")
                .arg(i + 1) // 1 2 3 4 5
                .arg(color.name())
                .arg(t_fontsize )
                .arg(t_font);

        if (t_italic)
        {
            t_color.append("font-style: italic;");
        }
        if (t_underline)
        {
            t_color.append("text-decoration: line-through;");
        }
        if (t_bold)
        {
            t_color.append("font-weight: bold;");
        }

        t_color.append("}");
        sheet.append(t_color + "\n");
    }
    ui->viewer->document()->setDefaultStyleSheet(sheet);

    QPalette p = ui->viewer->palette();
    p.setColor(QPalette::Base, Config::configuration()->getViewerColor());
    ui->viewer->setPalette(p);
}
//------------------------------------------------------------------------------
void ModuleViewer::openLastChapter()
{
    if (!Config::configuration()->getLastChapter().isEmpty())
    {
        m_curModule = Config::configuration()->getLastModule();
        m_curBook = Config::configuration()->getLastBook();
        m_curChapter = Config::configuration()->getLastChapter();

        showChapter(m_curModule, m_curBook, m_curChapter.toInt());
    }
}
//------------------------------------------------------------------------------
