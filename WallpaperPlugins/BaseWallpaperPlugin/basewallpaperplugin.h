#ifndef BASEWALLPAPERPLUGIN_H
#define BASEWALLPAPERPLUGIN_H

#include <QHash>
#include <QVariant>
#include "IWallpaperPlugin.h"
#include "BaseWallpaperManager.h"
#include "settingsform.h"

class BaseWallpaperPlugin: public IWallpaperPlugin{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID PLUGIN_IID FILE "BaseWallpaperPlugin.json")
    Q_INTERFACES(IWallpaperPlugin)
private:
    QHash<QString,QVariant> settings;
    BaseWallpaperManager wallpaperManager;
    SettingsForm* settingForm;
    // IWallpaperPlugin interface
private:
    void bindWallPaperEvent();
public:
    BaseWallpaperPlugin();
    void loaded();
    void unloaded();
    void activated();
    void finished();
    void setSettings(QHash<QString,QVariant> _settings);
    QVector<QWidget *> getWallpapers();
    QWidget *getSettingWidget();
    void setVolume(uint8_t value);
    void pause();
    void resume();

    void stop();

private slots:
    void dipatchSettingChanged(QHash<QString, QVariant> _settings);
};
#endif // BASEWALLPAPERPLUGIN_H
