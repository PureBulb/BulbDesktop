#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include <QGuiApplication>
#include <QScreen>
#include <QSystemTrayIcon>
#include <QWidgetAction>
#include <QMenu>

#include "widgets/AssistantForm.h"
#include "widgets/SettingWidget.h"
#include "components/trayiconmenu.h"
#include "SettingManager.h"
#include "utils/WindAdapterV2.h"
#include "utils/pluginUtils/AssistantPluginUtils.h"
#include "utils/pluginUtils/wallpaperpluginutils.h"

class Manager:public QObject
{
    Q_OBJECT
private:
    SettingWidget* settingWidget;
    WindAdapterV2* winAdapter;
    AssistantPluginUtils assistantPluginUtils;
    WallpaperPluginUtils wallpaperPluginUtils;
    SettingManager settingsManager;

    QSystemTrayIcon *trayIcon;
    TrayIconMenu* trayIconMenu;
    AssistantForm *assistantForm;

    bool hideIcons;
private:
    void pluginsLoad();
    void initTray();

public:
    Manager(QObject* parent = nullptr);
protected slots:
    void onCoreSettingsChanged();
    void onPluginSettingsChanged(QString pluginName,QHash<QString, QVariant> _settings);
    void onTrigggedIcons();

};

#endif // MANAGER_H
