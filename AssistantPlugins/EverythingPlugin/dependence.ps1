param($type,$sourceDir)
$pwdPath = Get-Location
echo "==============make everything plugin dependence=============="
echo $type
echo $sourceDir
$local:everythinsDependencePath = "$sourceDir/everything/dll/*.dll"
$local:buildPath = "$pwdPath/AssistantPlugins/EverythingPlugin/$buildType/"
Copy-Item -Path $everythinsDependencePath  $buildPath -Recurse -Force
echo "==========================finished==========================="
