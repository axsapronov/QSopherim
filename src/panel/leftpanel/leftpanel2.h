#ifndef LEFTPANEL2_H
#define LEFTPANEL2_H

#include <QDockWidget>
#include <QHash>
#include <QModelIndex>

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

    void retranslate();
signals:
    void editNote();

public slots:
    void showNoteList(QString curModule,
                      QString curBook,
                      QString curChapter,
                      QString curPath,
                      QString firstVerse);
private slots:
    void editNote(QModelIndex ind);
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

};

#endif // LEFTPANEL2_H
