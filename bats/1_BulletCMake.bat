@echo off

echo ---------------------------------------------------
echo Creando la carpeta "build" en dependencies/Bullet/build
echo ---------------------------------------------------
MD ..\Engine\dependencies\Bullet\build

echo ---------------------------------------------------
echo Ejecutando exe de CMake
echo Hay que generar Bullet en su carpeta build
echo ---------------------------------------------------
start ..\Engine\dependencies\cmake-3.20.0\bin\cmake-gui.exe

PAUSE