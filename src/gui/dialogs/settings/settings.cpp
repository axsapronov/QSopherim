#include "settings.h"
#include "ui_settings.h"
#include "defines.h"
#include "config.h"
#include "debughelper.h"
#include "defines.h"

#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QColorDialog>

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);

    setWindowTitle(QString(tr("Settings") + " | %1 - %2").arg(GL_PROG_NAME).arg(GL_PROG_VERSION_STR));

    ui->tabWidget->removeTab(3);
    init();
    createConnect();
}
//------------------------------------------------------------------------------
Settings::~Settings()
{
    delete GUI_Font;
    delete ui;
}
//------------------------------------------------------------------------------
void Settings::debug()
{

    myDebug() << "debug: appwsettings";
}
//------------------------------------------------------------------------------
void Settings::init()
{
    // add item to combobox
    ui->comBLanguage->addItem("Russian");
    ui->comBLanguage->addItem("English");
    ui->comBLanguage->addItem("Français");
    ui->comBLanguage->addItem("Deutsch");

    // load module settings
    //    ui->LEBibleFolder->setText(Config::configuration()->getBibleDir());
    //    ui->LEDictFolder->setText(Config::configuration()->getDictDir());
    //    ui->LEOtherFolder->setText(Config::configuration()->getOtherDir());
    //    // font
    //    ui->sBFontSize->setValue(Config::configuration()->getFontSize());
    //    ui->fontComB->setCurrentFont(QFont(Config::configuration()->getFontFamily()));
    //    m_fontColor = Config::configuration()->getFontColor();
    //    m_viewerColor = Config::configuration()->getViewerColor();

    loadSettings();


    GUI_Font = new FontDialog(this);
    //    ui->sBFontSize->setValue(Config);

    /// create QSettings
    //    settings = new QSettings("settings.conf",QSettings::NativeFormat);
    //    QString value = "Russian";
    //    settings->setValue("language/lang", value);
    //    settings->sync();
}
//------------------------------------------------------------------------------
void Settings::loadSettings()
{
    //    QString lang = settings->value("language/lang").toString();
    QString lang = Config::configuration()->getAppLang();

    setAPPLang(lang);
    ui->comBLanguage->setCurrentIndex(ui->comBLanguage->findText(lang));

    // load font and viewer settings
    ui->chBBold->setChecked(Config::configuration()->getFontBold());
    ui->chBItalic->setChecked(Config::configuration()->getFontItalic());
    ui->chBStrike->setChecked(Config::configuration()->getFontStrike());
    ui->chBUnderline->setChecked(Config::configuration()->getFontUnderline());

    ui->chBChangindTextColor->setChecked(Config::configuration()->getOptionChangeTextColor());
    ui->chBOptionAutoChapter->setChecked(Config::configuration()->getOptionAutoChapter());

    ui->sBFontSize->setValue(Config::configuration()->getFontSize());
    ui->fontComB->setCurrentFont(QFont(Config::configuration()->getFontFamily()));
    m_fontColor = Config::configuration()->getFontColor();
    m_viewerColor = Config::configuration()->getViewerColor();

    // gui
    ui->chBGuiTray->setChecked(Config::configuration()->getGuiTray());
    ui->chBDayMode->setChecked(Config::configuration()->getDayMode());

    ui->sBAppLogLevel->setValue(Config::configuration()->AppLogLevel());

    updateFontSettings();

    // replace to AppDir/*  if empty
    //    QDir::currentPath();

    //    myDebug() << settings->value("language/lang");
    //    if (lang.isEmpty())
    //        lang = "Russian";
    //    setAPPLang(lang);
    //    ui->comBLanguage->setCurrentIndex(ui->comBLanguage->findText(lang));
}
//------------------------------------------------------------------------------
void Settings::saveSettings()
{
    if (ui->comBLanguage->currentText() != Config::configuration()->getAppLang())
    {
        emit SIGNAL_RetranslateGUI(ui->comBLanguage->currentText());
    }
    Config::configuration()->setAppLang(ui->comBLanguage->currentText());

    Config::configuration()->setOptionChangeTextColor(ui->chBChangindTextColor->checkState());

    // save font settings and viewer settings
    Config::configuration()->setFontFamily(ui->fontComB->currentText());
    Config::configuration()->setFontSize(ui->sBFontSize->value());
    Config::configuration()->setFontColor(m_fontColor);
    Config::configuration()->setViewerColor(m_viewerColor);

    Config::configuration()->setFontBold(ui->chBBold->checkState());
    Config::configuration()->setFontItalic(ui->chBItalic->checkState());
    Config::configuration()->setFontStrike(ui->chBStrike->checkState());
    Config::configuration()->setFontUnderline(ui->chBUnderline->checkState());

<<<<<<< HEAD
=======
    Config::configuration()->setOptionChangeTextColor(ui->chBChangindTextColor->checkState());
    Config::configuration()->setOptionAutoChapter(ui->chBOptionAutoChapter->checkState());

    Config::configuration()->setGuiTray(ui->chBGuiTray->checkState());
    Config::configuration()->setDayMode(ui->chBDayMode->checkState());

    Config::configuration()->setAppLogLevel(ui->sBAppLogLevel->value());

>>>>>>> next
    //    ui->sBFontSize->setValue(Config::configuration()->getFontSize());

    //    ui->fontComB->setCurrentFont(QFont(Config::configuration()->getFontFamily()));
}
//------------------------------------------------------------------------------
void Settings::createConnect()
{
    connect(ui->pBColor, SIGNAL(clicked()), SLOT(selectFontColor()));
    connect(ui->pBBackgroundColor, SIGNAL(clicked()), SLOT(selectFontColor()));

    // font settings
    connect(ui->pBFontMenu, SIGNAL(clicked()), SLOT(fontSettings()));
    connect(ui->pBFontModulesName, SIGNAL(clicked()), SLOT(fontSettings()));
    connect(ui->pBFontBookName, SIGNAL(clicked()), SLOT(fontSettings()));
    connect(ui->pBFontStrongsHebrew, SIGNAL(clicked()), SLOT(fontSettings()));
    connect(ui->pBFontStrongsGreek, SIGNAL(clicked()), SLOT(fontSettings()));
    connect(ui->pBFontJornal, SIGNAL(clicked()), SLOT(fontSettings()));
    connect(ui->pBFontNotes, SIGNAL(clicked()), SLOT(fontSettings()));
    connect(ui->pBFontReadingPlan, SIGNAL(clicked()), SLOT(fontSettings()));

    connect(GUI_Font, SIGNAL(SIGNAL_SendInfo()), SLOT(updateFontSettings()));
}
//------------------------------------------------------------------------------
void Settings::accept()
{
    if (getModifySettings())
    {
        int ret = QMessageBox::warning(this, tr(GL_PROG_NAME),
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
            saveSettings();

            //            msgBox.setText("Settings has been modified. Please restart the"
            //                           "application for the entry into force of the settings");
            //            msgBox.exec();
            emit SIGNAL_ReLoadFontSettings();
            emit SIGNAL_UpdateTray();
            emit SIGNAL_UpdateDayMode();

            QWidget::hide();
            break;
        case QMessageBox::Discard:
            setParams();
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
QString Settings::getAPPLang()
{
    return m_APP_Lang;
}
//------------------------------------------------------------------------------
void Settings::setAPPLang(QString new_lang)
{
    m_APP_Lang = new_lang;
    return;
}
//------------------------------------------------------------------------------
bool Settings::getModifySettings()
{
    if (ui->comBLanguage->currentText() != Config::configuration()->getAppLang()
            || ui->sBFontSize->value() != Config::configuration()->getFontSize()
            || ui->fontComB->currentText() != Config::configuration()->getFontFamily()
            || m_fontColor != Config::configuration()->getFontColor()
            || ui->chBBold->checkState() != Config::configuration()->getFontBold()
            || ui->chBChangindTextColor->checkState() != Config::configuration()->getOptionChangeTextColor()
            || ui->chBItalic->checkState() != Config::configuration()->getFontItalic()
            || ui->chBStrike->checkState() != Config::configuration()->getFontStrike()
            || ui->chBUnderline->checkState() != Config::configuration()->getFontUnderline()
            || ui->chBGuiTray->checkState() != Config::configuration()->getGuiTray()
            || ui->chBDayMode->checkState() != Config::configuration()->getDayMode()
            || ui->chBOptionAutoChapter->checkState() != Config::configuration()->getOptionAutoChapter()
            )
    {
        return true;
    }

    return false;
}
//------------------------------------------------------------------------------
void Settings::setParams()
{
    ui->comBLanguage->setCurrentIndex(ui->comBLanguage->findText(getAPPLang()));
}
//------------------------------------------------------------------------------
void Settings::selectFontColor()
{
    QPushButton *button = (QPushButton *)sender();
    QColor t_color;
    t_color = QColorDialog::getColor(Config::configuration()->getFontColor(), this);
    if (!t_color.isValid())
    {
        return;
    }

    if (button == ui->pBBackgroundColor)
    {
        // set like background (viewer) color
        m_viewerColor = t_color;
    }
    else
    {
        // set like font color
        m_fontColor = t_color;
    }
}
//------------------------------------------------------------------------------
void Settings::retranslate()
{
    ui->retranslateUi(this);
}
//------------------------------------------------------------------------------
void Settings::fontSettings()
{
    QPushButton *button = (QPushButton *)sender();
    if (button == ui->pBFontMenu)
        GUI_Font->setNameOption("FontMenu");

    if (button == ui->pBFontModulesName)
        GUI_Font->setNameOption("FontModulesName");

    if (button == ui->pBFontBookName)
        GUI_Font->setNameOption("FontBookName");

    if (button == ui->pBFontStrongsHebrew)
        GUI_Font->setNameOption("FontStrongsHebrew");

    if (button == ui->pBFontStrongsGreek)
        GUI_Font->setNameOption("FontStrongsGreek");

    if (button == ui->pBFontJornal)
        GUI_Font->setNameOption("FontJournal");

    if (button == ui->pBFontNotes)
        GUI_Font->setNameOption("FontNotes");

    if (button == ui->pBFontReadingPlan)
        GUI_Font->setNameOption("FontReadingPlan");

    GUI_Font->show();
}
//------------------------------------------------------------------------------
void Settings::updateFontSettings()
{
    // fonts
    ui->fontComBMenu->setCurrentIndex(ui->fontComBMenu->findText(Config::configuration()->getGUIMapFont()["FontMenu"].family()));
    ui->fontComBModulesName->setCurrentIndex(ui->fontComBModulesName->findText(Config::configuration()->getGUIMapFont()["FontModulesName"].family()));
    ui->fontComBBookName->setCurrentIndex(ui->fontComBBookName->findText(Config::configuration()->getGUIMapFont()["FontBookName"].family()));
    ui->fontComBStrongsHebrew->setCurrentIndex(ui->fontComBStrongsHebrew->findText(Config::configuration()->getGUIMapFont()["FontStrongsHebrew"].family()));
    ui->fontComBStrongsGreek->setCurrentIndex(ui->fontComBStrongsGreek->findText(Config::configuration()->getGUIMapFont()["FontStrongsGreek"].family()));
    ui->fontComBJornal->setCurrentIndex(ui->fontComBJornal->findText(Config::configuration()->getGUIMapFont()["FontJournal"].family()));
    ui->fontComBNotes->setCurrentIndex(ui->fontComBNotes->findText(Config::configuration()->getGUIMapFont()["FontNotes"].family()));
    ui->fontComBReadingPlan->setCurrentIndex(ui->fontComBReadingPlan->findText(Config::configuration()->getGUIMapFont()["FontReadingPlan"].family()));

    ui->sBFontMenuSize->setValue(Config::configuration()->getGUIMapFont()["FontMenu"].pointSize());
    ui->sBFontModulesNameSize->setValue(Config::configuration()->getGUIMapFont()["FontModulesName"].pointSize());
    ui->sBFontBookNameSize->setValue(Config::configuration()->getGUIMapFont()["FontBookName"].pointSize());
    ui->sBFontStrongsHebrewSize->setValue(Config::configuration()->getGUIMapFont()["FontStrongsHebrew"].pointSize());
    ui->sBFontStrongsGreekSize->setValue(Config::configuration()->getGUIMapFont()["FontStrongsGreek"].pointSize());
    ui->sBFontJournalSize->setValue(Config::configuration()->getGUIMapFont()["FontJournal"].pointSize());
    ui->sBFontNotesSize->setValue(Config::configuration()->getGUIMapFont()["FontNotes"].pointSize());
    ui->sBFontReadingPlanSize->setValue(Config::configuration()->getGUIMapFont()["FontReadingPlan"].pointSize());
}
//-------------------------------------------------------------------------------
