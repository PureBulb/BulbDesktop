### 手动创建依赖
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
video.paths=resource/videos/test2.mp4
graph.paths=resource/images/test.jpg
#2是video模式
type=2 
graph.delay=20
gif.paths=@Invalid()

```
5. 复制项目中的依赖，进入项目目录```MinHookDllDemo/MinHookDllDemo.dll``` 复制粘贴到编译目录```DesktopManager\release\```中
