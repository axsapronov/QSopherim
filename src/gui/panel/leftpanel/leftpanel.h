#ifndef LEFTPANEL_H
#define LEFTPANEL_H

#include <QDockWidget>
#include <QModelIndex>
#include <QTranslator>

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
    /**
     * @brief retranslate
     * retranslate gui
     */
    void retranslate();

    void loadFirstBook();

    void setFirstLaunch(bool state);

public slots:
    /**
     * @brief showChapterFromJournal
     * @param module
     * @param book
     * @param chapter
     */
    void showChapterFromJournal(const QString f_module, const QString f_book, const QString f_chapter);
    /**
     * @brief sUpdateGUI
     */
    void sUpdateGUI();

    void sUpdateGUIDayMode();
    void sUpdateGUIFont();

    void loadModules();
    void loadDictionaries();
    void loadComments();
    void loadApocrypha();
    void loadBooks();

    void sRefreshModules();

signals:
    void SIGNAL_AddRecordToJournal(QString, QString, QString);
    void SIGNAL_ShowHideLeftPanel2(bool);
    void SIGNAL_ShowNotes(QString, QString, QString, QString);

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
    void refreshBookList(const QString nameOfModule, const QString f_type);
    /**
     * @brief showChapter
     */
    void showChapter(const QModelIndex);
    /**
     * @brief showWord
     */
    void showWord(const QModelIndex);

    /**
     * @brief refreshWordListFromDict
     */
    void refreshWordListFromDict(const QString);

    /**
     * @brief showDescriptionWordFromOtherModules
     * @param word
     */
    void showDescriptionWordFromOtherModules(const QString word);

    /**
     * @brief showDescriptionWord
     * @param word
     */
    void showDescriptionWord(const QString word);

    void sShowHideLeftPanel2(const int f_tab);

    void sSetCommentsFromModule(const QString);

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
    bool m_firstLaunch;

    QMap<QString, QString> m_listDictWord;

    QString m_curWord;
    bool m_fromJournal;
    /**
     * @brief init
     * @function
     * initall function
     */
    void init();


    /**
     * check current module, current book, current chapter and
     * Config::configuration()->getLastModule and other
     * @brief checkedNewAndOldChapter
     * @return
     */
    bool checkedNewAndOldChapter();

    void sUpdateGUIFromJournal();
    bool m_journal;

    /**
     * @brief createConnects
     */
    void createConnects();

    void refreshComboBooks();

    void showHideTabs();

    void refreshChapterList(const QString f_type, const QModelIndex f_ind);

    QStringList getListDictWithWord(const QString word);

    void makeOptionAutoChapter(const QString f_bookName);

    void showChapter(const QModelIndex ind, const QString f_type);

    void refreshListModule(QSopherimModuleList* list, const QString f_type);
    void refreshListDict(QSopherimModuleList* list);
    void refreshListComments(QSopherimModuleList* list);

};

#endif // LEFTPANEL_H
