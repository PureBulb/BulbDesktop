#include "PendantPluginUtils.h"

PendantPluginUtils::PendantPluginUtils(QObject *parent)
    :BasePluginUtils(PENDANT_PLUGINS_DIR,parent)
{
    connect(&handler,&DragDropEventHandler::pendantDrop,this,&PendantPluginUtils::onDropPendantEvent);
}

PendantPluginUtils::~PendantPluginUtils()
{

}

void PendantPluginUtils::load()
{
    BasePluginUtils::load();
    object2Interface();
}

void PendantPluginUtils::createByConfig(QWidget* parent)
{
    QHash<QString,QVariant> setting = settingsManager->getPluginSettings(PLUGIN_SETTING_NAME);
    foreach(auto pendantObject,setting["pendants"].toJsonArray()){
        QJsonObject obj = pendantObject.toObject();
        int x = obj["x"].toInt();
        int y = obj["y"].toInt();
        int w = obj["w"].toInt();
        int h = obj["h"].toInt();
        uint64_t id = obj["id"].toString().toULongLong();
        QString pluginName = obj["name"].toString();
        BasePendantWidget* widget = plugins[pluginName]->createNewWidget(x,y,w,h,id);
        widget->setParent(parent);
        widget->show();
    }

}

void PendantPluginUtils::createByConfig(const QVector<QWidget *> &wallpapers)
{
    QHash<QString,QVariant> setting = settingsManager->getPluginSettings(PLUGIN_SETTING_NAME);
    foreach(auto pendantObject,setting["pendants"].toJsonArray()){
        QJsonObject obj = pendantObject.toObject();
        int x = obj["x"].toInt();
        int y = obj["y"].toInt();
        int w = obj["w"].toInt();
        int h = obj["h"].toInt();
        uint64_t id = obj["id"].toString().toULongLong();
        QString pluginName = obj["name"].toString();

        BasePendantWidget* widget = plugins[pluginName]->createNewWidget(x,y,w,h,id);
        widget->raise();
        widget->show();
        plugins[pluginName]->endEditMode(wallpapers);
    }
}

void PendantPluginUtils::object2Interface()
{
    foreach(auto loader,loaders){
        QObject *obj = nullptr;
        IPendantPlugin *instance = nullptr;
        obj = loader->instance();
        instance = qobject_cast<IPendantPlugin*>(obj);
        if(instance){
            QString pluginName = loader->metaData().value("MetaData").toObject().value("plugin-name").toString();
            plugins.insert(pluginName,instance);
            icons.insert(pluginName,instance->getIcon());
            int i =10;
            while(i--)
                pendantChooseWidget.insert(instance->getIcon(),pluginName);

            //绑定日志功能
            connect(instance,&IPendantPlugin::reportDebug,this,&BasePluginUtils::logDebugHandler);
            connect(instance,&IPendantPlugin::reportInfo,this,&BasePluginUtils::logInfoHandler);
            connect(instance,&IPendantPlugin::reportWarring,this,&BasePluginUtils::logWarringHandler);
            connect(instance,&IPendantPlugin::reportError,this,&BasePluginUtils::logErrorHandler);

            connect(instance,&IPendantPlugin::changePendant,this,&::PendantPluginUtils::onPendantChange);
            connect(instance,&IPendantPlugin::closePendant,this,&::PendantPluginUtils::onPendantClose);

            instance->loaded();
        }

    }
}

void PendantPluginUtils::startEditorMode()
{
    foreach (auto plugin, plugins) {
        plugin->startEditMode();
    }
    pendantChooseWidget.show();
    auto rect = pendantChooseWidget.screen()->geometry();
    rect.setWidth(rect.width()*0.3);

    pendantChooseWidget.setGeometry(rect);
    WindAdapterV2::getInstance()->hideIcon();
}

void PendantPluginUtils::stopEditorMode(const QVector<QWidget *> &wallpapers)
{
    foreach (auto plugin, plugins) {
        plugin->endEditMode(wallpapers);
    }
    pendantChooseWidget.hide();
    WindAdapterV2::getInstance()->showIcon();
}

BasePendantWidget *PendantPluginUtils::newPendant(QString pluginName, int x, int y, int w, int h)
{
    BasePendantWidget* widget = plugins[pluginName]->createNewWidget(x,y,w,h);
    QJsonObject pendant;
    pendant.insert("x",x);
    pendant.insert("y",x);
    pendant.insert("w",x);
    pendant.insert("h",x);
    pendant.insert("name",pluginName);
    pendant.insert("id",QString::number(widget->getId()));
    QHash<QString,QVariant> settings = settingsManager->getPluginSettings(PLUGIN_SETTING_NAME);
    QJsonArray array = settings["pendants"].toJsonArray();
    array.append(pendant);
    settings["pendants"] = array;
    settingsManager->setPluginSettings(PLUGIN_SETTING_NAME,settings);
    widget->show();
    return widget;
}

void PendantPluginUtils::setSettings(SettingManager *setting)
{
    settingsManager = setting;
}

QHash<QString, QImage> PendantPluginUtils::getPluginThumbnails()
{
    return icons;
}

QImage PendantPluginUtils::getPluginThumbnailByName(const QString &name)
{
    return icons[name];
}

void PendantPluginUtils::installDragDropHandler(const QVector<QWidget *> &wallpapers)
{
    for(auto wallpaper:wallpapers){
        wallpaper->installEventFilter(&handler);
    }
}

void PendantPluginUtils::onPendantChange(uint64_t id, QRect geometry)
{
    QtConcurrent::run([=](){
        QHash<QString,QVariant> settings = settingsManager->getPluginSettings(PLUGIN_SETTING_NAME);
        QJsonArray pendants = settings["pendants"].toJsonArray();
        for(auto i = pendants.begin();i!=pendants.end();i++){
            auto pendant = (*i).toObject();
            qDebug()<<pendant["id"].toString().toULongLong()<<id;
            if(pendant["id"].toString().toULongLong() == id){
                int x,y,w,h;
                geometry.getRect(&x,&y,&w,&h);
                pendant["x"] = x;
                pendant["y"] = y;
                pendant["w"] = w;
                pendant["h"] = h;
                (*i) = pendant;
            }
        }
        settings["pendants"] = pendants;
        settingsManager->setPluginSettings(PLUGIN_SETTING_NAME,settings);
    });

}

void PendantPluginUtils::onPendantClose(uint64_t id)
{
    QtConcurrent::run([=](){
        QHash<QString,QVariant> settings = settingsManager->getPluginSettings(PLUGIN_SETTING_NAME);
        QJsonArray pendants = settings["pendants"].toJsonArray();
        for(auto i = pendants.begin();i!=pendants.end();i++){
            auto pendant = (*i).toObject();
            if(pendant["id"].toString().toULongLong() == id){
                i = pendants.erase(i);
                --i;
            }
        }
        settings["pendants"] = pendants;
        settingsManager->setPluginSettings(PLUGIN_SETTING_NAME,settings);
    });

}

void PendantPluginUtils::onDropPendantEvent(QString pendantName, QPoint pos)
{
    auto widget = newPendant(pendantName,pos.x(),pos.y(),100,100);
}
