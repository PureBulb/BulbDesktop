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



void TrayIconMenu::on_quitBtn_clicked()
{
    emit exit();
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

void TrayIconMenu::setAssistantForm(QWidget *value)
{
    assistantForm = value;
}

void TrayIconMenu::setSettingWidget(QWidget *value)
{
    settingWidget = value;
}

void TrayIconMenu::on_assistorBtn_clicked()
{
    assistantForm->show();
//    QMessageBox::information(this,"开发中","让生产队的驴歇歇吧 ");
}

void TrayIconMenu::on_volumeSlider_valueChanged(int value)
{
    ui->volumeLabel->setText(QString::number(value)+"%");
    emit volumeChange(value);
}

void TrayIconMenu::on_editBtn_clicked()
{
    emit triggedEditMode();
}

