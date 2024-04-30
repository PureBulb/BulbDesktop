#ifndef SETTINGMANAGER_H
#define SETTINGMANAGER_H

#include <QObject>
#include <QSettings>
#define INI_CORE_GROUP "core"
class SettingManager:public QObject
{
    Q_OBJECT
private:
    QSettings settings;
    void extracted(QHash<QString, QVariant> &result);
    QHash<QString,QVariant> getSettingsByGroup(QString groupName);
    void writeSettingsByGroup(QString groupName,QHash<QString,QVariant> _settings);
public:
    SettingManager(QObject* parent = nullptr);
    QHash<QString,QVariant> getPluginSettings(QString pluginName);
    QHash<QString,QVariant> getCoreSettings();
    void setPluginSettings(QString pluginName,QHash<QString,QVariant> settings);
    void setCoreSettings(QHash<QString,QVariant> settings);
signals:
    void pluginSettingsChanged(QString pluginName);
    void coreSettingsChanged();

};

#endif // SETTINGMANAGER_H
