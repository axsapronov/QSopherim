#ifndef NOTEEDITOR_H
#define NOTEEDITOR_H

#include <QDialog>

namespace Ui {
class NoteEditor;
}

class NoteEditor : public QDialog
{
    Q_OBJECT

public:
    explicit NoteEditor(QWidget *parent = 0);
    ~NoteEditor();

    void setModuleName(QString moduleName);
    void setBookName(QString bookName);
    void setChapterValue(QString chapterValue);
    void setPath(QString name);
private slots:
    void saveNote();

private:
    Ui::NoteEditor *ui;
    void init();
    void createConnects();

    QString m_moduleName;
    QString m_bookName;
    QString m_chapterValue;
    QString m_path;

    void setTextToLabel();
    void addTextNotes(QString text);
};

#endif // NOTEEDITOR_H
