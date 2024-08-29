#include "PendantChoseWidget.h"
#include "ui_PendantChoseWidget.h"

PendantChoseWidget::PendantChoseWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PendantChoseWidget)
{
    ui->setupUi(this);

}

void PendantChoseWidget::insert(QImage icon, QString name)
{
    PendantIconForm* widget = new PendantIconForm(icon,name,this);
    widget->resize(64,64);
    ui->pendantsView->addWidget(widget);
}

PendantChoseWidget::~PendantChoseWidget()
{
    delete ui;
}
