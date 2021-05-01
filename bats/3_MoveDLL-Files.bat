@echo off

echo ---------------------------------------------------
echo Moviendo .dll a bin
echo ---------------------------------------------------

::Main de OGRE
echo moviendo OGRE dll
copy ..\Engine\dependencies\Ogre\build\bin\debug\OgreMain_d.dll ..\Engine\bin
copy ..\Engine\dependencies\Ogre\build\bin\release\OgreMain.dll ..\Engine\bin

echo moviendo OGRE Debug Libs
copy ..\Engine\dependencies\Ogre\build\lib\Debug\OgreMain_d.lib ..\Engine\bin
copy ..\Engine\dependencies\Ogre\build\lib\Debug\OgreRTShaderSystem_d.lib ..\Engine\bin

echo moviendo OGRE Release Libs
copy ..\Engine\dependencies\Ogre\build\lib\Release\OgreMain.lib ..\Engine\bin
copy ..\Engine\dependencies\Ogre\build\lib\Release\OgreRTShaderSystem.lib ..\Engine\bin

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

echo moviendo SDL dll
copy ..\Engine\dependencies\Ogre\build\bin\debug\SDL2.dll ..\Engine\bin
copy ..\Engine\dependencies\Ogre\build\bin\release\SDL2.dll ..\Engine\bin

echo moviendo SDL Libs
copy ..\Engine\dependencies\Ogre\build\SDL2-build\RelWithDebInfo\SDL2.lib ..\Engine\bin
copy ..\Engine\dependencies\Ogre\build\SDL2-build\RelWithDebInfo\SDL2main.lib ..\Engine\bin

::Bullet
echo moviendo Bullet Debug Libs
copy ..\Engine\dependencies\Bullet\build\lib\Debug\BulletCollision_Debug.lib ..\Engine\bin
copy ..\Engine\dependencies\Bullet\build\lib\Debug\BulletDynamics_Debug.lib ..\Engine\bin
copy ..\Engine\dependencies\Bullet\build\lib\Debug\BulletInverseDynamics_Debug.lib ..\Engine\bin
copy ..\Engine\dependencies\Bullet\build\lib\Debug\BulletSoftBody_Debug.lib ..\Engine\bin
copy ..\Engine\dependencies\Bullet\build\lib\Debug\LinearMath_Debug.lib ..\Engine\bin

echo moviendo Bullet Release Libs
copy ..\Engine\dependencies\Bullet\build\lib\Release\BulletCollision.lib ..\Engine\bin
copy ..\Engine\dependencies\Bullet\build\lib\Release\BulletDynamics.lib ..\Engine\bin
copy ..\Engine\dependencies\Bullet\build\lib\Release\BulletInverseDynamics.lib ..\Engine\bin
copy ..\Engine\dependencies\Bullet\build\lib\Release\BulletSoftBody.lib ..\Engine\bin
copy ..\Engine\dependencies\Bullet\build\lib\Release\LinearMath.lib ..\Engine\bin

::Para cargar sonidos
echo moviendo FMOD
copy ..\Engine\dependencies\fmod\fmodL.dll ..\Engine\bin
copy ..\Engine\dependencies\fmod\fmod.dll ..\Engine\bin
copy ..\Engine\dependencies\fmod\lib\fmodL_vc.lib ..\Engine\bin
copy ..\Engine\dependencies\fmod\lib\fmod_vc.lib ..\Engine\bin

echo moviendo LUA
copy ..\Engine\dependencies\lua\lua54.dll ..\Engine\bin
copy ..\Engine\dependencies\lua\liblua54.a ..\Engine\bin

echo ---------------------------------------------------
echo FIN
echo ---------------------------------------------------

PAUSE