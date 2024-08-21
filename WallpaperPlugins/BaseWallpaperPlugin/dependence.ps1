param($buildType,$sourceDir)
# import you should use local to define your variable,and you can use the variable from main dependence.ps1
$local:pwdPath = Get-Location
echo "==============make wallpaper plugin dependence=============="
#echo $type
#echo $sourceDir
$local:ffmpegDependencePath = "$sourceDir/ffmpeg/bin/*.*"
$local:buildPath = "$pwdPath/WallpaperPlugins/BaseWallPaperPlugin/$buildType/"
Copy-Item -Path $ffmpegDependencePath  $buildPath -Recurse -Force
if($buildType -eq "release"){
# make windeployqt
}
echo "==========================finished==========================="
