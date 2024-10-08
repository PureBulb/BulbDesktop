#include "basewallpapermanager.h"
#include <QtDebug>
#include <QApplication>
#include "BaseWallpaperManager.h"
QVector<Wallpaper *> BaseWallpaperManager::getWallpapers() const
{
    return wallpapers;
}

void BaseWallpaperManager::getWallpapersFormScreen()
{
    int x = 0;
    int y = 0;
    int w,h;
    for(auto screen: QGuiApplication::screens()){
        int screenX,screenY;
        Wallpaper* wallpaper = new Wallpaper;
        wallpaper->show();
        wallpaper->setGeometry(screen->geometry());
        screen->geometry().getRect(&screenX,&screenY,&w,&h);
        wallpaper->move(x,y);
        x+=w;
        wallpapers.append(wallpaper);

    }
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
        for(auto wallpaper :qAsConst(wallpapers)){
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
        for(auto wallpaper : qAsConst(wallpapers))
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

    if(wallpaperPaths.size()>0){
        if(!video){
            video = new VideoUtils(wallpaperPaths.front());
            connect(video,&VideoUtils::displayFinished,this,&BaseWallpaperManager::setVideoBackground);
            for(auto wallpaper:qAsConst(wallpapers)){
                connect(video,&VideoUtils::sendDecodeImg,wallpaper,&Wallpaper::onDecodeImage);
                wallpaper->cleanGraph();
            }
            wallpaperPaths.pop_front();
            video->play();
            logInstance->logi("BaseWallpaperManager::setVideoBackground","video started");
        }
        else{
            video->stop();
            video->deleteLater();
            video = nullptr;
            // logInstance->logi("BaseWallpaperManager::setVideoBackground","video stopped");
            setVideoBackground();
        }
    }
    else{
        wallpaperPaths = getWallpaperPaths();
        setVideoBackground();
    }

    // logInstance->logi("BaseWallpaperManager::setVideoBackground","video out");
}

void BaseWallpaperManager::setSettings(QHash<QString, QVariant> _settings)
{
    qDebug()<<_settings;    //没有我会被优化掉，无语死了
    settings = _settings;

    bool flag;
    graphShowDelay = settings[INI_GRAPH_DELAY].toInt(&flag);
    if(!flag){
        logInstance->logd("BaseWallpaperManager::setSetting","graphShowDelay is null");
    }
    //TODO: re-init?
    // restart();


}

void BaseWallpaperManager::display()
{
    if(wallpapers.size()==0){
        getWallpapersFormScreen();
    }
    for(auto wallpaper :qAsConst(wallpapers)){
        wallpaper->show();
    }
    restart();

}

void BaseWallpaperManager::hide()
{
    pause();
    for(auto wallpaper :qAsConst(wallpapers)){
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
    for(auto wallpaper:qAsConst(wallpapers))
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

void BaseWallpaperManager::updateSettings(QHash<QString, QVariant> _settings)
{
    setSettings(_settings);
    wallpaperPaths = getWallpaperPaths(); //刷新壁纸，以防切换的时候保留上一次类型的壁纸路径
    restart();

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

    logInstance = LogDispacher::getInstance();
    getWallpapersFormScreen();
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
    if(gif){
        gif->deleteLater();
    }
    if(graphShowTimer){
        graphShowTimer->deleteLater();
    }
    if(video){
        video->stop();
        video->deleteLater();
    }
    gif = nullptr;
    graphShowTimer = nullptr;
    video = nullptr;
    nextWallpaper();
}
