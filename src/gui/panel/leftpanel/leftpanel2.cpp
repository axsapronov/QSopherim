#include "leftpanel2.h"
#include "ui_leftpanel2.h"

#include "filecommon.h"
#include "debughelper.h"
#include "strongcommon.h"

#include "defines.h"

#include <QDate>




// panel for info:
// strongs , journal, and other

LeftPanel2::LeftPanel2(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::LeftPanel2)
{
    ui->setupUi(this);
    init();
    createConnects();

    setReadingPlanForCurrentDay();
}
//------------------------------------------------------------------------------
LeftPanel2::~LeftPanel2()
{
    delete ui;
}
//------------------------------------------------------------------------------
void LeftPanel2::init()
{
    //    QString path = m_curPath;
    if (Config::configuration()->getStrongHebrew().isEmpty())
    {
        m_strongHebrew_on = false;
    }
    else
    {
        getMapStrongs(Config::configuration()->getStrongHebrew(), m_mapStrongHebrew);
        m_strongHebrew_on = true;
    }

    if (Config::configuration()->getStrongGreek().isEmpty())
    {
        m_strongGreek_on = false;
    }
    else
    {
        getMapStrongs(Config::configuration()->getStrongGreek(), m_mapStrongGreek);
        m_strongGreek_on = true;
    }

    m_journalList.clear();
    sUpdateGUIDayMode();
    sUpdateGUIFont();

}
//------------------------------------------------------------------------------
void LeftPanel2::createConnects()
{
    connect(ui->ListViewJournal, SIGNAL(clicked(QModelIndex)), SLOT(showChapterFromJournal(QModelIndex)));
    connect(ui->ListViewReadingPlan, SIGNAL(clicked(QModelIndex)), SLOT(showChapterFromPlan(QModelIndex)));
}
//------------------------------------------------------------------------------
void LeftPanel2::retranslate()
{
    ui->retranslateUi(this);
}
//------------------------------------------------------------------------------
void LeftPanel2::addRecordToJournal(QString modulename,
                                    QString bookname,
                                    QString chaptervalue)
{

    QString t_record =
            modulename + ":" +
            bookname + ":" +
            chaptervalue;

    QStandardItemModel *model = new QStandardItemModel(m_journalList.size(), 0);
    model->clear();
    ui->ListViewJournal->setModel(model);

    QStringList t_list;
    t_list << t_record;

    int count = 10;

    for (int i = 0; i < count - 1 && i < m_journalList.size(); i++)
    {
        t_list << m_journalList.at(i);
        // add to model
        model->appendRow( new QStandardItem(t_list.at(i)));
    }
    //add to model last elem
    model->appendRow( new QStandardItem(t_list.at(t_list.size() - 1)));

    // or this - this is add to model
    //    for (int i = 0; i < count && i < t_list.size(); i++)
    //    {
    //        model->appendRow( new QStandardItem(t_list.at(i)));
    //    }

    m_journalList = t_list;
    Config::configuration()->setJournalHistory(&m_journalList);
}
//------------------------------------------------------------------------------
void LeftPanel2::showChapterFromJournal(QModelIndex ind)
{
    // parse journal item
    // get module name, book name, chapter value
    QString str = ui->ListViewJournal->model()->data(ind).toString();
    int pos = str.indexOf(":");

    QString moduleName = QString(str).mid(0, pos);
    str.remove(moduleName + ":");
    pos = str.indexOf(":");
    QString bookName = QString(str).mid(0, pos);
    str.remove(bookName + ":");
    QString chapterValue = str;

    emit SIGNAL_ShowChapterFrom(moduleName, bookName, chapterValue);
}
//------------------------------------------------------------------------------
void LeftPanel2::showChapterFromPlan(QModelIndex ind)
{
    // parse journal item
    // get module name, book name, chapter value
    QString str = ui->ListViewReadingPlan->model()->data(ind).toString();

    int pos = str.indexOf(":");
    QString bookName = QString(str).mid(0, pos);
    str.remove(bookName + ":");
    pos = str.indexOf(":");
    QString chapterValue = QString(str).mid(0, pos);

    if (Config::configuration()->isExistLastChapter())
        emit SIGNAL_ShowChapterFrom(Config::configuration()->getLastModule(), bookName, chapterValue);
}
//------------------------------------------------------------------------------
void LeftPanel2::showStrong(QString number)
{
    if (getTypeStrong() == "Hebrew"
            and m_strongHebrew_on)
    {
        ui->textBrStrong->setFont(Config::configuration()->getGUIMapFont()["FontStrongsHebrew"]);
        QString str =
                tr("Strong number: ")
                + "<b>" + number + "</b>"
                + "\n<br>"
                + m_mapStrongHebrew[number.toInt()].text;
        ui->textBrStrong->setHtml(str);
    }

    if (getTypeStrong() == "Greek"
            and m_strongHebrew_on)
    {
        ui->textBrStrong->setFont(Config::configuration()->getGUIMapFont()["FontStrongsGreek"]);
        QString str =
                tr("Strong number: ")
                + "<b>" + number + "</b>"
                + "\n<br>"
                + m_mapStrongGreek[number.toInt()].text;
        ui->textBrStrong->setHtml(str);
    }
}
//------------------------------------------------------------------------------
void LeftPanel2::sSetStrongHebrew(QString path)
{
    getMapStrongs(path, m_mapStrongHebrew );
    m_strongHebrew_on = true;
}
//------------------------------------------------------------------------------
void LeftPanel2::sSetStrongGreek(QString path)
{
    getMapStrongs(path, m_mapStrongGreek);
    m_strongGreek_on = true;
}
//------------------------------------------------------------------------------
void LeftPanel2::loadJournal()
{
    m_journalList = *(Config::configuration()->getJournalHistory());
    QStandardItemModel *model = new QStandardItemModel(m_journalList.size(), 0);
    model->clear();
    ui->ListViewJournal->setModel(model);

    int count = 10;
    for (int i = 0; i < count && i < m_journalList.size(); i++)
    {
        // add to model
        model->appendRow( new QStandardItem(m_journalList.at(i)));
    }
}
//------------------------------------------------------------------------------
void LeftPanel2::sUpdateGUIDayMode()
{
    QPalette p = ui->ListViewJournal->palette();
    if (Config::configuration()->getDayMode())
    {
        p.setColor(QPalette::Base, GL_COLOR_DAY);
    }
    else
    {
        p.setColor(QPalette::Base, GL_COLOR_NIGHT);
    }
    ui->ListViewJournal->setPalette(p);
    ui->textBrStrong->setPalette(p);
    ui->ListViewReadingPlan->setPalette(p);
}
//------------------------------------------------------------------------------
void LeftPanel2::setReadingPlanForCurrentDay()
{
    QDate t_date;
    m_readingPlanList = getReadinPlanForDay(t_date.currentDate().month(), t_date.currentDate().day(), "family");

    QStandardItemModel *model = new QStandardItemModel(m_readingPlanList.size(), 0);
    model->clear();
    ui->ListViewReadingPlan->setModel(model);

    for (int i = 0; i < m_readingPlanList.size(); i++)
    {
        // add to model
        model->appendRow( new QStandardItem(m_readingPlanList.at(i)));
    }
}
//------------------------------------------------------------------------------
void LeftPanel2::sUpdateGUIFont()
{
    ui->ListViewJournal->setFont(Config::configuration()->getGUIMapFont()["FontJournal"]);
}
//------------------------------------------------------------------------------
