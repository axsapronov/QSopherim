#include "settings.h"
#include "ui_settings.h"
#include "defines.h"
#include "config.h"
#include "debughelper.h"

#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QColorDialog>

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    init();
    createConnect();
}
///----------------------------------------------------------------------------
Settings::~Settings()
{
    delete ui;
}
///----------------------------------------------------------------------------
void Settings::debug()
{

    myDebug() << "debug: appwsettings";
}
///----------------------------------------------------------------------------
void Settings::init()
{
    /// add item to combobox
    ui->comBLanguage->addItem("Russian");
    ui->comBLanguage->addItem("English");
    ui->comBLanguage->addItem("Français");
    ui->comBLanguage->addItem("Deutsch");

    /// load module settings
    ui->LEBibleFolder->setText(Config::configuration()->getBibleDir());
    ui->LEDictFolder->setText(Config::configuration()->getDictDir());
    ui->LEOtherFolder->setText(Config::configuration()->getOtherDir());
    // font
    ui->sBFontSize->setValue(Config::configuration()->getFontSize());
    ui->fontComB->setCurrentFont(QFont(Config::configuration()->getFontFamily()));
    m_fontColor = Config::configuration()->getFontColor();
    m_viewerColor = Config::configuration()->getViewerColor();

    //    ui->sBFontSize->setValue(Config);

    /// create QSettings
    //    settings = new QSettings("settings.conf",QSettings::NativeFormat);
    //    QString value = "Russian";
    //    settings->setValue("language/lang", value);
    //    settings->sync();
}
///----------------------------------------------------------------------------
void Settings::loadSettings()
{
    //    QString lang = settings->value("language/lang").toString();
    QString lang = Config::configuration()->getAppLang();

    setAPPLang(lang);
    ui->comBLanguage->setCurrentIndex(ui->comBLanguage->findText(lang));

    // load module settings

    QString t_folderbible = Config::configuration()->getBibleDir();
    QString t_folderdict = Config::configuration()->getDictDir();
    QString t_folderother = Config::configuration()->getOtherDir();

    // load font and viewer settings
    ui->chBBold->setChecked(Config::configuration()->getFontBold());
    ui->chBItalic->setChecked(Config::configuration()->getFontItalic());
    ui->chBStrike->setChecked(Config::configuration()->getFontStrike());
    ui->chBUnderline->setChecked(Config::configuration()->getFontUnderline());

    ui->LEBibleFolder->setText(t_folderbible);
    ui->LEDictFolder->setText(t_folderdict);
    ui->LEOtherFolder->setText(t_folderother);

    ui->sBFontSize->setValue(Config::configuration()->getFontSize());
    ui->fontComB->setCurrentFont(QFont(Config::configuration()->getFontFamily()));
    m_fontColor = Config::configuration()->getFontColor();
    m_viewerColor = Config::configuration()->getViewerColor();


    /// replace to AppDir/*  if empty

    //    QDir::currentPath();

    //    myDebug() << settings->value("language/lang");
    //    if (lang.isEmpty())
    //        lang = "Russian";
    //    setAPPLang(lang);
    //    ui->comBLanguage->setCurrentIndex(ui->comBLanguage->findText(lang));
}
///----------------------------------------------------------------------------
void Settings::saveSettings()
{
    if (ui->comBLanguage->currentText() != Config::configuration()->getAppLang())
    {
        emit SIGNAL_RetranslateGUI(ui->comBLanguage->currentText());
    }
    Config::configuration()->setAppLang(ui->comBLanguage->currentText());
    // save module settings
    Config::configuration()->setBibleDir(ui->LEBibleFolder->text());
    Config::configuration()->setDictDir(ui->LEDictFolder->text());
    Config::configuration()->setOtherDir(ui->LEOtherFolder->text());

    // save font settings and viewer settings
    Config::configuration()->setFontFamily(ui->fontComB->currentText());
    Config::configuration()->setFontSize(ui->sBFontSize->value());
    Config::configuration()->setFontColor(m_fontColor);
    Config::configuration()->setViewerColor(m_viewerColor);

    Config::configuration()->setFontBold(ui->chBBold->checkState());
    Config::configuration()->setFontItalic(ui->chBItalic->checkState());
    Config::configuration()->setFontStrike(ui->chBStrike->checkState());
    Config::configuration()->setFontUnderline(ui->chBUnderline->checkState());

    //    ui->sBFontSize->setValue(Config::configuration()->getFontSize());

    //    ui->fontComB->setCurrentFont(QFont(Config::configuration()->getFontFamily()));
}
///----------------------------------------------------------------------------
void Settings::createConnect()
{
    connect(ui->pBBibleFolder, SIGNAL(clicked()), SLOT(browseBibleDir()));
    connect(ui->pBOtherFolder, SIGNAL(clicked()), SLOT(browseOtherDir()));
    connect(ui->pBDictFolder, SIGNAL(clicked()), SLOT(browseDictDir()));

    connect(ui->pBColor, SIGNAL(clicked()), SLOT(selectFontColor()));
    connect(ui->pBBackgroundColor, SIGNAL(clicked()), SLOT(selectFontColor()));
}
///----------------------------------------------------------------------------
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

            emit SIGNAL_ReLoadModules();
            emit SIGNAL_ReLoadFontSettings();
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
///----------------------------------------------------------------------------
QString Settings::getAPPLang()
{
    return m_APP_Lang;
}
///----------------------------------------------------------------------------
void Settings::setAPPLang(QString new_lang)
{
    m_APP_Lang = new_lang;
    return;
}
///----------------------------------------------------------------------------
bool Settings::getModifySettings()
{
    if (ui->comBLanguage->currentText() != Config::configuration()->getAppLang())
        return true;
    if (ui->LEBibleFolder->text() != Config::configuration()->getBibleDir())
        return true;
    if (ui->LEDictFolder->text() != Config::configuration()->getDictDir())
        return true;
    if (ui->LEOtherFolder->text() != Config::configuration()->getOtherDir())
        return true;
    if (ui->sBFontSize->value() != Config::configuration()->getFontSize())
        return true;
    if (ui->fontComB->currentText() != Config::configuration()->getFontFamily())
        return true;
    if (m_fontColor != Config::configuration()->getFontColor())
        return true;

    return false;
}
///----------------------------------------------------------------------------
void Settings::setParams()
{
    ui->comBLanguage->setCurrentIndex(ui->comBLanguage->findText(getAPPLang()));
    ui->LEBibleFolder->setText(Config::configuration()->getBibleDir());
    ui->LEOtherFolder->setText(Config::configuration()->getOtherDir());
    ui->LEDictFolder->setText(Config::configuration()->getDictDir());
}
//------------------------------------------------------------------------------
void Settings::browseBibleDir()
{
    QFileDialog::Options options = QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly;
    QString directory = QFileDialog::getExistingDirectory(this,
                                                          tr("Select dir for bible modules"),
                                                          Config::configuration()->getAppDir(),
                                                          options);
    if (!directory.isEmpty())
    {
        ui->LEBibleFolder->setText(directory);
    }
}
//------------------------------------------------------------------------------
void Settings::browseDictDir()
{
    QFileDialog::Options options = QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly;
    QString directory = QFileDialog::getExistingDirectory(this,
                                                          tr("Select dir for dict modules"),
                                                          Config::configuration()->getAppDir(),
                                                          options);
    if (!directory.isEmpty())
    {
        ui->LEDictFolder->setText(directory);
    }
}
//------------------------------------------------------------------------------
void Settings::browseOtherDir()
{
    QFileDialog::Options options = QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly;
    QString directory = QFileDialog::getExistingDirectory(this,
                                                          tr("Select dir for other modules"),
                                                          Config::configuration()->getAppDir(),
                                                          options);
    if (!directory.isEmpty())
    {
        ui->LEOtherFolder->setText(directory);
    }
}
///----------------------------------------------------------------------------
void Settings::selectFontColor()
{
    QPushButton *button = (QPushButton *)sender();
    QColor t_color;
    t_color = QColorDialog::getColor(Config::configuration()->getFontColor(), this);
    if (!t_color.isValid())
    {
        return;
    }

    if (button->text().indexOf("background") >= 0)
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
///----------------------------------------------------------------------------
void Settings::retranslate()
{
    ui->retranslateUi(this);
}
///----------------------------------------------------------------------------
///----------------------------------------------------------------------------
///----------------------------------------------------------------------------
