param($type,$sourceDir)
$pwdPath = Get-Location
echo "==============make monitor plugin dependence=============="
echo $type
echo $sourceDir
$local:buildPath = "$pwdPath/PendantPlugins/MonitorPlugin/$buildType/"
if($buildType -eq "release"){
# make windeployqt
}
echo "==========================finished==========================="
