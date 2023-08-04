#include "assistantitem.h"
#include "ui_assistantitem.h"

void AssistantItem::mousePressEvent(QMouseEvent *event)
{
    emit clicked();
}

AssistantItem::AssistantItem(QListWidget *parent) :
    QWidget(parent),
    QListWidgetItem(parent),
    ui(new Ui::AssistantItem)
{
    ui->setupUi(this);
}
AssistantItem::AssistantItem(QueryResult &result, QListWidget *parent) :
    QWidget(parent),
    QListWidgetItem(parent),
    ui(new Ui::AssistantItem)
{
    ui->setupUi(this);

    type = result.getType();
    auto getIconFunc = result.getIconFunc();
    setIcon(getIconFunc());
    setTitle(result.getTitle());
    setDescription(result.getDescription());

}

AssistantItem *AssistantItem::setIcon(QIcon image)
{

    ui->iconLabel->setPixmap(image.pixmap(64,64));

    return this;
}

AssistantItem *AssistantItem::setTitle(QString title)
{
    ui->titleLabel->setText(title);
    return this;
}

AssistantItem *AssistantItem::setDescription(QString description)
{
    ui->descriptLabel->setText(description);
    return this;
}

AssistantItem::~AssistantItem()
{
    delete ui;
}
