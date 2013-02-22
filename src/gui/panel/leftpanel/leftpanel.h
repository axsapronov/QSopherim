#ifndef LEFTPANEL_H
#define LEFTPANEL_H

#include <QDockWidget>
#include <QModelIndex>
#include <QTranslator>

#include "leftpaneloperator.h"

class QStandardItemModel;
class QModelIndex;
class QStringListModel;

namespace Ui
{
    class LeftPanel;
}

class QSopherimModuleList;


class LeftPanel : public QDockWidget
{
    Q_OBJECT

public:
    explicit LeftPanel(QWidget *parent = 0);
    ~LeftPanel();

    void refreshBookList(QSopherimModuleList* list);
    void refreshListModule(QSopherimModuleList* list);
    void refreshListDict(QSopherimModuleList* list);

    void setListModuleFromList();

    /**
     * @brief retranslate
     * retranslate gui
     */
    void retranslate();


public slots:
    /**
     * @brief showChapterFromJournal
     * @param module
     * @param book
     * @param chapter
     */
    void showChapterFromJournal(QString module, QString book, QString chapter);
    /**
     * @brief sUpdateGUI
     */
    void sUpdateGUI();

signals:
    void SIGNAL_AddRecordToJournal(QString, QString, QString);
    void SIGNAL_ShowHideLeftPanel2(bool);

private slots:

    /**
     * @brief refreshChapterList
     */
    void refreshChapterList(const QModelIndex f_ind);

    /**
     * @brief refreshBookList
     * @param nameOfModule
     */
    void refreshBookList(QString nameOfModule);
    /**
     * @brief refreshBookList
     */
    void refreshBookList(QString nameOfModule, QString f_type);
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
    QSopherimModuleList *moduleList;

    QString m_lastNameOfBook;

    QStringListModel *typeModel;
    QStringListModel *typeModelBook;

    LeftPanelOperator *m_operator;

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

    void refreshComboBooks();

    void refreshChapterList(const QString f_type, const QModelIndex f_ind);

    QStringList getListDictWithWord(QString word);
};

#endif // LEFTPANEL_H
