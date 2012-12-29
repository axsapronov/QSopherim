#include "finddialog.h"
#include "ui_finddialog.h"

#include "config.h"
#include "debughelper.h"
#include "filecommon.h"
#include "stringcommon.h"

FindDialog::FindDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindDialog)
{
    ui->setupUi(this);
    init();
}
//------------------------------------------------------------------------------
FindDialog::~FindDialog()
{
    ui->tableFiles->model()->deleteLater();

    delete ui;
}
//------------------------------------------------------------------------------
void FindDialog::init()
{
    createConnects();
    m_currentDir.setPath(Config::configuration()->getAppDir() + "/");
    ui->LEFind->setText("В начале");
}
//------------------------------------------------------------------------------
void FindDialog::createConnects()
{
    connect(ui->pBFind, SIGNAL(clicked()), SLOT(find()));
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

        myDebug() << files.size() << find.files.size();

        SearchData data;
        data.files = find.files;
        //        data.verse = find.verse;
        data.books = find.books;
        data.chapter = find.chapters;
        updateItemforTable(data);
        showFiles(data);
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
    QStringList verses;
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
                    foundFiles << files[i];
                    books << curBook;
                    chapters << curChapter;
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
void FindDialog::updateComBBook()
{

}
//------------------------------------------------------------------------------
void FindDialog::updateComBChapter(QString path)
{

}
//------------------------------------------------------------------------------
void FindDialog::removeItemListChapter(QStringList &list)
{

}
//------------------------------------------------------------------------------
void FindDialog::removeItemListBook(QStringList &list)
{

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
    str = Config::configuration()->getAppDir() + "/bible";

    if (ui->comBModule->currentIndex() != 0)
        str.append("/").append(ui->comBModule->currentText());
    return str;
}
//------------------------------------------------------------------------------
void FindDialog::showFiles(const SearchData &data)
{
    for (int i = 0; i < data.files.size(); ++i)
    {
        QTableWidgetItem *fileNameItem = new QTableWidgetItem(data.files[i]);
        fileNameItem->setFlags(fileNameItem->flags() ^ Qt::ItemIsEditable);

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
                                   (" (Double click on a file to open it)"));
}
//------------------------------------------------------------------------------
void FindDialog::updateItemforTable(SearchData &data)
{
    QStringList lib[5];
    QString app[5];

    for (int i = 0; i < data.files.size(); i++)
    {

        QString str = data.files.at(i);
        QStringList list;
        // path to file text.xml
        list << str.split("/");
        app[2] = list.last().remove(".htm").remove(".html").remove(".HTML").remove(".HTM");

        //module name
        list.removeLast();
        app[1] = list.last();

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
