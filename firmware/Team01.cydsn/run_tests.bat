@echo off
REM Compile tests
make

REM Check if the compile was successful
if %ERRORLEVEL% NEQ 0 (
    echo Compilation failed.
    exit /b 1
)

REM Run tests
test_executable

REM Pause to view results
pause
