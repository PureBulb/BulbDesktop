#include "AssistantForm.h"
#include "ui_assistantform.h"
#include <QtDebug>
AssistantForm::AssistantForm(QWidget *parent) :
    QWidget(parent),
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

void AssistantForm::nextPage()
{
    for(int64_t i = pageCount*PAGE_SIZE,j=0;i<results.size()&&j<PAGE_SIZE;i++,j++){
        auto itemData = results[i];
        AssistantItem *item = new AssistantItem(itemData);
        item->setSizeHint(item->size());
    //    item->show();
        ui->itemsWidget->addItem(item);
        ui->itemsWidget->setItemWidget(item,item);
        connect(item,&AssistantItem::clicked,itemData.getItemClick());
    }
    pageCount++;
}

void AssistantForm::cleanData()
{
    pageCount = 0;
    results.clear();
    ui->itemsWidget->clear();
}

void AssistantForm::init()
{
    utils.load();

    //bind event
    installEventFilter(this);
    connect(ui->itemsWidget->verticalScrollBar(),&QScrollBar::valueChanged,this,&AssistantForm::onItemWidgetScrollBarChanged);
}

void AssistantForm::onSettingsChanged()
{

}

void AssistantForm::onItemWidgetScrollBarChanged(int value)
{
    if(ui->itemsWidget->verticalScrollBar()->maximum() == value) {
        nextPage();
    }
}

void AssistantForm::query(const QString &arg1)
{
    cleanData();
    results = utils.query(arg1.trimmed());
    nextPage();

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

bool AssistantForm::event(QEvent *event)
{
    if(event->type() == QEvent::ActivationChange  ){
        if(QApplication::activeWindow() != this){
            cleanData();
            this->hide();
        }
    }
    return QWidget::event(event);
}

bool AssistantForm::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    if(eventType == "windows_generic_MSG")
        {
            MSG* pMsg = reinterpret_cast<MSG*>(message);
            if(pMsg->message == WM_HOTKEY)
            {
                atomId = GlobalFindAtomA("Bulb");
                qDebug()<<pMsg->wParam;
                if(pMsg->wParam == atomId){
                    qDebug()<<"hot key press";
                }

            }
        }
        return QWidget::nativeEvent(eventType,message,result);
}



