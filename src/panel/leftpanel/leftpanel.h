#ifndef LEFTPANEL_H
#define LEFTPANEL_H

#include <QDockWidget>
#include <QModelIndex>

class QStandardItemModel;
class QModelIndex;

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

private slots:
    void refreshChapterList(QModelIndex);
private:
    Ui::LeftPanel *ui;
    QStandardItemModel *modelModules;
    QStandardItemModel *modelChapters;
    ProjectQModuleList *moduleList;
    void init();
    void createConnects();
};

#endif // LEFTPANEL_H
