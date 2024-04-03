#ifndef IWALLPAPERPLUGIN_H
#define IWALLPAPERPLUGIN_H

#include <QWidget>
#include <QPluginMetaData>
#include <QHash>
#include <QVariant>

//注意:本接口可能会在不久的未来将setting部分抽离成独立的类用来专门管理设置通信（目前冒泡式有点冗余）
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
    //当插件加载后会调用该函数传入属于本类的设置
    virtual void setSettings(QHash<QString,QVariant> settings){}
    //返回壁纸窗口，vector是为了支持多屏
    virtual QVector<QWidget *> getWallpapers() {}
    //返回设置窗口
    virtual QWidget* getSettingWidget() {}

    //value 0-100
    virtual void setVolume(uint8_t value) {}
    virtual void pause() {}
    virtual void resume() {}
    virtual void display() {}
    virtual void stop(){};

signals:
    //插件播放结束
    void displayFinished();
    // void settingsChanged(QHash<QString,QVariant> settings);
    //发送插件配置修改请求，处理成功后由responseSettings槽接受
    void requestUpdateSettings(QHash<QString,QVariant> settings);

    //隐藏桌面图标切换信号，由插件管理器接受
    void triggedIcons();
protected slots:
    //接受来自wallpaper的图标切换事件，并触发triggedIcons（向上冒泡）
    void onTriggedIcons(){emit triggedIcons();}
public slots:
    virtual void updatePluginSettings(QHash<QString,QVariant> _settings){};
    //接受来自管理类的处理结果转交给settingChangeSucceeded 让他通知该插件所有需要设置的类
    void responseSettings(QHash<QString,QVariant> settings){emit settingChangeSucceeded(settings);}
signals:

    void settingChangeSucceeded(QHash<QString, QVariant> _settings);
    // log 信号，在本例子中信号由LogDispacher发出 该接口继承者接受处理并发送给插件管理类处理
    void reportError(QString module, QString msg);
    void reportInfo(QString module, QString msg);
    void reportWarring(QString module, QString msg);
    void reportDebug(QString module, QString msg);

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

