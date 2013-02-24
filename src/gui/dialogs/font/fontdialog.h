#ifndef FONTDIALOG_H
#define FONTDIALOG_H

#include <QDialog>

namespace Ui {
class FontDialog;
}

class FontDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FontDialog(QWidget *parent = 0);
    ~FontDialog();

    void setNameOption(const QString name);

signals:
    void SIGNAL_SendInfo();

private:
    Ui::FontDialog *ui;

    QString m_name;
    QFont m_font;

    void createConnects();

    void accept();
    void reject();

    void setOptionFromFont(const QFont f_font);
    void saveOption();

    bool isModilySettings();


};

#endif // FONTDIALOG_H
