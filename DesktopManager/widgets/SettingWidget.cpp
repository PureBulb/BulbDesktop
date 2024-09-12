#include "SettingWidget.h"
#include "ui_SettingWidget.h"

SettingWidget::SettingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingWidget)
{
    ui->setupUi(this);
    setWindowTitle("设置");
}

SettingWidget::~SettingWidget()
{
    delete ui;
}

void SettingWidget::addSettingItem(QHash<QString, QWidget *> widgets)
{
   for(auto key:widgets.keys()){
        ui->tabWidget->addTab(widgets[key],key);
   }
}
