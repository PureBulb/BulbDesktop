#include "PendantIconform.h"
#include "ui_PendantIconform.h"

PendantIconForm::PendantIconForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PendantIconForm)
{
    ui->setupUi(this);
}

PendantIconForm::~PendantIconForm()
{
    delete ui;
}
