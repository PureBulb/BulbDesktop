#include "assistantform.h"
#include "ui_assistantform.h"

AssistantForm::AssistantForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AssistantForm)
{
    ui->setupUi(this);
}

AssistantForm::~AssistantForm()
{
    delete ui;
}
