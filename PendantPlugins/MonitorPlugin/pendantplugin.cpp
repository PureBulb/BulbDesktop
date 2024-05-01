#include "pendantplugin.h"

PendantPlugin::PendantPlugin() {
    logInstance = LogDispacher::getInstance();

    connect(logInstance,&LogDispacher::sendLogd,this,[=](QString module,QString msg){emit reportDebug(module,msg);});
    connect(logInstance,&LogDispacher::sendLogi,this,[=](QString module,QString msg){emit reportInfo(module,msg);});
    connect(logInstance,&LogDispacher::sendLoge,this,[=](QString module,QString msg){emit reportError(module,msg);});
    connect(logInstance,&LogDispacher::sendLogw,this,[=](QString module,QString msg){emit reportWarring(module,msg);});
}

void PendantPlugin::loaded()
{
    logInstance->logd("PendantPlugin::loaded","MonitorPlugin is loaded");
}

BasePendantWidget *PendantPlugin::createNewWidget(int x, int y, int w, int h)
{

    BasePendantWidget* widget = new MonitorWidget();
    widget->setGeometry(x,y,w,h);
    widgets.append(widget);
    if(!isEditMode){
        logInstance->logd("PendantPlugin::createNewWidget::!EditModestart",QString::number(widget->windowFlags()));
        widget->setWindowFlags(widget->windowFlags()| Qt::FramelessWindowHint);
        logInstance->logd("PendantPlugin::createNewWidget::!EditModeend",QString::number(widget->windowFlags()));
    }
    else{
        logInstance->logd("PendantPlugin::createNewWidget::EditModestart",QString::number(widget->windowFlags()));
        widget->setWindowFlags(widget->windowFlags() & (~Qt::FramelessWindowHint));
        logInstance->logd("PendantPlugin::createNewWidget::EditModeend",QString::number(widget->windowFlags()));
    }
    return widget;
}
