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
