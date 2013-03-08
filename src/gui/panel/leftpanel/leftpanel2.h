#ifndef LEFTPANEL2_H
#define LEFTPANEL2_H

#include <QDockWidget>
#include <QHash>
#include <QModelIndex>


#include <QStandardItem>
#include <QStandardItemModel>


class StrongList;

namespace Ui {
class LeftPanel2;
}

class LeftPanel2 : public QDockWidget
{
    Q_OBJECT

public:
    explicit LeftPanel2(QWidget *parent = 0);
    ~LeftPanel2();

    /*
     *retranslate gui
     */
    void retranslate();

    /**
     * @brief loadJournal
     */
    void loadJournal();



signals:
    void SIGNAL_ShowChapterFrom(QString, QString, QString);

public slots:


    void sSetStrongHebrew(QString path);
    void sSetStrongGreek(QString path);


    // journals slots
    void addRecordToJournal(QString modulename,
                            QString bookname,
                            QString chaptervalue);
private slots:


    void sUpdateGUIDayMode();

    void sUpdateGUIFont();


    void showStrong(QString number);

    /**
     \brief
     If select item in journal, then open this item
     */
    void showChapterFromJournal(QModelIndex);
    void showChapterFromPlan(QModelIndex);

private:
    Ui::LeftPanel2 *ui;

    QVector<StrongList> m_listStrongGreek;
    QVector<StrongList> m_listStrongHebrew;

    QMap<int, StrongList> m_mapStrongGreek;
    QMap<int, StrongList> m_mapStrongHebrew;

    QStringList m_journalList;
    QStringList m_readingPlanList;

    bool m_strongGreek_on;
    bool m_strongHebrew_on;

    void init();
    void createConnects();

    void setReadingPlanForCurrentDay();
};

#endif // LEFTPANEL2_H
