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

    void setModuleName(const QString moduleName);
    void setBookName(const QString bookName);
    void setChapterValue(const QString chapterValue);
    void setPath(const QString name);
    void setVerse(const QString first);
    void editNote(const QString text);

    void retranslate();

    void deleteNote(QString f_module, QString f_book, QString f_chapter, QString f_path, QString f_text);

public slots:
    void sUpdateGUIDayMode();

private slots:
    void saveNote();
    void rejectNote();

signals:
    void SIGNAL_HideNotes();

private:
    Ui::NoteEditor *ui;
    void init();
    void createConnects();

    void replaceNote(const QString f_newText, const QString f_oldText);
    bool m_edit;
    QString m_oldText;

    QString m_moduleName;
    QString m_bookName;
    QString m_chapterValue;
    QString m_path;
    QString m_verse;

    void setTextToLabel();
    void addTextNotes(const QString text);
};

#endif // NOTEEDITOR_H
