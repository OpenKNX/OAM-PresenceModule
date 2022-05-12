# set product names
$targetName="PresenceModule"
$sourceName="PMmodul"
# $releaseName="$sourceName-Release"
$releaseName="$sourceName"

# check for working dir
if (Test-Path -Path release) {
    # clean working dir
    Remove-Item -Recurse release\*
} else {
    New-Item -Path release -ItemType Directory | Out-Null
}

# create required directories
Copy-Item -Recurse scripts/data release

# get xml for kxnprod
~/bin/OpenKNXproducer.exe create --Debug --Output="release/$targetName.knxprod" --HeaderFileName="src/$sourceName.h" "src/$releaseName.xml"
if (!$?) {
    Write-Host "Error in knxprod, Release was not built!"
    exit 1
}
Move-Item "src/$releaseName.debug.xml" "release/data/$targetName.xml"

# build firmware based on generated headerfile for PICO
scripts/Build-Step.ps1 release_RP2040_devel firmware-devel uf2
if (!$?) { exit 1 }

scripts/Build-Step.ps1 release_RP2040_devel2 firmware-devel2 uf2
if (!$?) { exit 1 }

# build firmware based on generated headerfile for SAMD
scripts/Build-Step.ps1 release_SAMD_v31 firmware-v31 bin
if (!$?) { exit 1 }

# add necessary scripts
Copy-Item scripts/Readme-Release.txt release/
Copy-Item scripts/Build-knxprod.ps1 release/
Copy-Item scripts/Upload-Firmware*.ps1 release/

# cleanup
Remove-Item "release/$targetName.knxprod"

# create package 
Compress-Archive -Path release/* -DestinationPath Release.zip
Remove-Item -Recurse release/*
Move-Item Release.zip "release/$targetName.zip"

Write-Host "Release successfully created!"
