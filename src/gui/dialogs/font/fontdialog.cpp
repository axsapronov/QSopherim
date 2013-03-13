#include "fontdialog.h"
#include "ui_fontdialog.h"

#include "defines.h"
#include "debughelper.h"
#include "config.h"

#include <QMessageBox>

FontDialog::FontDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FontDialog)
{
    ui->setupUi(this);
    setWindowTitle(QString(tr("Font dialog") + " | %1 - %2").arg(GL_PROG_NAME).arg(GL_PROG_VERSION_STR));
}
//------------------------------------------------------------------------------
FontDialog::~FontDialog()
{
    delete ui;
}
//------------------------------------------------------------------------------
void FontDialog::createConnects()
{

}
//------------------------------------------------------------------------------
void FontDialog::accept()
{
    //todo
//    myDebug() << "accept";
    if (isModilySettings())
    {
        int ret = QMessageBox::warning(this, GL_PROG_NAME,
                                       tr("Settings has been modified.\n"
                                          "Do you want to save your changes?"),
                                       QMessageBox::Save
                                       | QMessageBox::Discard
                                       | QMessageBox::Cancel,
                                       QMessageBox::Save);
        //        QMessageBox msgBox;
        switch (ret)
        {
        case QMessageBox::Save:
            // Save was clicked
            saveOption();
            emit SIGNAL_SendInfo();

            QWidget::hide();
            break;
        case QMessageBox::Discard:
            setOptionFromFont(Config::configuration()->getGUIMapFont()[m_name]);
            QWidget::hide();
            break;
        case QMessageBox::Cancel:
            // Cancel was clicked
            break;
        default:
            // should never be reached
            break;
        }
    }
    else
    {
        QWidget::hide();
    }
}
//------------------------------------------------------------------------------
void FontDialog::reject()
{
//    myDebug() << "reject";
    QWidget::hide();
}
//------------------------------------------------------------------------------
void FontDialog::setNameOption(const QString f_name)
{
    m_name = f_name;
    setOptionFromFont(Config::configuration()->getGUIMapFont()[f_name]);
}
//------------------------------------------------------------------------------
bool FontDialog::isModilySettings()
{
    bool r_var = false;

    if (ui->chBItalic->checkState() != m_font.italic()
            || ui->fontComB->currentText() != m_font.family()
            || ui->sBSize->value() != m_font.pointSize()
            || ui->sBWeight->value() != m_font.weight())
    {
        r_var = true;
    }

    return r_var;
}
//------------------------------------------------------------------------------
void FontDialog::setOptionFromFont(const QFont f_font)
{
    m_font = f_font;
    ui->LAName->setText(m_name);
    ui->chBItalic->setChecked(f_font.italic());
    ui->sBSize->setValue(f_font.pointSize());
    ui->sBWeight->setValue(f_font.weight());
    ui->fontComB->setCurrentIndex(ui->fontComB->findText(f_font.family()));
}
//------------------------------------------------------------------------------
void FontDialog::saveOption()
{
    QFont t_font;
    t_font.setFamily(ui->fontComB->currentText());
    t_font.setPointSize(ui->sBSize->value());
    t_font.setWeight(ui->sBWeight->value());
    t_font.setItalic(ui->chBItalic->checkState());
    Config::configuration()->setGUIMapFontName(m_name, t_font);
}
//------------------------------------------------------------------------------
