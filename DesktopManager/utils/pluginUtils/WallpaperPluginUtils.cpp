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

            connect(instance,&IWallpaperPlugin::triggedIcons,this,&WallpaperPluginUtils::onTriggedIcons);
            //绑定设置更新事件
            connect(instance,&IWallpaperPlugin::requestUpdateSettings,this,&WallpaperPluginUtils::onRequestUpdateSettings);
            //绑定日志功能
            connect(instance,&IWallpaperPlugin::reportDebug,this,&WallpaperPluginUtils::logDebugHandler);
            connect(instance,&IWallpaperPlugin::reportInfo,this,&WallpaperPluginUtils::logInfoHandler);
            connect(instance,&IWallpaperPlugin::reportWarring,this,&WallpaperPluginUtils::logWarringHandler);
            connect(instance,&IWallpaperPlugin::reportError,this,&WallpaperPluginUtils::logErrorHandler);

            instance->loaded();


        }

    }
}

WallpaperPluginUtils::WallpaperPluginUtils()
    :BasePluginUtils(WALLPAPER_PLUGINS_DIR)
    ,pluginIndex(0)
    ,settingsManager(nullptr)
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
    foreach(auto plugin,plugins){
        plugin->unloaded();
    }

}

void WallpaperPluginUtils::nextWallpaper()
{
    emit activatePlugin.value()->nextWallpaper();
}


void WallpaperPluginUtils::nextPlugin()
{
    if(activatePlugin!=plugins.end()){
        activatePlugin.value()->stop();

        activatePlugin++;
        if(activatePlugin==plugins.end()){
            nextPlugin();
            return;
        }
        activatePlugin.value()->activated();
    }
    else{
        activatePlugin = plugins.begin();
        activatePlugin.value()->activated();
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

void WallpaperPluginUtils::onRequestUpdateSettings(QHash<QString, QVariant> _settings)
{
    QObject* obj = sender();
    IWallpaperPlugin* instant = qobject_cast<IWallpaperPlugin*>(obj);
    QString pluginName = plugins.key(instant);
    logInfoHandler("WallpaperPluginUtils::onRequestUpdateSettings",pluginName+"request settings");
    settingsManager->setPluginSettings(pluginName,_settings);
    instant->responseSettings(_settings);
}


void WallpaperPluginUtils::setSettings(SettingManager *manager)
{
    settingsManager = manager;
    for(auto plugin = plugins.begin();plugin!=plugins.end();plugin++){
        auto settings = settingsManager->getPluginSettings(plugin.key());
        plugin.value()->setSettings(settings);
    }
}

QHash<QString, QWidget *> WallpaperPluginUtils::getSettingForms()
{
    QHash<QString,QWidget*> result;
    foreach(auto key,plugins.keys()){
        QWidget* settingForm = plugins[key]->getSettingWidget();
        if(settingForm!=nullptr)
            result.insert(key,settingForm);
    }
    return result;
}
