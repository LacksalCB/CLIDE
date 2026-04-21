@echo off
set CLIDE=clide
set INSTALL_PATH=%APPDATA%\%CLIDE%

echo "%INSTALL_PATH%"

choice /C YN /M "Install templates to system?"
if errorlevel 2 exit /b
if errorlevel 1 (
    echo Installing templates...
    if not exist "%INSTALL_PATH%" mkdir "%INSTALL_PATH%"
    xcopy /E /I /Y "templates\*" "%INSTALL_PATH%"
    echo Finished Install
)
