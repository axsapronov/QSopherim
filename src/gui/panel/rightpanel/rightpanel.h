#ifndef RIGHTPANEL_H
#define RIGHTPANEL_H

#include <QDockWidget>
#include <QModelIndex>
#include <QStandardItemModel>
#include <QStringListModel>

#include "noteeditor.h"

namespace Ui {
    class RightPanel;
}

class RightPanel : public QDockWidget
{
    Q_OBJECT

public:
    explicit RightPanel(QWidget *parent = 0);
    ~RightPanel();
    /**
     * @brief retranslate
     * function for update translate
     */
    void retranslate();

    /**
     * @brief loadBookmarks
     * Load bookmarks from file
     */
    void loadBookmarks();

    /**
     * @brief saveBookmarks
     * Save bookmarks to file
     */
    void saveBookmarks();

    void loadFirstSettings();

signals:
    void SIGNAL_OpenBookmark(QString, QString, QString);

public slots:
    /**
     * @brief addNewBookmark
     * @function
     * Function for add bookmark
     * @param str
     */
    void addNewBookmark(QString str);

    void sShowNoteList(QString f_module,
                      QString f_book,
                      QString f_chapter,
                      QString f_path);

    void sUpdateGUIDayMode();

private slots:
    /**
     * @brief deleteBookmark
     * Delete bookmark from list
     */
    void deleteBookmark();
    /**
     * @brief openBookmark
     *
     */
    void openBookmark(QModelIndex);

    void sUpdateListNotes();

    // notes slots
    void sEditNote(QModelIndex ind);

    void sEditNote();
    void sNewNote();
    void sDeleteNote();
    void sLoadNotes();

private:
    Ui::RightPanel *ui;

    QStringList m_listBookmark;
    QStandardItemModel *m_modelNotes;
    QMap<int, QString> m_mapNotes;

    QMap<QString, QString> m_notes;

    NoteEditor *GUI_NoteEditor;

    QString m_curModule;
    QString m_curBook;
    QString m_curChapter;
    QString m_curPath;
    QString m_verse;

    /**
     * @brief init
     * Inital right panel function
     */
    void init();
    /**
     * @brief createConnect
     * Create connects
     */
    void createConnect();

    void fillModulesList();

};

#endif // RIGHTPANEL_H
