#ifndef LEFTPANEL2_H
#define LEFTPANEL2_H

#include <QDockWidget>
#include <QHash>
#include <QModelIndex>


#include <QStandardItem>
#include <QStandardItemModel>

#include "noteeditor.h"

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

signals:
    void SIGNAL_ShowChapterFromJournal(QString, QString, QString);

public slots:
    void showNoteList(QString curModule,
                      QString curBook,
                      QString curChapter,
                      QString curPath,
                      QString firstVerse);


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

    NoteEditor *GUI_NoteEditor;

    void init();
    void createConnects();

    QString m_curModule;
    QString m_curBook;
    QString m_curChapter;
    QString m_curPath;
    QString m_firstVerse;

    QStringList m_journalList;
};

#endif // LEFTPANEL2_H
