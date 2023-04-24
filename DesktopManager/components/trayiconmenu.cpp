#include "trayiconmenu.h"
#include "ui_trayiconmenu.h"

TrayIconMenu::TrayIconMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TrayIconMenu)
{
    ui->setupUi(this);
}

TrayIconMenu::~TrayIconMenu()
{
    delete ui;
}

void TrayIconMenu::on_horizontalSlider_valueChanged(int value)
{
    ui->volumeLabel->setText(QString::number(value)+"%");
    emit volumeChange(value);
}

void TrayIconMenu::on_quitBtn_clicked()
{
    QApplication::quit();
}

void TrayIconMenu::on_pauseBtn_clicked()
{
    emit pauseWallpaper();
}

void TrayIconMenu::on_startBtn_clicked()
{
    emit resumeWallpaper();
}

void TrayIconMenu::on_nextBtn_clicked()
{
    emit nextWallpaper();
}

void TrayIconMenu::on_settingsBtn_clicked()
{
    settingWidget->show();
}

void TrayIconMenu::setSubregionForm(BaseWidget *value)
{
    SubregionForm = value;
}

void TrayIconMenu::setSettingWidget(BaseWidget *value)
{
    settingWidget = value;
}

void TrayIconMenu::on_assistorBtn_clicked()
{
    SubregionForm->show();
}
