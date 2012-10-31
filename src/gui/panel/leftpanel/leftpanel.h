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
    void refreshListModule(ProjectQModuleList* list);
    void refreshListDict(ProjectQModuleList* list);

    /**
     * @brief retranslate
     * retranslate gui
     */
    void retranslate();
public slots:
    void showChapterFromJournal(QString module, QString book, QString chapter);
signals:
    void SIGNAL_AddRecordToJournal(QString, QString, QString);

private slots:
    void refreshChapterList(QModelIndex);
    void refreshBookList(QString);
    void showChapter(QModelIndex);

    void refreshWordListFromDict(QString);
private:
    Ui::LeftPanel *ui;
    QStandardItemModel *modelModules;
    QStandardItemModel *modelBooks;
    QStandardItemModel *modelChapters;
    QStandardItemModel *modelClear;
    ProjectQModuleList *moduleList;

    QString m_lastNameOfBook;

    QStringListModel *typeModel;
    /**
     * @brief init
     * @function
     * initall function
     */
    void init();
    void createConnects();


};

#endif // LEFTPANEL_H
