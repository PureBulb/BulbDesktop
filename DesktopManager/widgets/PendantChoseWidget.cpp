#include "PendantChoseWidget.h"
#include "ui_PendantChoseWidget.h"

PendantChoseWidget::PendantChoseWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PendantChoseWidget)
{
    ui->setupUi(this);
}

PendantChoseWidget::~PendantChoseWidget()
{
    delete ui;
}
