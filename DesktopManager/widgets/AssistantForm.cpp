#include "AssistantForm.h"
#include "ui_assistantform.h"

AssistantForm::AssistantForm(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::AssistantForm),
    editorQueryTimer(nullptr)
{
    ui->setupUi(this);
    init();
}

AssistantForm::~AssistantForm()
{
    delete ui;
    utils.unload();
}

void AssistantForm::init()
{
    utils.load();

}

void AssistantForm::onSettingsChanged()
{

}

void AssistantForm::query(const QString &arg1)
{
        qDebug()<<arg1.trimmed();
        QList<QueryResult> result = utils.query(arg1.trimmed());
        ui->itemsWidget->clear();
        for(auto i : result){
            AssistantItem *item = new AssistantItem(i);
            item->setSizeHint(item->size());
        //    item->show();
            ui->itemsWidget->addItem(item);
            ui->itemsWidget->setItemWidget(item,item);
            connect(item,&AssistantItem::clicked,i.getItemClick());
        }
}

void AssistantForm::on_inputEdit_textChanged(const QString &arg1)
{
    if(editorQueryTimer == nullptr){
        editorQueryTimer = new QTimer(this);

    }
    else{
        editorQueryTimer->stop();
        editorQueryTimer->deleteLater();
        editorQueryTimer = new QTimer(this);
    }

    editorQueryTimer->setInterval(1000);
    connect(editorQueryTimer,&QTimer::timeout,this,[=](){
        editorQueryTimer->stop();
        query(arg1);
        editorQueryTimer->deleteLater();
        editorQueryTimer = nullptr;
    });
    editorQueryTimer->start();
}


