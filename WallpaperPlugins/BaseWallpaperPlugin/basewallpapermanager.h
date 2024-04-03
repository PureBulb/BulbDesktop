#ifndef BASEWALLPAPERMANAGER_H
#define BASEWALLPAPERMANAGER_H

#include <QVector>
#include <QGuiApplication>
#include <QScreen>
#include <QPixmap>

#include "common.h"
#include "utils/logdispacher.h"
#include "wallpaper.h"
#include "utils/videoUtils/videoutils.h"
class BaseWallpaperManager:public QObject
{
    Q_OBJECT
private:

    QHash<QString,QVariant> settings;
    uint64_t graphShowDelay;
    LogDispacher* logInstance;
    QVector<Wallpaper*> wallpapers;
    QStringList wallpaperPaths;

    QTimer* graphShowTimer;
    QMovie *gif;
    VideoUtils * video;

    QStringList getWallpaperPaths();
    void getWallpapersFormScreen();
public:
    BaseWallpaperManager();
    ~BaseWallpaperManager();
    void restart();
    // if you have multiple screens this fuction will return multiple widgets
    QVector<Wallpaper*> getWallpapers() const;

    void setSettings(QHash<QString,QVariant> _settings);
    void initWallpaper();

    void display();
    void hide();
public slots:
    void nextWallpaper();

    void setGifBackground();

    void setGraphBackground();

    void setVideoBackground();

    void pause();

    void resume();

    void stop();

    void volumeChanged(uint8_t value);

    void updateSettings(QHash<QString,QVariant> _settings);




};

#endif // BASEWALLPAPERMANAGER_H
