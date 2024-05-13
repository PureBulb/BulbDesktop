#include "SettingManager.h"
#include "QDebug"
QHash<QString, QVariant> SettingManager::getSettingsByGroup(QString groupName)
{
    QHash<QString,QVariant> result;

    settings.beginGroup(groupName);
    for(auto key:settings.allKeys()){
        result[key] = settings.value(key);
    }
    settings.endGroup();
    return result;
}

void SettingManager::writeSettingsByGroup(QString groupName,QHash<QString,QVariant> _settings)
{

    QHash<QString,QVariant> result;
    settings.beginGroup(groupName);
    for(auto key:_settings.keys()){
        settings.setValue(key,_settings[key]);
    }
    settings.endGroup();
}

SettingManager::SettingManager(QObject *parent)
    :QObject(parent)
    ,settings("./setting.ini",QSettings::IniFormat)
{

}

QHash<QString, QVariant> SettingManager::getPluginSettings(QString pluginName)
{
    return getSettingsByGroup(pluginName);
}

QHash<QString, QVariant> SettingManager::getCoreSettings()
{
    return getSettingsByGroup(INI_CORE_GROUP);
}

void SettingManager::setPluginSettings(QString pluginName, QHash<QString, QVariant> settings)
{
    writeSettingsByGroup(pluginName,settings);
    emit pluginSettingsChanged(pluginName);
}

void SettingManager::setCoreSettings(QHash<QString, QVariant> settings)
{
    writeSettingsByGroup(INI_CORE_GROUP,settings);
}
