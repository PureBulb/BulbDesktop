#ifndef CONTEXT_H
#define CONTEXT_H

#include <QObject>
#include <QMessageBox>
#include <QSettings>
#include <QString>
#include <QList>
#include "log.h"
class Context:public QObject
{
    Q_OBJECT
signals:
    void settingsChanged();
private:
    static Context* instance;
    static QSettings *settings;
    static const char* startWallpaper;
    static const char* hideIcon;
    static const char* autoLaunch;
    static const char* graphWallpaperPath;
    static const char* videoWallpaperPath;
    static const char* gifWallpaperPath;
    static const char* wallpaperType;
    static const char* doubleClickedHideIcon;

    static const char* graphShowDelay;

    static QStringList wallpaperTypeName;
    Context();

    static void addWallpaperPath(QString pathType, const QList<QString> value);
    static void setWallpaperPath(QString pathType, const QList<QString> value);
public:
    enum wallpaperType{graph,gif,video};
    typedef enum wallpaperType WallPaperType;
    static Context* getInstance();


    //启动后自动运行壁纸
    static bool isStartWallpaper();
    static void setStartWallpaper(bool value);

    static bool isHideIcon();
    static void setHideIcon(bool value);

    //开机自启
    static bool isAutoLaunch();
    static void setAutoLaunch(bool value);

    static bool isDoubleClickedHideIcon();
    static void setDoubleClickedHideIcon(bool value);
     //只获取目前模式的wallpaperPath
    static QList<QString> getWallpaperPaths();
    static QList<QString> getVideoWallpaperPaths();
    static QList<QString> getGraphWallpaperPaths();
    static QList<QString> getGifWallpaperPaths();


    static void addVideoWallpaperPath(const QList<QString> value);
    static void addGraphWallpaperPath(const QList<QString> value);
    static void addGifWallpaperPath(const QList<QString> value);

    static void deleteVideoWallpaperPath(const QString &value);
    static void deleteGraphWallpaperPath(const QString &value);
    static void deleteGifWallpaperPath(const QString &value);


    static int getWallpaperType();
    static void setWallpaperType(enum wallpaperType &&value);

    static void setGraphShowDelay(int value);
    static int getGraphShowDelay();

    static QStringList getWallpaperTypeName();

};

#endif // CONTEXT_H
