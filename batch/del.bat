@ECHO OFF
IF NOT pwd==%cd% (cd /d %~dp0) 
cd..
if exist build RMDIR /S /Q build
