#ifndef LEFTPANEL2_H
#define LEFTPANEL2_H

#include <QDockWidget>

namespace Ui {
    class LeftPanel2;
}

class LeftPanel2 : public QDockWidget
{
    Q_OBJECT

public:
    explicit LeftPanel2(QWidget *parent = 0);
    ~LeftPanel2();

private:
    Ui::LeftPanel2 *ui;
};

#endif // LEFTPANEL2_H
