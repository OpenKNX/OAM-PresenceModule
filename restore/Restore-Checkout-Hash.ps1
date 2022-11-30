$subprojects = Get-Content dependencies.txt
foreach ($subproject in $subprojects) {
    $attr = $subproject.Split()
    if ($attr[0] -ne "-------") {
        git --git-dir "$($attr[2])/.git" checkout $attr[0]
    }
}