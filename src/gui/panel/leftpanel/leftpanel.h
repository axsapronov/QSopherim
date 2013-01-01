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

    void setListModuleFromList();

    /**
     * @brief retranslate
     * retranslate gui
     */
    void retranslate();
public slots:
    void showChapterFromJournal(QString module, QString book, QString chapter);

signals:
    void SIGNAL_AddRecordToJournal(QString, QString, QString);
    void SIGNAL_ShowHideLeftPanel2(bool);

private slots:

    /**
     * @brief refreshChapterList
     */
    void refreshChapterList(QModelIndex);
    /**
     * @brief refreshBookList
     */
    void refreshBookList(QString);
    /**
     * @brief showChapter
     */
    void showChapter(QModelIndex);
    /**
     * @brief showWord
     */
    void showWord(QModelIndex);

    /**
     * @brief refreshWordListFromDict
     */
    void refreshWordListFromDict(QString);

    /**
     * @brief showDescriptionWordFromOtherModules
     * @param word
     */
    void showDescriptionWordFromOtherModules(QString word);

    /**
     * @brief showDescriptionWord
     * @param word
     */
    void showDescriptionWord(QString word);

    void sShowHideLeftPanel2(int f_tab);

private:
    Ui::LeftPanel *ui;
    QStandardItemModel *modelModules;
    QStandardItemModel *modelBooks;
    QStandardItemModel *modelChapters;
    QStandardItemModel *modelClear;
    ProjectQModuleList *moduleList;

    QString m_lastNameOfBook;

    QStringListModel *typeModel;

    QString m_curWord;
    /**
     * @brief init
     * @function
     * initall function
     */
    void init();

    /**
     * @brief createConnects
     */
    void createConnects();

    QStringList getListDictWithWord(QString word);
};

#endif // LEFTPANEL_H
