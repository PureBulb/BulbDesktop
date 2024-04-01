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
            connect(instance,&IWallpaperPlugin::requestSettings,this,&WallpaperPluginUtils::onSettingChanged);
            //绑定日志功能
            connect(instance,&IWallpaperPlugin::reportDebug,this,&WallpaperPluginUtils::logDebugHandler);
            connect(instance,&IWallpaperPlugin::reportInfo,this,&WallpaperPluginUtils::logInfoHandler);
            connect(instance,&IWallpaperPlugin::reportWarring,this,&WallpaperPluginUtils::logWarringHandler);
            connect(instance,&IWallpaperPlugin::reportError,this,&WallpaperPluginUtils::logErrorHandler);
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

void WallpaperPluginUtils::onSettingChanged(QHash<QString, QVariant> _settings)
{

    for(auto i = plugins.keyValueBegin();i!=plugins.keyValueEnd();i++){
        if((*i).second==sender()){
            emit pluginSettingChanged((*i).first,_settings);
            (*i).second->responseSettings(_settings);
            break;
        }
    }
    emit
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

void WallpaperPluginUtils::logInfoHandler(QString module, QString msg)
{
    logi("wallpaperPlugin::"+module,msg);
}

void WallpaperPluginUtils::logDebugHandler(QString module, QString msg)
{
    logd("wallpaperPlugin::"+module,msg);
}

void WallpaperPluginUtils::logWarringHandler(QString module, QString msg)
{
    logw("wallpaperPlugin::"+module,msg);
}

void WallpaperPluginUtils::logErrorHandler(QString module, QString msg)
{
    loge("wallpaperPlugin::"+module,msg);
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
    for(auto key:plugins.keys()){
        QWidget* settingForm = plugins[key]->getSettingWidget();
        if(settingForm!=nullptr)
            result.insert(key,settingForm);
    }
    return result;
}
