#include "subregionform.h"
#include "ui_subregionform.h"

SubregionForm::SubregionForm(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::SubregionForm)
{
    ui->setupUi(this);
}

SubregionForm::~SubregionForm()
{
    delete ui;
}
