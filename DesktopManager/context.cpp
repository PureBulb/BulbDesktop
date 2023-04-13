#include "context.h"
QSettings* Context::settings = new QSettings("./setting.ini",QSettings::IniFormat);
const char* Context::startWallpaper = "app/startWallpaper";
const char* Context::hideIcon = "app/hideIcon";
const char* Context::autoLaunch = "app/autoLaunch";
const char* Context::wallpaperPath = "app/wallpaperPath";
const char* Context::wallpaperType = "app/wallpaperType";

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

QString Context::getWallpaperPath()
{
    return settings->value(wallpaperPath).toString();

}

void Context::setWallpaperPath(const QString &value)
{
    settings->setValue(wallpaperPath,value);
}

int Context::getWallpaperType()
{
    return settings->value(wallpaperType).toInt();
}

void Context::setWallpaperType(enum wallpaperType &&value)
{
    settings->setValue(wallpaperType,value);
}
