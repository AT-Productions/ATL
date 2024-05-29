@ECHO OFF
IF NOT pwd==%cd% (cd /d %~dp0) 
call .\globals.bat
if not defined DevEnvDir ( 
    call "%TOOLSPATH%\VsDevCmd.bat"
)

cd..
MKDIR build & CD build & cmake .. & cmake --build . & CD ..