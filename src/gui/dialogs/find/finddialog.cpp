#include "finddialog.h"
#include "ui_finddialog.h"

#include "config.h"
#include "debughelper.h"
#include "filecommon.h"
#include "stringcommon.h"

#include "defines.h" // GL_

#include <QStandardItemModel>

FindDialog::FindDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindDialog)
{
    ui->setupUi(this);

    setWindowTitle(QString(tr("Find") + " | %1 - %2").arg(GL_PROG_NAME).arg(GL_PROG_VERSION_STR));

    init();
}
//------------------------------------------------------------------------------
FindDialog::~FindDialog()
{
    ui->tableFiles->model()->deleteLater();

    delete ui;
}
//------------------------------------------------------------------------------
void FindDialog::preShowDialog()
{
    m_currentDir.setPath(Config::configuration()->getDataPath() + GL_MODULE_PATH + "/");
    updateComBModule();
}
//------------------------------------------------------------------------------
void FindDialog::init()
{
    ui->tableFiles->setColumnWidth(0, 400); // module name
    ui->tableFiles->setColumnWidth(1, 150); // book name
    ui->tableFiles->setColumnWidth(2, 110); // chapter value
    ui->tableFiles->setColumnWidth(3, 110); // type module
    createConnects();
}
//------------------------------------------------------------------------------
void FindDialog::createConnects()
{
    connect(ui->pBFind, SIGNAL(clicked()), SLOT(find()));
    connect(ui->comBModule, SIGNAL(activated(int)), SLOT(updateComBBook(int)));
    connect(ui->comBBook, SIGNAL(activated(int)), SLOT(updateComBChapter(int)));
    connect(ui->tableFiles, SIGNAL(activated(QModelIndex)), SLOT(showChapter(QModelIndex)));
}
//------------------------------------------------------------------------------
void FindDialog::find()
{
    if (!ui->LEFind->text().isEmpty())
    {
        ui->tableFiles->setRowCount(0);
        QString fileName = "*";
        QString text = ui->LEFind->text();

        QStringList files;
        if (fileName.isEmpty())
            fileName = "*";
        files = recursiveFind(getPathFind());


        FindData find;
        if (!text.isEmpty())
            find = findFiles(files, text);

        //        myDebug() << files.size() << find.files.size();

        SearchData data;
        data.files = find.files;
        //        data.verse = find.verse;
        data.books = find.books;
        data.chapter = find.chapters;
        updateItemforTable(data);
        showFiles(data);
        QMessageBox::information(this, tr("Search is completed"), tr("Search is completed"));
    }
}
//------------------------------------------------------------------------------
FindData FindDialog::findFiles(const QStringList &files, const QString &text)
{
    // доставать текст по главам и определять там номер главы и стиха
    FindData output;
    QProgressDialog progressDialog(this);
    progressDialog.setCancelButtonText(tr("&Cancel"));
    progressDialog.setRange(0, files.size());
    progressDialog.setWindowTitle(tr("Find Files"));

    QStringList foundFiles;
    //    QStringList verses;
    QStringList books;
    QStringList chapters;

    QString curBook;
    QString curChapter;

    for (int i = 0; i < files.size(); ++i)
    {
        progressDialog.setValue(i);
        progressDialog.setLabelText(tr("Searching file number %1 of %2...")
                                    .arg(i).arg(files.size()));
        qApp->processEvents();

        if (progressDialog.wasCanceled())
            break;

        if (files.at(i).indexOf(GL_MODULE_PATH) == -1)
            continue;

        QFile file(m_currentDir.absoluteFilePath(files[i]));
        if (file.open(QIODevice::ReadOnly))
        {
            QString line;
            QTextStream in(&file);
            while (!in.atEnd())
            {
                if (progressDialog.wasCanceled())
                    break;
                line = in.readLine();
                if (line.indexOf("<book") >= 0 )
                    curBook = getBookNameFromStr(&line);

                if (line.indexOf("<chapter") >= 0 )
                    curChapter = getChapterNameFromStr(&line);

                if (line.contains(text))
                {
                    if (
                            (
                                ui->comBBook->currentIndex() == 0
                                or
                                ui->comBBook->currentText() == curBook
                                )
                            and
                            (
                                ui->comBChapter->currentIndex() == 0
                                or
                                ui->comBChapter->currentText() == curChapter
                                )
                            )
                    {
                        if (curChapter.isEmpty())
                            continue;
                        foundFiles << files[i];
                        books << curBook;
                        chapters << curChapter;
                    }
                    //                    verses << getIntVerse(line);
                    //                    verses << QString::number(1);
                }
            }
        }
    }
    output.files = foundFiles;
    //    output.verse = verses;
    output.books = books;
    output.chapters = chapters;
    return output;
}
//------------------------------------------------------------------------------
void FindDialog::updateInfo()
{

}
//------------------------------------------------------------------------------
void FindDialog::updateComBModule()
{
    // fill combox modules names
    ui->comBModule->clear();
    QStringList listModules;
    listModules << tr("All modules");

    // get all modules
    QStringList t_list = getListModulesFromPath(Config::configuration()->getDataPath() + GL_MODULE_PATH);
    QString t_moduleName;

    for (int i = 0; i < t_list.size(); i++)
    {
        t_moduleName = getModuleNameFromIni(t_list.at(i));
        listModules << t_moduleName;
    }

    ui->comBModule->addItems(listModules);
}
//------------------------------------------------------------------------------
void FindDialog::updateComBBook(int f_moduleIndex)
{
    QStringList t_list;
    t_list << tr("All books");
    if (f_moduleIndex != 0)
    {
        t_list.append(getBookList(Config::configuration()->getDataPath() + GL_MODULE_PATH +
                                  Config::configuration()->getListModulesFromMap
                                  (
                                      Config::configuration()->getTypeOfModule(ui->comBModule->currentText())
                                      )
                                  ->getModuleWithName(ui->comBModule->currentText())
                                  ->getModulePath()));

    }

    ui->comBBook->clear();
    ui->comBBook->addItems(t_list);

    if (f_moduleIndex != 0)
        updateComBChapter(1);
}
//------------------------------------------------------------------------------
void FindDialog::updateComBChapter(int f_bookIndex)
{
    QStringList listChapters;
    listChapters << tr("All chapters");
    if (f_bookIndex != 0)
    {
        QHash<QString, int> t_hash = getNumberOfChaptersInBook
                (
                    Config::configuration()->getDataPath() + GL_MODULE_PATH +
                                                      Config::configuration()->getListModulesFromMap
                                                      (
                                                          Config::configuration()->getTypeOfModule(ui->comBModule->currentText())
                                                          )
                                                      ->getModuleWithName(ui->comBModule->currentText())
                                                      ->getModulePath()
                    );

        int countChapters = t_hash[ui->comBBook->currentText()];

        for (int i = 0; i < countChapters; i++)
        {
            listChapters << QString::number(i + 1);
        }
    }

    ui->comBChapter->clear();
    ui->comBChapter->addItems(listChapters);
}
//------------------------------------------------------------------------------
void FindDialog::accept ()
{
    ui->LEFind->setText("");
    ui->tableFiles->clearContents();
    QWidget::hide();
}
//------------------------------------------------------------------------------
void FindDialog::reject ()
{
    ui->LEFind->setText("");
    ui->tableFiles->clearContents();
    QWidget::hide();
}
//------------------------------------------------------------------------------
QString FindDialog::getPathFind()
{
    QString str;
    str = Config::configuration()->getDataPath() + GL_MODULE_PATH + "/";

    if (ui->comBModule->currentIndex() != 0)
        str.append(Config::configuration()->getListModulesFromMap(Config::configuration()->getTypeOfModule(ui->comBModule->currentText()))
                   ->getModuleWithName(ui->comBModule->currentText())->getModulePath().remove("module" + GL_FORMAT_MODULE));
    else
        str.append("");

    return str;
}
//------------------------------------------------------------------------------
void FindDialog::showFiles(const SearchData &data)
{
    for (int i = 0; i < data.files.size(); ++i)
    {
        QTableWidgetItem fileNameItem = QTableWidgetItem(data.files[i]);
        fileNameItem.setFlags(fileNameItem.flags() ^ Qt::ItemIsEditable);

        QTableWidgetItem *bookItem = new QTableWidgetItem(data.books[i]);
        bookItem->setFlags(bookItem->flags() ^ Qt::ItemIsEditable);

        QTableWidgetItem *moduleItem = new QTableWidgetItem(data.modules[i]);
        moduleItem->setFlags(moduleItem->flags() ^ Qt::ItemIsEditable);

        //        QTableWidgetItem *verseItem = new QTableWidgetItem(data.verse[i]);
        //        verseItem->setFlags(verseItem->flags() ^ Qt::ItemIsEditable);

        QTableWidgetItem *chapterItem = new QTableWidgetItem(data.chapter[i]);
        chapterItem->setFlags(chapterItem->flags() ^ Qt::ItemIsEditable);

        QTableWidgetItem *typeItem = new QTableWidgetItem(data.type[i]);
        typeItem->setFlags(typeItem->flags() ^ Qt::ItemIsEditable);

        int row = ui->tableFiles->rowCount();
        ui->tableFiles->insertRow(row);

        ui->tableFiles->setItem(row, 0, moduleItem);
        ui->tableFiles->setItem(row, 1, bookItem);
        ui->tableFiles->setItem(row, 2, chapterItem);
        //        ui->tableFiles->setItem(row, 3, verseItem);
        ui->tableFiles->setItem(row, 3, typeItem);
    }
    ui->tableFiles->resizeColumnsToContents();

    ui->LAFilesFoundLabel->setText(tr("%1 file(s) found").arg(data.files.size()) +
                                   tr(" (Double click on a file to open it)"));
}
//------------------------------------------------------------------------------
void FindDialog::updateItemforTable(SearchData &data)
{
    QStringList lib[5];
    QString app[5];

    QString prev;
    QString curModuleName;

    for (int i = 0; i < data.files.size(); i++)
    {
        QString str = data.files.at(i);
        QStringList list;
        // path to file text.qst
        list << str.split("/");
        // case intens
        app[2] = list.last().remove(".htm").remove(".html").remove(".HTML").remove(".HTM");

        //module name
        list.removeLast();
        if (prev != data.files.at(i))
        {
            prev = data.files.at(i);
            QString t_str = data.files.at(i);
            t_str.replace("text" + GL_FORMAT_TEXT, "module" + GL_FORMAT_MODULE);
            curModuleName = getModuleNameFromIni(t_str);
        }
        app[1] = curModuleName;

        //type module
        list.removeLast();
        app[0] = list.last();

        // book name
        app[2] = data.books.at(i);

        // chapter name
        app[3] = data.chapter.at(i);

        lib[0] << app[0];
        lib[1] << app[1];
        lib[2] << app[2];
        lib[3] << app[3];
        lib[4] << app[4];
    }
    data.type = lib[0];
    data.modules = lib[1];
    data.books = lib[2];
    data.chapter = lib[3];
    data.files = lib[4];
}
//------------------------------------------------------------------------------
void FindDialog::showChapter(QModelIndex f_ind)
{
    QString module = ui->tableFiles->model()->index(f_ind.row(), 0).data().toString();
    QString book = ui->tableFiles->model()->index(f_ind.row(), 1).data().toString();
    QString chapter = ui->tableFiles->model()->index(f_ind.row(), 2).data().toString();
    QString type = ui->tableFiles->model()->index(f_ind.row(), 3).data().toString();

    if (type == "bible" or type == "apocrypha" or type == "book")
    {
        emit SIGNAL_ShowChapter(module, book, chapter);
        emit SIGNAL_UpdateGUI();
    }
}
//------------------------------------------------------------------------------


