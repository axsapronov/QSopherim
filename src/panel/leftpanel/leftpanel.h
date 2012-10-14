#ifndef LEFTPANEL_H
#define LEFTPANEL_H

#include <QDockWidget>
#include <QModelIndex>
#include <QTranslator>

class QStandardItemModel;
class QModelIndex;
class QStringListModel;

namespace Ui {
class LeftPanel;
}
class ProjectQModuleList;
class LeftPanel : public QDockWidget
{
    Q_OBJECT

public:
    explicit LeftPanel(QWidget *parent = 0);
    ~LeftPanel();
    void refreshBookList(ProjectQModuleList* list);
    void refreshList(ProjectQModuleList* list);

    void retranslate();

private slots:
    void refreshChapterList(QModelIndex);
    void refreshBookList(QString);
    void showChapter(QModelIndex);
private:
    Ui::LeftPanel *ui;
    QStandardItemModel *modelModules;
    QStandardItemModel *modelBooks;
    QStandardItemModel *modelChapters;
    QStandardItemModel *modelClear;
    ProjectQModuleList *moduleList;

    QString lastNameOfBook;

    QStringListModel *typeModel;
    void init();
    void createConnects();
};

#endif // LEFTPANEL_H
