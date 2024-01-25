@echo OFF
set outputDir=%1
set sourceDir=%2
set build_type=%3
set build_everythingPluginDir__debug=%outputDir%\AssistantPlugins\EverythingPlugin
set build_programPluginDir__debug=%outputDir%\AssistantPlugins\ProgramsPlugin
set build_wallpaperPluginDir__debug=%outputDir%\WallpaperPlugins\BaseWallPaperPlugin

set out_everythingPluginDir__debug=%outputDir%\DesktopManager\AssistantPlugins\EverythingPlugin
set out_programPluginDir__debug=%outputDir%\DesktopManager\AssistantPlugins\ProgramsPlugin
set out_wallpaperPluginDir__debug=%outputDir%\DesktopManager\WallpaperPlugins\BaseWallPaperPlugin
set out_thumbnailDir__debug=%outputDir%\thumbnail
echo %build_type%

if %build_type%=="release" ( 

set out_everythingPluginDir__release=%outputDir%\DesktopManager\release\AssistantPlugins\EverythingPlugin
set out_programPluginDir__release=%outputDir%\DesktopManager\release\AssistantPlugins\ProgramsPlugin
set out_wallpaperPluginDir__release=%outputDir%\DesktopManager\release\WallpaperPlugins\BaseWallPaperPlugin
set out_thumbnailPluginDir__release=%outputDir%\DesktopManager\release\thumbnail

mkdir "%out_everythingPluginDir__debug%"
mkdir "%out_programPluginDir__debug%"
mkdir "%out_wallpaperPluginDir__debug%"
mkdir "%out_thumbnailDir__debug%"

copy "%build_everythingPluginDir__debug%\release\EverythingPlugin.dll" "%out_everythingPluginDir__debug%"
copy "%sourceDir%\everything\dll\*.dll" "%out_everythingPluginDir__debug%\"

copy "%build_programPluginDir__debug%\release\ProgramsPlugin.dll" "%out_programPluginDir__debug%"

copy "%build_wallpaperPluginDir__debug%\release\BaseWallPaperPlugin.dll" "%out_wallpaperPluginDir__debug%"
copy "%sourceDir%\ffmpeg\bin\*" "%out_wallpaperPluginDir__debug%"

copy "%sourceDir%\MinHookDllDemo\MinHookDllDemo.dll" "%outputDir%\DesktopManager\MinHookDllDemo.dll"

copy "%out_everythingPluginDir__debug%" "%out_everythingPluginDir__release%"
copy "%out_programPluginDir__debug%" "%out_programPluginDir__release%"
copy "%out_wallpaperPluginDir__debug%" "%out_wallpaperPluginDir__release%"

copy "%outputDir%\DesktopManager\MinHookDllDemo.dll" "%outputDir%\DesktopManager\release\"
if not exist "%outputDir%\DesktopManager\release\setting.ini" (
    copy "%sourceDir%\setting.ini" "%outputDir%\DesktopManager\release\"

)
if not exist "%outputDir%\DesktopManager\setting.ini" (
    copy "%sourceDir%\setting.ini" "%outputDir%\DesktopManager\"
)



)

if %build_type% equ "profile" (

set out_everythingPluginDir__release=%outputDir%\DesktopManager\release\AssistantPlugins\EverythingPlugin
set out_programPluginDir__release=%outputDir%\DesktopManager\release\AssistantPlugins\ProgramsPlugin
set out_wallpaperPluginDir__release=%outputDir%\DesktopManager\release\WallpaperPlugins\BaseWallPaperPlugin
set out_thumbnailPluginDir__release=%outputDir%\DesktopManager\release\thumbnail

mkdir "%out_everythingPluginDir__debug%"
mkdir "%out_programPluginDir__debug%"
mkdir "%out_wallpaperPluginDir__debug%"
mkdir "%out_thumbnailDir__debug%"

copy "%build_everythingPluginDir__debug%\release\EverythingPlugin.dll" "%out_everythingPluginDir__debug%\EverythingPlugin.dll"
copy "%sourceDir%\everything\dll\*.dll" "%out_everythingPluginDir__debug%\"

copy "%build_programPluginDir__debug%\release\ProgramsPlugin.dll" "%out_programPluginDir__debug%\ProgramsPlugin.dll"

copy "%build_wallpaperPluginDir__debug%\release\BaseWallPaperPlugin.dll" "%out_wallpaperPluginDir__debug%\BaseWallPaperPlugin.dll"
copy "%sourceDir%\ffmpeg\bin\*" "%out_wallpaperPluginDir__debug%\"

copy "%sourceDir%\MinHookDllDemo\MinHookDllDemo.dll" "%outputDir%\DesktopManager\MinHookDllDemo.dll"

copy "%out_everythingPluginDir__debug%" "%out_everythingPluginDir__release%"
copy "%out_programPluginDir__debug%" "%out_programPluginDir__release%"
copy "%out_wallpaperPluginDir__debug%" "%out_wallpaperPluginDir__release%"

copy "%outputDir%\DesktopManager\MinHookDllDemo.dll" "%outputDir%\DesktopManager\release\MinHookDllDemo.dll"
if not exist  "%outputDir%\DesktopManager\release\setting.ini"  (
    copy "%sourceDir%\setting.ini" "%outputDir%\DesktopManager\release\"

)
if not exist "%outputDir%\DesktopManager\setting.ini" (
    copy "%sourceDir%\setting.ini" "%outputDir%\DesktopManager\"
)
)