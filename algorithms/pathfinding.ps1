function CompileAndRunBfs {

    $currentDir = Get-Location
    Write-Host "Compiling bfs with g++..."

    $traversalDir = Join-Path -Path $currentDir -ChildPath '\traversals'
    Set-Location -Path $traversalDir
    $gccOutput = & g++ 'bfs.cpp' -o 'bfs' 2>&1
    if ($LASTEXITCODE -ne 0) {
        Write-Host "Compilation failed:"
        Write-Host $gccOutput
        return
    }

    Write-Host "Compilation successful."

    & '.\bfs.exe' 
    Set-Location -Path $currentDir
}

function VisualisePath {

    $currentDir = Get-Location
    $PlotMapPath = Join-Path -Path $currentDir -ChildPath '/visualisation/plot_output_map.py'


    & python $PlotMapPath
}

function Main {
    while ($true) {
        Write-Host "COMPSYS 301 Team_01 Pathfinding Algorithms"
        Write-Host "------------------------------------------"
        Write-Host "Options:"
        Write-Host "1. Run BFS"
        Write-Host "2. Visualise"
        Write-Host "3. Exit"

        $choice = Read-Host "Enter your choice (1/2/3):"

        switch ($choice) {
            1 {
                CompileAndRunBfs -CppFileName $CppFileName
            }
            2 {
                VisualisePath -PythonFileName $PythonFileName
            }
            3 {
                return
            }
            default {
                Write-Host "Invalid choice."
            }
        }
    }
}

Main
