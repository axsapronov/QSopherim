#ifndef RIGHTPANEL_H
#define RIGHTPANEL_H

#include <QDockWidget>

namespace Ui {
    class RightPanel;
}

class RightPanel : public QDockWidget
{
    Q_OBJECT

public:
    explicit RightPanel(QWidget *parent = 0);
    ~RightPanel();
    void retranslate();
    void loadBookmarks();

public slots:
    /**
     * @brief addNewBookmark
     * @function
     * Function for add bookmark
     * @param str
     */
    void addNewBookmark(QString str);

private:
    Ui::RightPanel *ui;

    QStringList m_listBookmark;
};

#endif // RIGHTPANEL_H
