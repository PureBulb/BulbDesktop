#include "pendantplugin.h"

PendantPlugin::PendantPlugin() {
    logInstance = LogDispacher::getInstance();

    connect(logInstance,&LogDispacher::sendLogd,this,&PendantPlugin::reportDebug);
    connect(logInstance,&LogDispacher::sendLogi,this,&PendantPlugin::reportInfo);
    connect(logInstance,&LogDispacher::sendLoge,this,&PendantPlugin::reportError);
    connect(logInstance,&LogDispacher::sendLogw,this,&PendantPlugin::reportWarring);
}

void PendantPlugin::loaded()
{
    MonitorWidget widget;

    logInstance->logd("PendantPlugin::loaded","MonitorPlugin is loaded");
}

BasePendantWidget *PendantPlugin::createNewWidget(int x, int y, int w, int h,uint64_t id)
{
    BasePendantWidget* widget = new MonitorWidget();
    widget->editMode();
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
    connect(widget,&BasePendantWidget::changeWidget,this,[=](uint64_t id,QRect geometry){emit changePendant(id,geometry);});
    connect(widget,&BasePendantWidget::closeWidget,this,[=](uint64_t id){emit closePendant(id);});
    widget->setId(id);
    if(id==0){
        widget->setId(QDateTime::currentMSecsSinceEpoch());
    }
    widget->setWindowTitle("Monitor");
    static_cast<MonitorWidget*>(widget)->setCity(settings["city"].toString());
    return widget;
}

QImage PendantPlugin::getIcon()
{
    return QImage (":/MonitorPlugin/icon.png");

}

void PendantPlugin::setSettings(QHash<QString, QVariant> _settings)
{
    settings = _settings;
    if(settings.find("city")==settings.end()){
        settings["city"]="beijing";
        emit requestUpdateSettings(settings);
    }
}

