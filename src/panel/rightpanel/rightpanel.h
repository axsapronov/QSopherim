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

private:
    Ui::RightPanel *ui;
};

#endif // RIGHTPANEL_H
