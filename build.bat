@ECHO OFF
setlocal
IF NOT pwd==%cd% (cd /d %~dp0)
call .\batch\msvs-dev-env.bat
cd ..

if not exist build mkdir build
if not exist output mkdir output

cd build
if(%1 == "Release") (
    @REM cmake .. --preset="x64-release"
    "C:\Windows\system32\cmd.exe" /c "%SYSTEMROOT%\System32\chcp.com 65001 >NUL && "%CMAKEPATH%\CMake\bin\cmake.exe"  -G "Ninja"  -DCMAKE_C_COMPILER:STRING="%COMPILERPATH%" -DCMAKE_CXX_COMPILER:STRING="%COMPILERPATH%" -DCMAKE_BUILD_TYPE:STRING="%1" -DCMAKE_INSTALL_PREFIX:PATH="./install/x64-release"   -DCMAKE_MAKE_PROGRAM="%NINJAPATH%\ninja.exe" ".." 2>&1"
    cmake --build . --config %1 
) else (
    @REM cmake .. --preset="x64-debug"
    "C:\Windows\system32\cmd.exe" /c "%SYSTEMROOT%\System32\chcp.com 65001 >NUL && "%CMAKEPATH%\CMake\bin\cmake.exe"  -G "Ninja"  -DCMAKE_C_COMPILER:STRING="%COMPILERPATH%" -DCMAKE_CXX_COMPILER:STRING="%COMPILERPATH%" -DCMAKE_BUILD_TYPE:STRING="Debug" -DCMAKE_INSTALL_PREFIX:PATH="./install/x64-debug"   -DCMAKE_MAKE_PROGRAM="%NINJAPATH%\ninja.exe" ".." 2>&1"
    cmake --build . --config Debug
)
cd..
ECHO ======== START RUNNING =========
ECHO ================================
build\ATL.exe %*
ECHO ================================

if exist .\output\*.exe del .\output\*.exe
if exist .\output\*.obj del .\output\*.obj

SET "OUTPUT="
SET "INPUT="

:Loop
IF "%1" equ "" GOTO Continue
IF "%1" equ "-o" (
    SET "OUTPUT=%2"
    GOTO Continue
)
SHIFT
GOTO Loop
:Continue

.\nasm-2.16.02\nasm.exe -f win64 .\output\test.asm -o .\output\%OUTPUT%.obj
.\Golink\GoLink.exe /console /entry main .\output\%OUTPUT%.obj kernel32.dll

ECHO ======== START RUNNING =========
ECHO ================================
.\output\test.exe
ECHO ================================

endlocal