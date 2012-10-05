#ifndef LEFTPANEL_H
#define LEFTPANEL_H

#include <QDockWidget>

namespace Ui {
    class LeftPanel;
}

class LeftPanel : public QDockWidget
{
    Q_OBJECT

public:
    explicit LeftPanel(QWidget *parent = 0);
    ~LeftPanel();
    void refreshBookList();

private:
    Ui::LeftPanel *ui;
};

#endif // LEFTPANEL_H
