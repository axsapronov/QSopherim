#ifndef MODULEVIEWER_H
#define MODULEVIEWER_H

#include <QWidget>
#include <QTimer>
#include <QHash>


namespace Ui {
class ModuleViewer;
}



QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
QT_END_NAMESPACE

class ModuleViewer : public QWidget
{
    Q_OBJECT

public:
    explicit ModuleViewer(QWidget *parent = 0);
    ~ModuleViewer();

    static ModuleViewer *viewer();

    void setModuleName(QString newModule);
    QString getModuleName();

    void setBookName(QString newmodule);
    QString getBookName();

    void setChapterValue(QString newchapter);
    QString getChapterValue();

    void setPath(QString newPath);
    QString getPath();

    void showChapter(QString pathToFile, QString nameBook, int numberchapter);

    void setStrongList(QString path);
    void retranslate();

    QString getLastNumberLine();

public slots:

    /**
     * @brief updateFontSettings
     * @function
     * Update font settings
     */
    void updateFontSettings();

    /**
     * @brief find
     */
    void find();
    /**
     * @brief findNext
     */
    void findNext();
    /**
     * @brief findPrevious
     */
    void findPrevious();

signals:
    void SIGNAL_ShowNoteList(QString, QString, QString, QString, QString);
    void SIGNAL_AddNewBookmark(QString);

//    void SIGNAL_AddNote(QString, QString, QString, QString, QString);
    void SIGNAL_AddNote();

    void SIGNAL_ShowStrong(QString);

private slots:
    /**
     * @brief showContextMenu
     * @param pt
     */
    void sShowContextMenu(QPoint pt);

    /**
     * @brief addBookmark
     */
    void sAddBookmark();

    /**
     * @brief find
     * @param forward
     * @param backward
     */
    void sFind(QString, bool forward = false, bool backward = false);

    void sAddNote();
protected:
    //    void contextMenuEvent(QContextMenuEvent *event);
//    bool eventFilter(QObject *obj, QEvent *ev);
    bool event(QEvent *e);
//    void mouseMoveEvent (QMouseEvent* event);

private:
    Ui::ModuleViewer *ui;

//    QVector<StrongList> m_list;
    QHash< QString, QVector<int> > m_strongs;

    QAction *act_cut;
    QAction *act_copy;
    QAction *act_paste;
    QAction *act_addBookmarks;
    QAction *act_addNote;

    void init();
    void createActions();
    void loadViewSettings();

    QString m_curModule;
    QString m_curBook;
    QString m_curChapter;
    QString m_curPath;

    int m_lastLine;

    bool m_strong;

    QString m_backupChapter;

    void showNoteList();
    void showStrong();
    void debug();

    QString fillStrongList(QString str);

    QTimer *autoHideTimer;


};

#endif // MODULEVIEWER_H
