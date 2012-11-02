#ifndef RIGHTPANEL_H
#define RIGHTPANEL_H

#include <QDockWidget>
#include <QModelIndex>

namespace Ui {
    class RightPanel;
}

class RightPanel : public QDockWidget
{
    Q_OBJECT

public:
    explicit RightPanel(QWidget *parent = 0);
    ~RightPanel();
    /**
     * @brief retranslate
     * function for update translate
     */
    void retranslate();

    /**
     * @brief loadBookmarks
     * Load bookmarks from file
     */
    void loadBookmarks();

    /**
     * @brief saveBookmarks
     * Save bookmarks to file
     */
    void saveBookmarks();

signals:
    void SIGNAL_OpenBookmark(QString, QString, QString);

public slots:
    /**
     * @brief addNewBookmark
     * @function
     * Function for add bookmark
     * @param str
     */
    void addNewBookmark(QString str);

private slots:
    /**
     * @brief deleteBookmark
     * Delete bookmark from list
     */
    void deleteBookmark();
    /**
     * @brief openBookmark
     *
     */
    void openBookmark(QModelIndex);

private:
    Ui::RightPanel *ui;

    QStringList m_listBookmark;

    /**
     * @brief init
     * Inital right panel function
     */
    void init();
    /**
     * @brief createConnect
     * Create connects
     */
    void createConnect();

};

#endif // RIGHTPANEL_H
