# 介绍
### 功能

1. 助手功能，该功能可以使用Bulb Desktop Manager自带的基础插件（文件搜索、程序搜索插件）
2. 动态壁纸功能，Bulb Desktop Manager 自带的基础动态壁纸功能，基础动态壁纸包括（视频、Gif、图片）自动播放和切换功能
3. 自定义插件功能，Bulb Desktop Manager 在项目的DesktopManager/plugins 目录中提供了IAssistantPlugin接口（助手插件接口）以及IWallpaperPlugin 接口（壁纸插件接口），用户可以通过自己实现接口以及编译插件后将插件文件复制粘贴到安装目录中对应的插件目录。
### 添加插件方法
#### 使用别人编译好的
这里可以借鉴原生壁纸插件BaseWallPaperPlugin 的加载方法
1. 首先介绍下BaseWallPaperPlugin 该插件的主体是BaseWallPaperPlugin.dll并且他还由很多依赖文件
2. 现在你需要新建一个文件夹，该文件夹名称与插件主体名称相同
3. 将插件以及插件文件复制粘贴到你新建的文件夹
4. 将新建的文件夹复制粘贴到安装目录的WallpapePlugins目录中
5. 程序每次启动的时候都会自动加载插件目录中的dll
#### 自己编译打包
[自动拷贝依赖](doc/autoBuild.md)
[手动拷贝依赖](doc/manualBuild.md)
### 自定义插件方法
[插件接口文档](doc/howToMakePlugin.md)
