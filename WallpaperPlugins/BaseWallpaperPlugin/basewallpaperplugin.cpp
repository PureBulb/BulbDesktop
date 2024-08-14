#include "BaseWallpaperPlugin.h"
#include "QDebug"

void BaseWallpaperPlugin::bindWallPaperEvent()
{
    for(auto wallpaper:wallpaperManager.getWallpapers()){
        connect(wallpaper,&Wallpaper::triggedIcons,this,&BaseWallpaperPlugin::onTriggedIcons);
    }

}

BaseWallpaperPlugin::BaseWallpaperPlugin()
    :settingForm(nullptr)
{
    logInstance = LogDispacher::getInstance();
    connect(this,&BaseWallpaperPlugin::settingChangeSucceeded,&wallpaperManager,&BaseWallpaperManager::updateSettings);

    connect(logInstance,&LogDispacher::sendLogd,this,&BaseWallpaperPlugin::reportDebug);
    connect(logInstance,&LogDispacher::sendLogi,this,&BaseWallpaperPlugin::reportInfo);
    connect(logInstance,&LogDispacher::sendLoge,this,&BaseWallpaperPlugin::reportError);
    connect(logInstance,&LogDispacher::sendLogw,this,&BaseWallpaperPlugin::reportWarring);

}

void BaseWallpaperPlugin::loaded()
{
    // you can bind event in this func
    bindWallPaperEvent();
    logInstance->logi("BaseWallpaperPlugin::unloaded","base is loaded");
}

void BaseWallpaperPlugin::unloaded()
{
    logInstance->logi("BaseWallpaperPlugin::unloaded","base is unloaded");
}

void BaseWallpaperPlugin::activated()
{
    wallpaperManager.display();
}

void BaseWallpaperPlugin::finished()
{
    emit displayFinished();
}

void BaseWallpaperPlugin::setSettings(QHash<QString, QVariant> _settings)
{
    settings = _settings;
    wallpaperManager.setSettings(settings);
    if(settingForm == nullptr){
        settingForm = new SettingsForm(settings);
        connect(settingForm,&SettingsForm::settingFormChanged,this,[=](QHash<QString, QVariant> _settings){
            emit requestUpdateSettings(_settings);
        });
        connect(this,&BaseWallpaperPlugin::settingChangeSucceeded,settingForm,&SettingsForm::updateSettings);
    }
    else{
        settingForm->setSettings(settings);
    }
}

QVector<QWidget *> BaseWallpaperPlugin::getWallpapers()
{
    auto w = wallpaperManager.getWallpapers();
    QVector<QWidget *> result(w.begin(),w.end());

    return result;
}
//if you don't have setting widget you should return nullptr
QWidget *BaseWallpaperPlugin::getSettingWidget()
{
    return settingForm;
}

void BaseWallpaperPlugin::setVolume(uint8_t value)
{
    wallpaperManager.volumeChanged(value);
}

void BaseWallpaperPlugin::pause()
{
    wallpaperManager.pause();
}

void BaseWallpaperPlugin::resume()
{
    wallpaperManager.resume();
}

void BaseWallpaperPlugin::stop()
{
    wallpaperManager.stop();
}

