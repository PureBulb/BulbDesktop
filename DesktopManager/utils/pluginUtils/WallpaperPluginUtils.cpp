#include "WallpaperPluginUtils.h"
#include <QDebug>
void WallpaperPluginUtils::object2Interface()
{
    for(auto loader: loaders){
        QObject *obj = nullptr;
        IWallpaperPlugin *instance = nullptr;
        obj = loader->instance();
        instance = qobject_cast<IWallpaperPlugin*>(obj);
        if(instance){
            QString pluginName = loader->metaData().value("MetaData").toObject().value("plugin-name").toString();
            plugins.insert(pluginName,instance);
            instance->loaded();
            connect(instance,&IWallpaperPlugin::triggedIcons,this,&WallpaperPluginUtils::onTriggedIcons);
            connect(instance,&IWallpaperPlugin::settingsChanged,this,&WallpaperPluginUtils::settingChanged);
        }

    }
}

WallpaperPluginUtils::WallpaperPluginUtils()
    :BasePluginUtils(WALLPAPER_PLUGINS_DIR)
    ,pluginIndex(0)
{

}

void WallpaperPluginUtils::load()
{
    BasePluginUtils::load();
    object2Interface();
    activatePlugin = plugins.end();

}

void WallpaperPluginUtils::unload()
{
    for(auto plugin: plugins){
        plugin->unloaded();
    }

}


void WallpaperPluginUtils::nextWallpaper()
{
    if(activatePlugin!=plugins.end()){
        activatePlugin.value()->stop();


        activatePlugin++;
        if(activatePlugin==plugins.end()){
            nextWallpaper();
            return;
        }
        activatePlugin.value()->activated();
    }
    else{
        activatePlugin = plugins.begin();
        activatePlugin.value()->activated();
    }


}

void WallpaperPluginUtils::settingChanged(QHash<QString, QVariant> _settings)
{

    for(auto i = plugins.keyValueBegin();i!=plugins.keyValueEnd();i++){
        if((*i).second==sender()){
            emit pluginSettingChanged((*i).first,_settings);
            break;
        }
    }
}



QVector<QWidget *> WallpaperPluginUtils::getWallpaperWidgets()
{
    if(activatePlugin!=plugins.end()){
        auto res = activatePlugin.value()->getWallpapers();
        return res;
    }
    return QVector<QWidget *>();
}

void WallpaperPluginUtils::onRequestSettings()
{
    QObject* obj = sender();
    IWallpaperPlugin* instant = qobject_cast<IWallpaperPlugin*>(obj);
    QString pluginName = plugins.key(instant);
    qDebug()<<pluginName<<"request settings";
    instant->setSettings(settingsManager->getPluginSettings(pluginName));


}

void WallpaperPluginUtils::onVolumeChanged(int value)
{
    activatePlugin.value()->setVolume(value);
}

void WallpaperPluginUtils::pause()
{
    activatePlugin.value()->pause();
}

void WallpaperPluginUtils::resume()
{
    activatePlugin.value()->resume();
}

void WallpaperPluginUtils::onTriggedIcons()
{
    emit triggedIcons();
}

void WallpaperPluginUtils::setSettings(SettingManager *manager)
{
    settingsManager = manager;
    for(auto plugin = plugins.begin();plugin!=plugins.end();plugin++){
        auto settings = settingsManager->getPluginSettings(plugin.key());
        plugin.value()->setSettings(settings);
        connect(plugin.value(),&IWallpaperPlugin::requestSettings,this,&WallpaperPluginUtils::onRequestSettings);
    }
}

QHash<QString, QWidget *> WallpaperPluginUtils::getSettingForms()
{
    QHash<QString,QWidget*> result;
    for(auto key:plugins.keys()){
        QWidget* settingForm = plugins[key]->getSettingWidget();
        if(settingForm!=nullptr)
            result.insert(key,settingForm);
    }
    return result;
}
