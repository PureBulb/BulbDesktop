#include "assistantitem.h"
#include "ui_assistantitem.h"

AssistantItem::AssistantItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AssistantItem)
{
    ui->setupUi(this);
}

AssistantItem::~AssistantItem()
{
    delete ui;
}
