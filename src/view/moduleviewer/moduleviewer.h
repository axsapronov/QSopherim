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

    void showChapter(QString pathToFile, QString nameBook, int numberchapter);

private slots:
    void showContextMenu(QPoint pt);
protected:
    void contextMenuEvent(QContextMenuEvent *event);


private:
    Ui::ModuleViewer *ui;

    QAction *cutAct;
    QAction *copyAct;
    QAction *pasteAct;
    void init();
    void createConnects();
    void loadViewSettings();

//    void getTextChapter(QString pathToFile, QString nameBook, int numberchapter);

    void createActions();
};

#endif // MODULEVIEWER_H
