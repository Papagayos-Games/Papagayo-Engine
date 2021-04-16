@echo off

echo ---------------------------------------------------
echo Moviendo .dll a bin
echo ---------------------------------------------------

::Main de OGRE
echo moviendo OGRE
copy ..\Engine\dependencies\Ogre\build\bin\debug\OgreMain_d.dll ..\Engine\bin
copy ..\Engine\dependencies\Ogre\build\bin\release\OgreMain.dll ..\Engine\bin
::for /R "..\Engine\dependencies\Ogre\build\bin\debug" %%G in (*.dll) do copy "%%G" "..\Engine\bin"

echo moviendo OgreRTShaderSystem
copy ..\Engine\dependencies\Ogre\build\bin\debug\OgreRTShaderSystem_d.dll ..\Engine\bin
copy ..\Engine\dependencies\Ogre\build\bin\release\OgreRTShaderSystem.dll ..\Engine\bin

::zlib
echo moviendo zlib
copy ..\Engine\dependencies\Ogre\build\bin\debug\zlib.dll ..\Engine\bin
copy ..\Engine\dependencies\Ogre\build\bin\release\zlib.dll ..\Engine\bin

::Sistema de renderizado
echo moviendo RenderSystem
copy ..\Engine\dependencies\Ogre\build\bin\debug\RenderSystem_Direct3D11_d.dll ..\Engine\bin\OgreD
copy ..\Engine\dependencies\Ogre\build\bin\release\RenderSystem_Direct3D11.dll ..\Engine\bin\Ogre

::Para cargar imagenes .jpg, .png, etc
echo moviendo CODEC
copy ..\Engine\dependencies\Ogre\build\bin\debug\Codec_STBI_d.dll ..\Engine\bin\OgreD
copy ..\Engine\dependencies\Ogre\build\bin\release\Codec_STBI.dll ..\Engine\bin\Ogre

::Para cargar sonidos
echo moviendo FMOD
copy ..\Engine\dependencies\fmod\lib\fmod.dll ..\Engine\bin
copy ..\Engine\dependencies\fmod\lib\fmodL.dll ..\Engine\bin


echo ---------------------------------------------------
echo FIN
echo ---------------------------------------------------

PAUSE