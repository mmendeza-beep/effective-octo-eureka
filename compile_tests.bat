@echo off
REM Script para compilar y ejecutar tests desde PowerShell/CMD

echo ========================================
echo Compilando proyecto con tests...
echo ========================================

cd build

REM Nota: Este script debe ejecutarse desde MSYS2 MINGW64
REM No desde PowerShell de Windows

echo.
echo IMPORTANTE: Este script debe ejecutarse desde MSYS2 MINGW64
echo.
echo Para compilar y ejecutar tests:
echo 1. Abre MSYS2 MINGW64
echo 2. cd /c/Proyectos/effective-octo-eureka/build
echo 3. mingw32-make
echo 4. ctest --output-on-failure
echo.

pause
