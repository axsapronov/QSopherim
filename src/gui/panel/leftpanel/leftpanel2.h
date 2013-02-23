#ifndef LEFTPANEL2_H
#define LEFTPANEL2_H

#include <QDockWidget>
#include <QHash>
#include <QModelIndex>


#include <QStandardItem>
#include <QStandardItemModel>

#include "noteeditor.h"


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
    void SIGNAL_ShowChapterFromJournal(QString, QString, QString);

public slots:

    void showNoteList(QString curModule,
                      QString curBook,
                      QString curChapter,
                      QString curPath,
                      QString verse);

    void showStrong(QString number);

    void sSetStrongHebrew(QString path);
    void sSetStrongGreek(QString path);

    void sUpdateGUIDayMode();

private slots:

    // notes slots
    void editNote(QModelIndex ind);


    // journals slots
    void addRecordToJournal(QString modulename,
                            QString bookname,
                            QString chaptervalue);

    /**
     \brief
     If select item in journal, then open this item
     */
    void showChapterFromJournal(QModelIndex);

private:
    Ui::LeftPanel2 *ui;

    QHash<int, QString> m_data;

    QVector<StrongList> m_listStrongGreek;
    QVector<StrongList> m_listStrongHebrew;

    QMap<int, StrongList> m_mapStrongGreek;
    QMap<int, StrongList> m_mapStrongHebrew;

    QStandardItemModel *m_modelNotes;

    NoteEditor *GUI_NoteEditor;

    QString m_curModule;
    QString m_curBook;
    QString m_curChapter;
    QString m_curPath;
    QString m_verse;

    QStringList m_journalList;

    bool m_strongGreek_on;
    bool m_strongHebrew_on;

    void init();
    void createConnects();
};

#endif // LEFTPANEL2_H
