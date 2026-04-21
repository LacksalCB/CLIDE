@echo off
set CLIDE=clide
set INSTALL_PATH=%APPDATA%\%CLIDE%

echo Copy templates to system?

choice /C YN/M "Install"
if errorlevel 2 exit /b
if errorlevel 1 (
    echo Installing templates...
    if not exist "%INSTALL_PATH%" mkdir "%INSTALL_PATH%"
    xcopy /E /I /Y "templates\*" "%INSTALL_PATH%"
    echo Finished Install
)
