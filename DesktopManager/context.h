#ifndef CONTEXT_H
#define CONTEXT_H

#include <QSettings>
#include <QString>
class Context
{

private:
    static QSettings *settings;
    static const char* startWallpaper;
    static const char* hideIcon;
    static const char* autoLaunch;
    static const char* wallpaperPath;
    static const char* wallpaperType;

public:
    enum wallpaperType{graph,gif,video};
    Context();



    static bool isStartWallpaper();
    static void setStartWallpaper(bool value);

    static bool isHideIcon();
    static void setHideIcon(bool value);

    static bool isAutoLaunch();
    static void setAutoLaunch(bool value);

    static QString getWallpaperPath();
    static void setWallpaperPath(const QString &value);


    static int getWallpaperType();
    static void setWallpaperType(enum wallpaperType &&value);




};

#endif // CONTEXT_H
