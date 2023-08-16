function CompileAndRunAlgorithm {
    param(
        [string]$algorithmName
    )

    $currentDir = Get-Location
    Write-Host "Compiling $algorithmName with g++..."

    $traversalDir = Join-Path -Path $currentDir -ChildPath '\traversals'
    Set-Location -Path $traversalDir
    $gccOutput = & g++ "$algorithmName.cpp" -o "$algorithmName" 2>&1
    if ($LASTEXITCODE -ne 0) {
        Write-Host "Compilation failed:"
        Write-Host $gccOutput
        return
    }

    Write-Host "Compilation successful."

    & ".\$algorithmName.exe" 
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
        Write-Host "2. Run Dijkstras"
        Write-Host "3. Visualise"
        Write-Host "4. Exit"

        $choice = Read-Host "Enter your choice (1/2/3/4):"

        switch ($choice) {
            1 {
                CompileAndRunAlgorithm -algorithmName "bfs"
            }
            2 {
                CompileAndRunAlgorithm -algorithmName "dijkstras"
            }
            3 {
                VisualisePath
            }
            4 {
                return
            }
            default {
                Write-Host "Invalid choice."
            }
        }
    }
}

Main
