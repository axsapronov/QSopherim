#ifndef MODULEVIEWER_H
#define MODULEVIEWER_H

#include <QWidget>
#include <QHash>
class StrongList;

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

    QString getLastSelectLineFirst();
    void setLastSelectLineFirst(int firstlast);

    QString getLastSelectLineLast();
    void setLastSelectLineLast(int lastlast);

    void setStrongList(QString path);
    void retranslate();

public slots:

    /**
     * @brief updateFontSettings
     * @function
     * Update font settings
     */
    void updateFontSettings();

signals:
    void SIGNAL_ShowNoteList(QString, QString, QString, QString, QString);
    void SIGNAL_AddNewBookmark(QString);

private slots:
    void showContextMenu(QPoint pt);
    void setCurLine();
    void addBookmark();
protected:
    //    void contextMenuEvent(QContextMenuEvent *event);
    bool eventFilter(QObject *obj, QEvent *ev);
//    void mouseMoveEvent (QMouseEvent* event);

private:
    Ui::ModuleViewer *ui;

    QVector<StrongList> m_list;
    QHash< QString, QVector<int> > m_strongs;

    QAction *act_cut;
    QAction *act_copy;
    QAction *act_paste;
    QAction *act_addBookmarks;

    void init();
    void createConnects();
    void createActions();
    void loadViewSettings();

    QString curModule;
    QString curBook;
    QString curChapter;
    QString curPath;
    int lastSelectLineFirst;
    int lastSelectLineLast;

    void showNoteList();
    void showStrong();
    void debug();

    QString fillStrongList(QString str);

//    QHash<int, QHash<QString, QString> > getListStrongWord(QString word);
    //    void getTextChapter(QString pathToFile, QString nameBook, int numberchapter);

};

#endif // MODULEVIEWER_H
