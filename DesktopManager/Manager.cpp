#include "Manager.h"

void Manager::pluginsLoad()
{
    assistantPluginUtils.load();
    wallpaperPluginUtils.load();
    connect(&wallpaperPluginUtils,&WallpaperPluginUtils::pluginSettingChanged,this,&Manager::onPluginSettingsChanged);
    connect(&wallpaperPluginUtils,&WallpaperPluginUtils::triggedIcons,this,&Manager::onTrigggedIcons);
}

void Manager::initTray()
{
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setToolTip("SystemTray Program");
    trayIcon->setIcon(QIcon(":/resource/icons/icon.png"));
    trayIconMenu = new TrayIconMenu();
    settingWidget = new SettingWidget();
    trayIconMenu->setSettingWidget(settingWidget);
    assistantForm = new AssistantForm();
    atomId = GlobalAddAtomA("Bulb");
    if(RegisterHotKey(HWND(assistantForm->winId()),atomId,MOD_CONTROL,'1'))
        trayIconMenu->setAssistantForm(assistantForm);
//    trayIconMenu->setSubregionForm();
    QWidgetAction* action = new QWidgetAction(this);
    QMenu* menu = new QMenu();
    action->setDefaultWidget(trayIconMenu);
    menu->addAction(action);
    trayIcon->setContextMenu(menu);

    connect(trayIconMenu,&TrayIconMenu::exit,this,&Manager::onExit);
    connect(trayIconMenu,&TrayIconMenu::volumeChange,&wallpaperPluginUtils,&WallpaperPluginUtils::onVolumeChanged);
    connect(trayIconMenu,&TrayIconMenu::pauseWallpaper,&wallpaperPluginUtils,&WallpaperPluginUtils::pause);
    connect(trayIconMenu,&TrayIconMenu::resumeWallpaper,&wallpaperPluginUtils,&WallpaperPluginUtils::resume);

    trayIcon->show();

}



Manager::Manager(QObject *parent)
    :QObject(parent)
    ,winAdapter(nullptr)
    ,hideIcons(false)
{

    winAdapter = WindAdapterV2::getInstance();

    pluginsLoad();

    wallpaperPluginUtils.setSettings(&settingsManager);

    wallpaperPluginUtils.nextWallpaper();

    for(auto wallpaper:wallpaperPluginUtils.getWallpaperWidgets()){
       winAdapter->installDesktopEventFilter( (HWND)wallpaper->winId());
       winAdapter->underOnProgmanW((HWND)wallpaper->winId());  
    }
    initTray();


    settingWidget->addSettingItem(wallpaperPluginUtils.getSettingForms());
}

void Manager::onCoreSettingsChanged()
{

}

void Manager::onPluginSettingsChanged(QString pluginName, QHash<QString, QVariant> _settings)
{
    qDebug()<<pluginName<<_settings;
    settingsManager.setPluginSettings(pluginName,_settings);
}

void Manager::onTrigggedIcons()
{
    if(hideIcons){
        winAdapter->hideIcon();
    }
    else{
        winAdapter->showIcon();
    }
    hideIcons = !hideIcons;
}

void Manager::onExit()
{
    UnregisterHotKey((HWND)assistantForm->winId(),atomId);
    GlobalDeleteAtom(atomId);
    QApplication::quit();
}
