#ifndef BOTTOMPANEL_H
#define BOTTOMPANEL_H

#include <QDockWidget>

namespace Ui {
    class BottomPanel;
}

class BottomPanel : public QDockWidget
{
    Q_OBJECT

public:
    explicit BottomPanel(QWidget *parent = 0);
    ~BottomPanel();

private:
    Ui::BottomPanel *ui;
};

#endif // BOTTOMPANEL_H
