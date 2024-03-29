#ifndef IWALLPAPERPLUGIN_H
#define IWALLPAPERPLUGIN_H

#include <QWidget>
#include <QPluginMetaData>
#include <QHash>
#include <QVariant>


class IWallpaperPlugin:public QObject
{
    Q_OBJECT
protected:
    QWidget* wallpaper;

public:
    IWallpaperPlugin(){}
    virtual void loaded() {}
    virtual void unloaded() {}
    virtual void activated() {}
    virtual void finished() {}

    virtual void setSettings(QHash<QString,QVariant> settings){}

    virtual QVector<QWidget *> getWallpapers() {}
    virtual QWidget* getSettingWidget() {}

    //value 0-100
    virtual void setVolume(uint8_t value) {}
    virtual void pause() {}
    virtual void resume() {}
    virtual void display() {}
    virtual void stop(){};

signals:
    void displayFinished();
    // void settingsChanged(QHash<QString,QVariant> settings);
    void requestSettings(QHash<QString,QVariant> settings);
    void triggedIcons();
protected slots:
    void onTriggedIcons(){emit triggedIcons();}
public slots:
    virtual void updatePluginSettings(QHash<QString,QVariant> _settings){};
    void responseSettings(QHash<QString,QVariant> settings){emit settingChangeSucceeded(settings);}
signals:
    void settingChangeSucceeded(QHash<QString, QVariant> _settings);

};
/*
 * json meta demo
{
    "plugin-name" : "xxx",
    "dependencies" : [ ],
    "type" : "wallpaper"
}
*/

QT_BEGIN_NAMESPACE
#define PLUGIN_IID "org.qt-project.Qt.IWallpaperPlugin"
Q_DECLARE_INTERFACE(IWallpaperPlugin,PLUGIN_IID);
QT_END_NAMESPACE

#endif // IWALLPAPERPLUGIN_H
