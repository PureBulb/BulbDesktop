param($type,$sourceDir)
$buildtype=""
$pwdPath=Get-Location
Write-Output "source dir: $sourceDir"
Write-Output "build dir: $pwdPath"
$exePath="$pwdPath/DesktopManager/$buildtype/"
Add-Type -AssemblyName PresentationFramework
# line 7 line 8 please enter your Qt environment
$path1="E:\environment\qt\5.14.2\mingw73_64\bin"
$path2="E:/environment/qt/Tools/mingw730_64\bin"

$env:path+="$path2;$path2"
if(!(Test-Path -Path $path1) -and !(Test-Path -Path $path2)){
    [System.Windows.MessageBox]::Show('please check Qt evn is right')
    return -1
}
if($type -eq "debug"){
    $buildtype="debug"
}
elseif($type -eq "release"){
    $buildtype="release"
}
elseif($type -eq "profile"){
    $buildtype="release"
}
# define what plugin do you have and what type they are
$AssistantPlugins=@("EverythingPlugin","ProgramsPlugin")
$WallpaperPlugins=@("BaseWallPaperPlugin")
$PendantPlugins=@("MonitorPlugin")
$allTypePlugins=@{AssistantPlugins = $AssistantPlugins;WallpaperPlugins = $WallpaperPlugins;PendantPlugins = $PendantPlugins}

Write-Output "coping plugins..."
foreach ($pluginType in $allTypePlugins.Keys){
    foreach($pluginName in $($allTypePlugins[$pluginType])){
        $dependenceShPath = "$sourceDir/$pluginType/$pluginName/dependence.ps1"
        
        if(Test-Path -Path $dependenceShPath){
            $exePath="$pwdPath/DesktopManager/$buildtype/"
            invoke-expression -Command "$dependenceShPath $buildtype $sourceDir"
        }
        
        $dllPath="$pwdPath/$pluginType/$pluginName/$buildtype/*.dll"
        $exePath="$pwdPath/$pluginType/$pluginName/$buildtype/*.exe"
        $debugPath="$pwdPath/DesktopManager/$pluginType/$pluginName"
        
        if (-Not (Test-Path -Path $debugPath)) {
            New-Item -Path $debugPath -ItemType Directory
        }
        Copy-Item -Path $dllPath  $debugPath -Recurse -Force 
        Copy-Item -Path $exePath  $debugPath -Recurse -Force
        if($buildtype -eq "release"){
            $buildPath="$pwdPath/DesktopManager/$buildtype/$pluginType/$pluginName"
            if (-Not (Test-Path -Path $buildPath)) {
                New-Item -Path $buildPath -ItemType Directory
            }
            Copy-Item -Path $dllPath  $buildPath -Recurse -Force 
            Copy-Item -Path $exePath  $buildPath -Recurse -Force
        }
        Write-Output "finished $pluginName"
    }


}
Write-Output "copy finished "

Write-Output "coping settings..."
if($buildtype -eq "release"){
    $settingsPath="$sourceDir/setting.ini"
    $exePath="$pwdPath/DesktopManager/$buildtype/"
    Copy-Item -Path $settingsPath $exePath -Recurse -Force

}
Write-Output "copy finished "

Write-Output "coping hook..."
#because it use exe Relative paths to inject hook so it just copy to exe path
$hookPath = "$sourceDir/MinHookDllDemo/MinHookDllDemo.dll"
$exePath="$pwdPath/DesktopManager/$buildtype/"
Copy-Item -Path $hookPath  $exePath -Recurse -Force

Write-Output "copy finished "

Write-Output "create some dir"
$thumbnailDir = "$pwdPath/DesktopManager/thumbnail"
if (-Not (Test-Path -Path $thumbnailDir)) {
    New-Item -Path $thumbnailDir -ItemType Directory
}
if($buildtype -eq "release"){
    $thumbnailDir="$pwdPath/DesktopManager/$buildtype/thumbnail"
    New-Item -Path $thumbnailDir -ItemType Directory
}
Write-Output "create finished "
windeployqt $pwdPath/DesktopManager/$buildtype
Write-Output "copy Qt plugins"
$QtPluginPath = "$path1/../plugins"
Copy-Item -Path $QtPluginPath $exePath -Recurse -Force
Write-Output "copy finished "
if($buildtype -eq "release"){
    Write-Output "cleaning....."
    remove-item "$exePath/*.o"
    remove-item "$exePath/*.cpp"
    remove-item "$exePath/*.h"
    Write-Output "cleaned"
}
