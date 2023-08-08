# 介绍
### 功能

1. 助手功能，该功能可以使用Bulb Desktop Manager自带的基础插件（文件搜索、程序搜索插件）
2. 动态壁纸功能，Bulb Desktop Manager 自带的基础动态壁纸功能，基础动态壁纸包括（视频、Gif、图片）自动播放和切换功能
3. 自定义插件功能，Bulb Desktop Manager 在项目的DesktopManager/plugins 目录中提供了IAssistantPlugin接口（助手插件接口）以及IWallpaperPlugin 接口（壁纸插件接口），用户可以通过自己实现接口以及编译插件后将插件文件复制粘贴到安装目录中对应的插件目录。
### 添加插件方法
    这里可以借鉴原生壁纸插件BaseWallPaperPlugin 的加载方法
    1. 首先介绍下BaseWallPaperPlugin 该插件的主体是BaseWallPaperPlugin.dll并且他还由很多依赖文件
    2. 现在你需要新建一个文件夹，该文件夹名称与插件主体名称相同
    3. 将插件以及插件文件复制粘贴到你新建的文件夹
    4. 将新建的文件夹复制粘贴到安装目录的WallpapePlugins目录中
    5. 程序每次启动的时候都会自动加载插件目录中的dll
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


class IWallpaperPlugin:public QObject
{
    Q_OBJECT
protected:
    QWidget* wallpaper;

public:
    IWallpaperPlugin(){}
    // 生命周期函数，当被加载后会被调用
    virtual void loaded() {}
    // 生命周期函数，当被卸载后会被调用
    virtual void unloaded() {}
    // 生命周期函数，当被激活后会被调用
    virtual void activated() {}
    // 预留
    virtual void finished() {}
    virtual void setSettings(QHash<QString,QVariant> settings) {}
    // 返回壁纸给插件加载器使用，几个屏幕就返回几张
    virtual QVector<QWidget *> getWallpapers() {}
    // 返回设置窗口加载器使用
    virtual QWidget* getSettingWidget() {}
    //value 0-100
    virtual void setVolume(uint8_t value) {}
    virtual void pause() {}
    virtual void resume() {}
    virtual void display() {}
    virtual void stop(){};

signals:
    void displayFinished();
    void settingsChanged(QHash<QString,QVariant> settings);
    void requestSettings();
    // 插件已经利用钩子监听双击事件，该消息用于隐藏桌面图标
    void triggedIcons();
protected slots:
    // 分发信号（起名没有起好）
    void onTriggedIcons(){emit triggedIcons();};
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

```

### 编译Bulb Desktop Manager
1. 构建整个父项目
2. 按照最开头介绍添加插件的方法添加插件，此处展示EverythingPlugin插件：
-  进入编译目录 ```AssistantPlugins\EverythingPlugin\release```
- 复制EverythingPlugin.dll到 ```DesktopManager\release\AssistantPlugins\EverythingPlugin``` 粘贴（目录自己创建）
- 复制项目中的依赖，进入项目目录```everythin/dll/``` 复制Everything64.dll进入编译目录```DesktopManager\release\AssistantPlugins\EverythingPlugin``` 粘贴
- 利用Qt的打包工具cd进目录 ```DesktopManager\release\AssistantPlugins\EverythingPlugin``` 输入windeployqt 插件名称.dll
- 这样你就完成了一个插件的部署，其他类同
3. 编译目录创建 ```DesktopManager\release\thumbnail```
4. 创建```DesktopManager\release\setting.ini``` 并复制以下内容
```ini
[BaseWallpaper]
video.paths=至少要有一个有效的视频文件路径
graph.paths=D:/test.png
#2是video模式
type=2 
graph.delay=20
gif.paths=@Invalid()

```
5. 复制项目中的依赖，进入项目目录```MinHookDllDemo/MinHookDllDemo.dll``` 复制粘贴到编译目录```DesktopManager\release\```中
