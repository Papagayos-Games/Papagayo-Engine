@echo off

echo ---------------------------------------------------
echo Creando la carpeta "build" en dependencies/Ogre
echo ---------------------------------------------------
MD ..\Engine\dependencies\Ogre\build

echo ---------------------------------------------------
echo Ejecutando exe de CMake
echo Hay que generar Ogre en su carpeta build
echo ---------------------------------------------------
start ..\Engine\dependencies\cmake-3.20.0\bin\cmake-gui.exe

PAUSE