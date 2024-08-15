param($type,$sourceDir)
$buildtype=""
$pwdPath=pwd
echo "source dir: $sourceDir"
echo "build dir: $pwdPath"
if($type -eq "debug"){
    $buildtype="debug"
}
elseif($type -eq "release"){
    $buildtype="release"
}
elseif($type -eq "profile"){
    $buildtype="release"
}

$EverythingPluginDllPath="$pwdPath\AssistantPlugins\EverythingPlugin\$buildtype\EverythingPlugin.dll"
$ProgramsPluginDllPath="$pwdPath\AssistantPlugins\ProgramsPlugin\$buildtype\ProgramsPlugin.dll"

$WAllpaperPluginDllPath="$pwdPath\WallpaperPlugins\BaseWallPaperPlugin\$buildtype\BaseWallPaperPlugin.dll"

$MonitorPluginDllPath="$pwdPath\PendantPlugins\MonitorPlugin\$buildtype\MonitorPlugin.dll"
echo "coping plugins..."
$pluginsDllPath=@($EverythingPluginDllPath,$ProgramsPluginDllPath,$WAllpaperPluginDllPath,$MonitorPluginDllPath)
foreach ($element in $pluginsDllPath) {
  if(Test-Path -Path $element){
    $temp = $element.Split("\")
    $temp = $temp[$temp.Count-1]
    $dirName = $temp.Split(".")[0]
    $debugDir = "$pwdPath\DesktopManager\$dirName"
    if (-Not (Test-Path -Path $debugDir)) {
        New-Item -Path $debugDir -ItemType Directory
    }
    Copy-Item -Path $element "$debugDir\" -Force
    if($type -eq "release"){
        $releaseDir = "$pwdPath\DesktopManager\$buildPath\$dirName"
        if (-Not (Test-Path -Path $releaseDir)) {
            New-Item -Path $releaseDir -ItemType Directory
        }
        Copy-Item -Path $element "$releaseDir\" -Force
        
    }
  } 
  echo "finished $dirName"
}
echo "copy finished "
