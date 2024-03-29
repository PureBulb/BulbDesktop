#ifndef WALLPAPERPLUGINUTILS_H
#define WALLPAPERPLUGINUTILS_H

#include <QVector>
#include <QThread>
#include "BasePluginUtils.h"
#include "../../plugins/IWallpaperPlugin.h"

#define WALLPAPER_PLUGINS_DIR "./WallpaperPlugins"

class WallpaperPluginUtils : public BasePluginUtils
{
    Q_OBJECT
    /*TODO: change lifecycle*/
private:
    uint8_t pluginIndex;
    SettingManager* settingsManager;
    QHash<QString,IWallpaperPlugin *> plugins;
    QHash<QString,IWallpaperPlugin *>::Iterator activatePlugin;
    QThread wallpaperThread;
    void object2Interface();
 public:
    WallpaperPluginUtils();

    // PluginUtils interface
    void load();
    void unload();



//    void setSettings(QHash<QString,QVariant> settings);

signals:
    void pluginSettingChanged(QString,QHash<QString, QVariant> );
    void triggedIcons();

public slots:
    void nextWallpaper();
    void onSettingChanged(QHash<QString, QVariant> _settings);
    QVector<QWidget *> getWallpaperWidgets();
    void onRequestSettings();
    //value 0-100
    void onVolumeChanged(int value);
    void pause();
    void resume();

    void onTriggedIcons();
    // BasePluginUtils interface
public:
    void setSettings(SettingManager *manager);
    QHash<QString,QWidget*> getSettingForms();
};

#endif // WALLPAPERPLUGINUTILS_H
