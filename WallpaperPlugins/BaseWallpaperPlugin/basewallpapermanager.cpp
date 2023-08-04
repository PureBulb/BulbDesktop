#include "basewallpapermanager.h"
#include <QtDebug>
#include "log.h"
QVector<Wallpaper *> BaseWallpaperManager::getWallpapers() const
{
    return wallpapers;
}

void BaseWallpaperManager::nextWallpaper()
{
    WallpaperType type = (WallpaperType)settings["type"].toInt();
    if( type == WallpaperType::gif){
        setGifBackground();
    }
    else if(type == WallpaperType::graph){
        setGraphBackground();
    }
    else if(type == WallpaperType::video){
        setVideoBackground();
    }
}

void BaseWallpaperManager::setGifBackground()
{

    if(!gif){
        gif = new QMovie;
        connect(gif,&QMovie::finished,this,&BaseWallpaperManager::setGifBackground);
    }
    else{
        gif->stop();
    }
    if(wallpaperPaths.size()>0){
        gif->setFileName(wallpaperPaths.front());
        gif->setScaledSize(wallpapers[0]->size());
        for(auto wallpaper :wallpapers){
            wallpaper->setGif(gif);
        }
        gif->start();
        wallpaperPaths.pop_front();
    }
    else{
        gif->stop();
        wallpaperPaths = getWallpaperPaths();
        setGifBackground();
    }
}

void BaseWallpaperManager::setGraphBackground()
{
    if(!graphShowTimer){
        graphShowTimer = new QTimer;
        graphShowTimer->setInterval(graphShowDelay*60*1000);
        connect(graphShowTimer,&QTimer::timeout,this,&BaseWallpaperManager::setGraphBackground);
    }
    if(wallpaperPaths.size()>0){
        for(auto wallpaper : wallpapers)
            wallpaper->setGraph(QPixmap(wallpaperPaths.front()));
        wallpaperPaths.pop_front();
        graphShowTimer->start();
    }
    else{
        wallpaperPaths = getWallpaperPaths();
        setGraphBackground();
    }

}

void BaseWallpaperManager::setVideoBackground()
{
    logi("BaseWallpaperManager::setVideoBackground","video entry");
    if(wallpaperPaths.size()>0){
        if(!video){
            video = new VideoUtils(wallpaperPaths.front());
            connect(video,&VideoUtils::displayFinished,this,&BaseWallpaperManager::setVideoBackground);
            for(auto wallpaper:wallpapers)
                connect(video,&VideoUtils::sendDecodeImg,wallpaper,&Wallpaper::onDecodeImage);
            wallpaperPaths.pop_front();
            logi("BaseWallpaperManager::setVideoBackground","play entry");
            video->play();
            logi("BaseWallpaperManager::setVideoBackground","play out");
        }
        else{
            logi("BaseWallpaperManager::setVideoBackground","video stop");
            video->stop();
            video->deleteLater();
            video = nullptr;
            logi("BaseWallpaperManager::setVideoBackground","video stopped");
            setVideoBackground();
        }
    }
    else{
        wallpaperPaths = getWallpaperPaths();
        setVideoBackground();
    }

    logi("BaseWallpaperManager::setVideoBackground","video out");
}

void BaseWallpaperManager::setSettings(QHash<QString, QVariant> _settings)
{
    settings = _settings;

    graphShowDelay = settings["graph.graphShowDelay"].toUInt();

    //TODO: re-init?


}

void BaseWallpaperManager::display()
{
    for(auto wallpaper :wallpapers){
        wallpaper->show();
    }
    restart();

}

void BaseWallpaperManager::hide()
{
    pause();
    for(auto wallpaper :wallpapers){
        wallpaper->hide();
    }
}



void BaseWallpaperManager::pause()
{
    if(video){
        video->pause();
    }
    else if(gif){
        gif->setPaused(true);
    }
    else if(graphShowTimer){
        graphShowTimer->stop();
    }
}

void BaseWallpaperManager::resume()
{
    if(video){
        video->resume();
    }
    if(gif){
        gif->setPaused(false);
    }
    else if(graphShowTimer){
        graphShowTimer->start();
    }
}

void BaseWallpaperManager::stop()
{
    for(auto wallpaper:wallpapers)
        wallpaper->deleteLater();
    wallpapers.clear();
    if(gif)
        gif->deleteLater();
    if(graphShowTimer)
        graphShowTimer->deleteLater();
    if(video)
        video->deleteLater();
    gif = nullptr;
    graphShowTimer = nullptr;
    video = nullptr;
}

void BaseWallpaperManager::volumeChanged(uint8_t value)
{
    if(video){
        video->setVolume(value);
    }
}



QStringList BaseWallpaperManager::getWallpaperPaths()
{
    if(settings[INI_TYPE].toInt() == WallpaperType::gif)
        return settings[INI_GIF_PATHS].toStringList();
    if(settings[INI_TYPE].toInt() == WallpaperType::graph)
        return settings[INI_GRAPH_PATHS].toStringList();
    if(settings[INI_TYPE].toInt() == WallpaperType::video)
        return settings[INI_VIDEO_PATHS].toStringList();
    return QStringList();
}

BaseWallpaperManager::BaseWallpaperManager()
{

    for(auto screen: QGuiApplication::screens()){
        Wallpaper* wallpaper = new Wallpaper;
        wallpaper->setGeometry(screen->geometry());
        wallpapers.append(wallpaper);

    }
    gif = nullptr;
    graphShowTimer = nullptr;
    video = nullptr;



}

BaseWallpaperManager::~BaseWallpaperManager()
{
    stop();
}

void BaseWallpaperManager::restart()
{
    if(gif)
        gif->deleteLater();
    if(graphShowTimer)
        graphShowTimer->deleteLater();
    if(video)
        video->deleteLater();
    gif = nullptr;
    graphShowTimer = nullptr;
    video = nullptr;
    nextWallpaper();
}
