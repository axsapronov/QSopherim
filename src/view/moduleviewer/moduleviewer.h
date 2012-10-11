#ifndef MODULEVIEWER_H
#define MODULEVIEWER_H

#include <QWidget>

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

private slots:
    void showContextMenu(QPoint pt);
    void setCurLine();
protected:
//    void contextMenuEvent(QContextMenuEvent *event);


private:
    Ui::ModuleViewer *ui;

    QAction *cutAct;
    QAction *copyAct;
    QAction *pasteAct;
    void init();
    void createConnects();
    void loadViewSettings();

    QString curModule;
    QString curBook;
    QString curChapter;
    QString curPath;
    int lastSelectLineFirst;
    int lastSelectLineLast;

//    void getTextChapter(QString pathToFile, QString nameBook, int numberchapter);

    void createActions();
};

#endif // MODULEVIEWER_H
