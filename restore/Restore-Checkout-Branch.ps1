$subprojects = Get-Content dependencies.txt
$currentDir = Get-Location
foreach ($subproject in $subprojects) {
    $attr = $subproject.Split()
    if ($attr[0] -ne "-------") {
        # the following does not work as expected
        # git --git-dir "$($attr[2])/.git" checkout $attr[1]
        Set-Location $attr[2]
        git checkout $attr[1]
        Set-Location $currentDir
    }
}