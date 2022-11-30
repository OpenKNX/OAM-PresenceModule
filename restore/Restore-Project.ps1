$subprojects = Get-ChildItem -File lib
cd ..
foreach ($subproject in $subprojects) {
    $cloned = 0
    if ($subproject.Name -eq "knx")
    {
        git clone https://github.com/thelsing/knx.git
        $cloned = 1
    }
    elseif ($subproject.Name -ne "README")
    {
        git clone https://github.com/OpenKNX/$subproject.git
        $cloned = 1
    }
    if ($cloned)
    {
        Remove-Item OAM-PresenceModule/lib/$subproject
        cmd /c "mklink /D OAM-PresenceModule\lib\$subproject ..\..\$subproject"
    }
}