#include "context.h"
QSettings* Context::settings = new QSettings("./setting.ini",QSettings::IniFormat);
const char* Context::startWallpaper = "app/startWallpaper";
const char* Context::hideIcon = "app/hideIcon";
const char* Context::doubleClickedHideIcon = "app/doubleClickedHideIcon";
const char* Context::autoLaunch = "app/autoLaunch";
const char* Context::wallpaperType = "app/wallpaperType";

const char* Context::graphWallpaperPath = "graph/wallpaperPath";
const char* Context::videoWallpaperPath = "video/wallpaperPath";
const char* Context::gifWallpaperPath = "gif/wallpaperPath";


Context::Context()
{

}

bool Context::isStartWallpaper()
{
    return settings->value(startWallpaper).toBool();
}

void Context::setStartWallpaper(bool value)
{
    settings->setValue(startWallpaper,value);

}

bool Context::isHideIcon()
{
    return settings->value(hideIcon).toBool();
}

void Context::setHideIcon(bool value)
{
    settings->setValue(hideIcon,value);
}

bool Context::isAutoLaunch()
{
    return settings->value(autoLaunch).toBool();
}

void Context::setAutoLaunch(bool value)
{
    settings->setValue(autoLaunch,value);
}

bool Context::isDoubleClickedHideIcon()
{
    return settings->value(doubleClickedHideIcon).toBool();
}

void Context::setDoubleClickedHideIcon(bool value)
{
    settings->setValue(doubleClickedHideIcon,value);
}

QString Context::getWallpaperPath()
{
    enum wallpaperType type = (enum wallpaperType) getWallpaperType();
    if(type == graph)
        return settings->value(graphWallpaperPath).toString();

}

void Context::setWallpaperPath(const QString &value)
{
    settings->setValue(videoWallpaperPath,value);
}

int Context::getWallpaperType()
{
    return settings->value(wallpaperType).toInt();
}

void Context::setWallpaperType(enum wallpaperType &&value)
{
    settings->setValue(wallpaperType,value);
}
