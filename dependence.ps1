param($type,$sourceDir)
$buildtype=""
$pwdPath=Get-Location
Write-Output "source dir: $sourceDir"
Write-Output "build dir: $pwdPath"
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
            Copy-Item -Path $dllPath  $buildPath -Recurse -Force 
            Copy-Item -Path $exePath  $buildPath -Recurse -Force
        }
        Write-Output "finished $pluginName"
    }


}
Write-Output "copy finished "

Write-Output "coping settings..."
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

