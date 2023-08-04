#include "widgets/mainwindow.h"

#include <QApplication>
#include <utils/pluginUtils/wallpaperpluginutils.h>
#include <Manager.h>

int main(int argc, char *argv[])
{



    QApplication a(argc, argv);
    Manager manager;
//    MainWindow w;
//    w.show();

//    WallpaperPluginUtils utils;
//    utils.load();
//    QHash<QString, QVariant> settings;
//    SettingManager manager;
//    QStringList paths;
//    paths<<"D:/test2.mp4"<<"D:/test3.mp4";
//    settings["video.paths"] = paths;
//    settings["type"] = 2;
//    utils.setSettings(&manager);

    //utils.nextWallpaper();


    return a.exec();
}
