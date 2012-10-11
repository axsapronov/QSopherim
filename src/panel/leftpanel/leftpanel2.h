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

public slots:
    void showNoteList(QString curModule,
                      QString curBook,
                      QString curChapter,
                      QString curPath,
                      QString firstVerse);

private:
    Ui::LeftPanel2 *ui;
    void init();
};

#endif // LEFTPANEL2_H
