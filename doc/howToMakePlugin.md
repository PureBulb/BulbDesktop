### 插件接口说明

1. IAssistantPlugin.h
```C++
#ifndef IASSISTANTPLUGIN_H
#define IASSISTANTPLUGIN_H

#include <QIcon>
#include <QObject>
#include <QString>
#include <QList>
#include <QPluginMetaData>
// 结果类型
enum ResultType{file,folder,program};
// 查询结果
struct QueryResult{
public:
    // 返回结果标题，该值将会返回到助手界面的item中的标题位置
    QString getTitle() {return  title;};
    // 设置返回结果标题
    void setTitle(const QString &value){ title = value;};
    // 返回结果详情，该值将会返回到助手界面的item中的详情位置
    QString getDescription() {return description;};
    // 设置返回结果详情
    void setDescription(const QString &value){description = value;};
    //返回类型
    ResultType getType() {return type;};
    //设置返回类型
    void setType(const ResultType &value){type = value;};
    // item被点击事件回调函数（无需过度关注，无需实现该方法，下同）
    std::function<void ()> getItemClick() {return itemClick;};
    // 设置item被点击事件回调函数（无需过度关注，无需实现该方法，下同）
    void setItemClick(const std::function<void (QueryResult)> value){
        itemClick = std::bind(value,*this);
    };
    //item 第一个按钮的点击事件
    std::function<void ()> getBtn1Click() {return btn1Click;};
    void setBtn1Click(const std::function<void (QueryResult)> value){
        btn1Click = std::bind(value,*this);
    };
    //item 第二个按钮的点击事件
    std::function<void ()> getBtn2Click() {return btn2Click;};
    void setBtn2Click(const std::function<void (QueryResult)> value){
        btn2Click = std::bind(value,*this);
    };


    //Icon生成方法（无需过度关注）
    std::function<QIcon ()> getIconFunc() {return iconFunc;};
    void setIconFunc(const std::function<QIcon(QueryResult)> &value){
        iconFunc = std::bind(value,*this);
    };

private:

    QString title;
    QString description;
    ResultType type;
    std::function<void()> itemClick;    //when you are setting it please use IAssistantPlugin::returnItemClickFunc to get the callback function（自己翻一下吧，写的时候有时候喜欢谢英文注释）
    std::function<void()> btn1Click;    //when you are setting it please use IAssistantPlugin::returnBtn1ClickFunc to get the callback function
    std::function<void()> btn2Click;    //when you are setting it please use IAssistantPlugin::returnBtn2ClickFunc to get the callback function
    std::function<QIcon()> iconFunc;    //when you are setting it please use IAssistantPlugin::returnBtn2ClickFunc to get the callback function
};

class IAssistantPlugin {
    friend struct QueryResult;
protected:
    uint8_t pluginProperty; // 0-50 is the highest level, only system plugin can be
    //需要自己实现的回调函数，item被点击事件
    virtual void onItemClick(QueryResult){};
    //需要自己实现的回调函数，item第一个按钮被点击事件
    virtual void onBtn1Click(QueryResult){};
    //需要自己实现的回调函数，item 第二个按钮被点击事件
    virtual void onBtn2Click(QueryResult){};
    //需要自己实现的回调函数，item icon生成函数
    virtual QIcon getIconFunc(QueryResult){ return QIcon();};
    //以下方法无需自己实现
    virtual std::function<void (QueryResult)> getOnItemClickFunc(){
        return std::bind(&IAssistantPlugin::onItemClick,this,std::placeholders::_1);
    };
    virtual std::function<void (QueryResult)> getOnBtn1ClickFunc(){
        return std::bind(&IAssistantPlugin::onBtn1Click,this,std::placeholders::_1);
    };
    virtual std::function<void (QueryResult)> getOnBtn2ClickFunc(){
        return std::bind(&IAssistantPlugin::onBtn2Click,this,std::placeholders::_1);
    };
    virtual std::function< QIcon(QueryResult)> getGetIconFunc(){
        return std::bind(&IAssistantPlugin::getIconFunc,this,std::placeholders::_1);
    };
public:
    //生命周期函数，当被加载进程序时调用
    virtual void loaded() = 0;
    //生命周期函数，当被进程序卸载时调用
    virtual void unload() = 0;
    /*
    * 参数：
    *  queryStr:查询字符串
    *  result：结果集合
    * 返回：
    *  true: 本插件数据+其他插件数据
    *  false： 优先级低（数字大）的插件将不再进行
    */
    virtual bool query(QString queryStr,QList<QueryResult>& result) = 0;
    virtual uint8_t getPluginProperty(){return this->pluginProperty;};
    virtual ~IAssistantPlugin(){}

    //TODO: context setting manager link
};

/*
* json mate demo
{
    "plugin-name" : "xxx",
    "dependencies" : [ ],
    "type" : "assistant"
}
*/

QT_BEGIN_NAMESPACE
#define PLUGIN_IID "org.qt-project.Qt.IAssistantPlugin"
Q_DECLARE_INTERFACE(IAssistantPlugin,PLUGIN_IID);
QT_END_NAMESPACE
#endif // IASSISTANTPLUGIN_H


```

2. IWallpaperPlugin
```C++
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
    //生命周期函数，当被加载进程序时调用
    virtual void loaded() {}
    //生命周期函数，当被卸载时调用
    virtual void unloaded() {}
    //生命周期函数，当被管理器激活时时调用
    virtual void activated() {}
    //生命周期函数，当被生命周期结束时时调用
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
    void requestSettings(QHash<QString,QVariant> settings);
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
