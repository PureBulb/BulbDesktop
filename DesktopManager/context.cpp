#include "context.h"
QSettings* Context::settings = new QSettings("./setting.ini",QSettings::IniFormat);
Context* Context::instance = nullptr;
QStringList Context::wallpaperTypeName = {"图片 ","gif ","视频 ","用户自定义 " };
const char* Context::startWallpaper         = "app/startWallpaper";
const char* Context::hideIcon               = "app/hideIcon";
const char* Context::doubleClickedHideIcon  = "app/doubleClickedHideIcon";
const char* Context::autoLaunch             = "app/autoLaunch";
const char* Context::wallpaperType          = "app/wallpaperType";

const char* Context::graphWallpaperPath     = "graph/wallpaperPath";
const char* Context::graphShowDelay         = "graph/graphShowDelay";


const char* Context::videoWallpaperPath     = "video/wallpaperPath";


const char* Context::gifWallpaperPath       = "gif/wallpaperPath";


Context::Context()
{

}

void Context::addWallpaperPath(QString pathType, const QList<QString> value)
{
    if(instance){
        QList<QVariant> paths = settings->value(pathType).toList();
        for(auto item: value){
            paths.push_back(item);
        }
        settings->setValue(pathType,paths);
        emit instance->settingsChanged();
    }
    else{
        loge("context","setxx:didn't have instance\n");
    }
}

void Context::setWallpaperPath(QString pathType, const QList<QString> value)
{
    if(instance){
        QList<QVariant> data;
        for(auto item: value){
            data.append(item);
        }
        settings->setValue(pathType,data);
        emit instance->settingsChanged();
    }
    else{
        loge("context","setxx:didn't have instance\n");
    }
}

Context *Context::getInstance()
{
    if(instance == nullptr)
        instance = new Context;
    return instance;
}

bool Context::isStartWallpaper()
{

    return settings->value(startWallpaper).toBool();
}

void Context::setStartWallpaper(bool value)
{
    if(instance){
        settings->setValue(startWallpaper,value);
        emit instance->settingsChanged();
    }
    else{
        loge("context","setxx:didn't have instance\n");
    }


}

bool Context::isHideIcon()
{
    return settings->value(hideIcon).toBool();
}

void Context::setHideIcon(bool value)
{
    if(instance){
        settings->setValue(hideIcon,value);
        emit instance->settingsChanged();
    }
    else{
        loge("context","setxx:didn't have instance\n");
    }
}

bool Context::isAutoLaunch()
{
    return settings->value(autoLaunch).toBool();
}

void Context::setAutoLaunch(bool value)
{
    if(instance){
        settings->setValue(autoLaunch,value);
        emit instance->settingsChanged();
    }
    else{
        loge("context","setxx:didn't have instance\n");
    }
}

bool Context::isDoubleClickedHideIcon()
{
    return settings->value(doubleClickedHideIcon).toBool();
}

void Context::setDoubleClickedHideIcon(bool value)
{
    if(instance){
        settings->setValue(doubleClickedHideIcon,value);
        emit instance->settingsChanged();
    }
    else{
        loge("context","setxx:didn't have instance\n");
    }
}

QList<QString> Context::getWallpaperPaths()
{
    enum wallpaperType type = (enum wallpaperType) getWallpaperType();
    QList<QString> result;
    if(type == graph)
        return settings->value(graphWallpaperPath).toStringList();
    if (type ==gif)
        return settings->value(gifWallpaperPath).toStringList();
    if(type == video)
        return settings->value(videoWallpaperPath).toStringList();
    //
    return {};
}

QList<QString> Context::getVideoWallpaperPaths()
{
    return settings->value(videoWallpaperPath).toStringList();
}

QList<QString> Context::getGraphWallpaperPaths()
{
    return settings->value(graphWallpaperPath).toStringList();
}

QList<QString> Context::getGifWallpaperPaths()
{
    return settings->value(gifWallpaperPath).toStringList();
}

void Context::addVideoWallpaperPath(const QList<QString> value)
{
    addWallpaperPath(videoWallpaperPath,value);
}

void Context::addGraphWallpaperPath(const QList<QString> value)
{
    addWallpaperPath(graphWallpaperPath,value);
}

void Context::addGifWallpaperPath(const QList<QString> value)
{
    addWallpaperPath(gifWallpaperPath,value);
}

void Context::deleteVideoWallpaperPath(const QString &value)
{
    QStringList paths = getVideoWallpaperPaths();
    if(paths.size() <=1){
        QMessageBox::information(nullptr,"至少要有一个视频 ","至少要有一个视频 ");
        return ;
    }
    if(paths.contains(value)){
        paths.removeOne(value);
    }
    setWallpaperPath(videoWallpaperPath,paths);
}

void Context::deleteGraphWallpaperPath(const QString &value)
{
    QStringList paths = getGraphWallpaperPaths();
    if(paths.contains(value)){
        paths.removeOne(value);
    }
    setWallpaperPath(graphWallpaperPath,paths);
}

void Context::deleteGifWallpaperPath(const QString &value)
{
    QStringList paths = getGifWallpaperPaths();
    if(paths.contains(value)){
        paths.removeOne(value);
    }
    setWallpaperPath(gifWallpaperPath,paths);
}

int Context::getWallpaperType()
{
    return settings->value(wallpaperType).toInt();
}

void Context::setWallpaperType(enum wallpaperType &&value)
{
    if(instance){
        settings->setValue(wallpaperType,value);
        emit instance->settingsChanged();
    }
    else{
        loge("context","setxx:didn't have instance\n");
    }
}

void Context::setGraphShowDelay(int value)
{
    if(instance){
        settings->setValue(graphShowDelay,value);
        emit instance->settingsChanged();
    }
    else{
        loge("context","setxx:didn't have instance\n");
    }
}

int Context::getGraphShowDelay()
{

    return settings->value(graphShowDelay).toInt();
}

QStringList Context::getWallpaperTypeName()
{
    return wallpaperTypeName;
}
