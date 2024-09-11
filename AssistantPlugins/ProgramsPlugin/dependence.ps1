param($type,$sourceDir)
$pwdPath = Get-Location
echo "==============make programs plugin dependence=============="
echo $type
echo $sourceDir
$local:buildPath = "$pwdPath/AssistantPlugins/ProgramsPlugin/$buildType/"
if($buildType -eq "release"){
windeployqt "$buildPath/ProgramsPlugin.dll"
}
echo "==========================finished==========================="
