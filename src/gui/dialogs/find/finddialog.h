#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QProgressDialog>
#include <QFile>
#include <QDir>


namespace Ui {
class FindDialog;
}

typedef struct FindData
{
    QStringList files;
    QStringList verse;
} FindData;

typedef struct SearchData
{
    QStringList modules;
    QStringList books;
    QStringList chapter;
    QStringList files;
    QStringList type;
    QStringList verse;
} SearchData;

class FindDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FindDialog(QWidget *parent = 0);
    ~FindDialog();

private slots:
    /**
     * @brief find
     */
    void find();

    /**
     * @brief updateInfo
     */
    void updateInfo();


private:
    Ui::FindDialog *ui;

    /**
     * @brief init
     */
    void init();

    /**
     * @brief createConnects
     */
    void createConnects();

    /**
     * @brief updateCBBook
     */
    void updateComBBook();

    /**
     * @brief updateCBChapter
     * @param path
     */
    void updateComBChapter(QString path);

    /**
     * @brief removeItemListChapter
     * @param list
     */
    void removeItemListChapter(QStringList &list);

    /**
     * @brief removeItemListBook
     * @param list
     */
    void removeItemListBook(QStringList &list);

    /**
     * @brief findFiles
     * @param files
     * @param text
     * @return
     */
    FindData findFiles(const QStringList &files, const QString &text);

    /**
     * @brief showFiles
     * @param files
     */
    void showFiles(const SearchData &files);

    /**
     * @brief updateItemforTable
     * @param data
     */
    void updateItemforTable(SearchData &data);

    /**
     * @brief accept
     */
    void accept();

    /**
     * @brief reject
     */
    void reject();

    QString getPathFind();

    QDir m_currentDir;

};

#endif // FINDDIALOG_H
