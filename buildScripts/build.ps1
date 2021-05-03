# Version: 1.0.1

param (
    [Alias("MsBuild")]
    [Parameter(Position = 0)]
    [ValidateScript( { Test-Path -LiteralPath $_ -PathType Leaf })]
    [string]
    $MsBuildPath = "",

    [Alias("CMake")]
    [string] $CMakePath,
    [switch] $Clean,

    # Configurations
    [switch] $NDebug,
    [switch] $NRelease,

    # Dependencies
    [switch] $BuildDependencies,
    [switch] $BuildFmod,
    [switch] $BuildLUA,
    [switch] $BuildOgre,
    [switch] $BuildBullet,
    [switch] $BuildCegui,
    [switch] $BuildCeguiDependencies,

    # Project
    [switch] $BuildProject,

    # Misc
    [switch] $BuildAll
)

$ErrorActionPreference = "Stop"

$local:RootFolder = Split-Path $PSScriptRoot -Parent
$local:ModulesFolder = "$RootFolder\buildScripts\modules"
$local:BinaryDirectory = "$RootFolder\Engine\bin"
$local:DependenciesRoot = "$RootFolder\Engine\dependencies"

Import-Module -Name (Join-Path -Path $ModulesFolder -ChildPath "MsBuild")
Import-Module -Name (Join-Path -Path $ModulesFolder -ChildPath "CMake")
Import-Module -Name (Join-Path -Path $ModulesFolder -ChildPath "Shared")

$local:FModFolder = Join-Path -Path $DependenciesRoot -ChildPath "fmod"
$local:LUAFolder = Join-Path -Path $DependenciesRoot -ChildPath "lua"
$local:OgreFolder = Join-Path -Path $DependenciesRoot -ChildPath "Ogre"
$local:BulletFolder = Join-Path -Path $DependenciesRoot -ChildPath "Bullet"
$local:CeguiFolder = Join-Path -Path $DependenciesRoot -ChildPath "cegui"
$local:CeguiDependenciesFolder = Join-Path -Path $DependenciesRoot -ChildPath "cegui-dependencies"

If ($Clean) {
    $local:DllFiles = Get-ChildItem -Path $BinaryDirectory -Filter "*.dll";

    Write-Host "# Now deleting " -ForegroundColor Blue -NoNewline
    Write-Host $DllFiles.Length  -ForegroundColor Cyan -NoNewline
    Write-Host " file(s) from "  -ForegroundColor Blue -NoNewline
    Write-Host $BinaryDirectory  -ForegroundColor Cyan -NoNewline
    Write-Host "'... "           -ForegroundColor Blue -NoNewLine

    If ($DllFiles.Length -Ne 0) {
        $DllFiles | Remove-Item | Out-Null
        Write-Host "Finished!"           -ForegroundColor Green
    } Else {
        Write-Host "Skipped."            -ForegroundColor DarkGray
    }

    Remove-Variable DllFiles

    function Remove-Directory([string[]] $Path) {
        Write-Host "# Now deleting folder '" -ForegroundColor Blue -NoNewline
        Write-Host $Path                     -ForegroundColor Cyan -NoNewline
        Write-Host "'... "                   -ForegroundColor Blue -NoNewLine

        If (Test-Path -Path $Path) {
            Remove-Item -LiteralPath $Path -Recurse | Out-Null
            Write-Host "Finished!"           -ForegroundColor Green
        } Else {
            Write-Host "Skipped."            -ForegroundColor DarkGray
        }
    }

    Remove-Directory -Path (Join-Path -Path $FModFolder -ChildPath "build")
    Remove-Directory -Path (Join-Path -Path $LUAFolder -ChildPath "build")
    Remove-Directory -Path (Join-Path -Path $OgreFolder -ChildPath "build")
    Remove-Directory -Path (Join-Path -Path $BulletFolder -ChildPath "build")
    Remove-Directory -Path (Join-Path -Path $CeguiFolder -ChildPath "build")
    Remove-Directory -Path (Join-Path -Path $CeguiDependenciesFolder -ChildPath "build")
}

# Whether or not any dependency was specified
$private:BuildDependenciesSpecified = $BuildDependencies.ToBool() -Or
    $BuildFmod.ToBool() -Or
    $BuildLUA.ToBool()	-Or
    $BuildOgre.ToBool() -Or
    $BuildBullet.ToBool() -Or
    $BuildCegui.ToBool() -Or
    $BuildCeguiDependencies.ToBool()

# Whether or not any build step was specified
$private:BuildSpecified = $BuildDependenciesSpecified -Or $BuildAll.ToBool() -Or $BuildProject.ToBool()

# Whether or not any build type was specified
$private:BuildTypeSpecified = $NDebug.ToBool() -Or $NRelease.ToBool();

If ($BuildAll -Or !$BuildSpecified) {
    # If BuildAll is set or no build step was specified, set defaults to build all dependencies and the project itself
    # This will happen with the following cases:
    #   ./scripts/build.ps1
    #   ./scripts/build.ps1 -BuildAll

    $BuildDependencies = $true
    $BuildProject = $true
} ElseIf (!$BuildProject.IsPresent -And !$BuildDependenciesSpecified) {
    # If -BuildProject was not specified and no dependencies were as well
    # This will happen with the following case:
    #   ./scripts/build.ps1 -BuildProject
    #
    # This will *not* happen with the following case:
    #   ./scripts/build.ps1 -BuildBullet

    $BuildProject = $true
}

If ($BuildDependencies) {
    If (!$BuildFmod.IsPresent) { $BuildFmod = $true }
    If (!$BuildLUA.IsPresent) { $BuildLUA = $true }
    If (!$BuildOgre.IsPresent) { $BuildOgre = $true }
    If (!$BuildBullet.IsPresent) { $BuildBullet = $true }
    If (!$BuildCegui.IsPresent) { $BuildCegui = $true }
    If (!$BuildCeguiDependencies.IsPresent) { $BuildCeguiDependencies = $true }
}

If (!$BuildTypeSpecified) {
    If (!$NDebug.IsPresent) { $NDebug = $true }
    If (!$NRelease.IsPresent) { $NRelease = $true }
}

# Find and assert MSBuild and CMake
$local:MsBuild = Find-MsBuild -MsBuildPath $MsBuildPath
$local:CMake = Find-CMake -CMakePath $CMakePath

Try {
    # Build FMod
    If ($BuildFmod) {
        Step-CopyToFolder -To $BinaryDirectory -From "fmod" -Paths @(
            "$FModFolder\fmod.dll",
			"$FModFolder\fmodL.dll",
			"$FModFolder\lib\fmod_vc.lib",
			"$FModFolder\lib\fmodL_vc.lib"
        )
    }

    # Build LUA
    If ($BuildLUA) {
        Step-CopyToFolder -To $BinaryDirectory -From "lua" -Paths @(
            "$LUAFolder\lua54.dll",
			"$LUAFolder\liblua54.a"
        )
    }
	
	# Build Ogre
    If ($BuildOgre) {
        Step-CMake $CMake $OgreFolder @(
		"-DOGRE_BUILD_COMPONENT_BITES:BOOL=OFF",
		"-DOGRE_BUILD_COMPONENT_CSHARP:BOOL=OFF",
		"-DOGRE_BUILD_COMPONENT_HTMLS:BOOL=OFF",
		"-DOGRE_BUILD_COMPONENT_JAVA:BOOL=OFF",
		"-DOGRE_BUILD_COMPONENT_PYTHON:BOOL=OFF",
		"-DOGRE_BUILD_RENDERSYSTEM_TINY:BOOL=OFF"
		)

        If ($NDebug) {
            Step-VisualStudio -MsBuild $MsBuild -Path "$OgreFolder\build\OGRE.sln" -Configuration "Debug"
            Step-CopyToFolder -To $BinaryDirectory -From "Ogre" -Paths @(
                "$OgreFolder\build\bin\debug\OgreMain_d.dll",
                "$OgreFolder\build\bin\debug\RenderSystem_Direct3D11_d.dll",
                "$OgreFolder\build\bin\debug\RenderSystem_GL_d.dll",
                "$OgreFolder\build\bin\debug\OgreRTShaderSystem_d.dll",
                "$OgreFolder\build\bin\debug\Codec_STBI_d.dll",
                "$OgreFolder\build\bin\debug\Plugin_ParticleFX_d.dll",
                "$OgreFolder\build\bin\debug\zlib.dll",
				"$OgreFolder\build\bin\debug\SDL2.dll",
				"$OgreFolder\build\SDL2-build\RelWithDebInfo\SDL2.lib",
				"$OgreFolder\build\lib\Debug\OgreMain_d.lib",
				"$OgreFolder\build\lib\Debug\OgreRTShaderSystem_d.lib",
				"$OgreFolder\build\lib\Debug\RenderSystem_Direct3D11_d.lib"
            )
        }

        If ($NRelease) {
            Step-VisualStudio -MsBuild $MsBuild -Path "$OgreFolder\build\OGRE.sln" -Configuration "Release"
            Step-CopyToFolder -To $BinaryDirectory -From "Ogre" -Paths @(
                "$OgreFolder\build\bin\release\OgreMain.dll",
                "$OgreFolder\build\bin\release\RenderSystem_Direct3D11.dll",
                "$OgreFolder\build\bin\release\RenderSystem_GL.dll",
                "$OgreFolder\build\bin\release\OgreRTShaderSystem.dll",
                "$OgreFolder\build\bin\release\Codec_STBI.dll",
                "$OgreFolder\build\bin\release\Plugin_ParticleFX.dll",
                "$OgreFolder\build\bin\release\zlib.dll"
				"$OgreFolder\build\bin\release\SDL2.dll",
				"$OgreFolder\build\SDL2-build\RelWithDebInfo\SDL2main.lib",
				"$OgreFolder\build\lib\Release\OgreMain.lib",
				"$OgreFolder\build\lib\Release\OgreRTShaderSystem.lib",
				"$OgreFolder\build\lib\Release\RenderSystem_Direct3D11.lib"
            )
        }
    }
	
    # Build Bullet
    If ($BuildBullet) {
        Step-CMake $CMake $BulletFolder @(
            "-DBUILD_BULLET2_DEMOS:BOOL=OFF",
            "-DBUILD_BULLET3:BOOL=ON",
            "-DBUILD_CLSOCKET:BOOL=OFF",
            "-DBUILD_CPU_DEMOS:BOOL=OFF",
            "-DBUILD_ENET:BOOL=OFF",
            "-DBUILD_EXTRAS:BOOL=OFF",
            "-DBUILD_OPENGL3_DEMOS:BOOL=OFF",
            "-DBUILD_PYBULLET:BOOL=OFF",
            "-DBUILD_SHARED_LIBS:BOOL=OFF",
            "-DBUILD_UNIT_TESTS:BOOL=OFF",
			"-DENABLE_VHACD:BOOL=OFF",
			"-DINSTALL_LIBS:BOOL=ON",
            "-DUSE_MSVC_RUNTIME_LIBRARY_DLL:BOOL=ON"
        )

        If ($NDebug) {
            Step-VisualStudio -MsBuild $MsBuild -Path "$BulletFolder\build\BULLET_PHYSICS.sln" -Configuration "Debug"
			Step-CopyToFolder -To $BinaryDirectory -From "Bullet" -Paths @(
                "$BulletFolder\\build\lib\Debug\BulletCollision_Debug.lib",
				"$BulletFolder\\build\lib\Debug\BulletDynamics_Debug.lib",
				"$BulletFolder\\build\lib\Debug\BulletInverseDynamics_Debug.lib",
				"$BulletFolder\\build\lib\Debug\BulletSoftBody_Debug.lib",
				"$BulletFolder\\build\lib\Debug\LinearMath_Debug.lib"
            )
        }

        If ($NRelease) {
            Step-VisualStudio -MsBuild $MsBuild -Path "$BulletFolder\build\BULLET_PHYSICS.sln" -Configuration "Release"
			Step-CopyToFolder -To $BinaryDirectory -From "Bullet" -Paths @(
				"$BulletFolder\\build\lib\Release\BulletCollision.lib",
				"$BulletFolder\\build\lib\Release\BulletDynamics.lib",
				"$BulletFolder\\build\lib\Release\BulletInverseDynamics.lib",
				"$BulletFolder\\build\lib\Release\BulletSoftBody.lib",
				"$BulletFolder\\build\lib\Release\LinearMath.lib"
            )
		}
    }
   

    # Build CEGUI's dependencies
    If ($BuildCeguiDependencies) {
        Step-CMake $CMake $CeguiDependenciesFolder @()

        If ($NDebug) {
            Step-VisualStudio -MsBuild $MsBuild -Path "$CeguiDependenciesFolder\build\CEGUI-DEPS.sln" -Configuration "Debug"
        }

        If ($NRelease) {
            Step-VisualStudio -MsBuild $MsBuild -Path "$CeguiDependenciesFolder\build\CEGUI-DEPS.sln" -Configuration "Release"
        }
    }

    # Build CEGUI
    #If ($BuildCegui) {
    #    $local:CeguiBuiltDependencies = Join-Path -Path $CeguiDependenciesFolder -ChildPath "build/dependencies"
    #    Step-CMake $CMake $CeguiFolder @(
    #        "-DCEGUI_BUILD_RENDERER_DIRECT3D10:BOOL=OFF",
    #        "-DCEGUI_BUILD_RENDERER_DIRECT3D11:BOOL=OFF",
    #        "-DCEGUI_BUILD_RENDERER_DIRECT3D9:BOOL=OFF",
    #        "-DCEGUI_BUILD_RENDERER_DIRECTFB:BOOL=OFF",
    #        "-DCEGUI_BUILD_RENDERER_IRRLICHT:BOOL=OFF",
    #        "-DCEGUI_BUILD_RENDERER_NULL:BOOL=OFF",
    #        "-DCEGUI_BUILD_RENDERER_OGRE:BOOL=ON",
    #        "-DCEGUI_BUILD_RENDERER_OPENGL:BOOL=OFF",
    #        "-DCEGUI_BUILD_RENDERER_OPENGL3:BOOL=OFF",
    #        "-DCEGUI_BUILD_RENDERER_OPENGLES:BOOL=OFF",
    #        "-DCMAKE_PREFIX_PATH:PATH=$CeguiBuiltDependencies",
    #        "-DOGRE_H_BUILD_SETTINGS_PATH:PATH=$OgreFolder/build/include",
    #        "-DOGRE_H_PATH:PATH=$OgreFolder/OgreMain/include",
    #        "-DOGRE_LIB:FILEPATH=$OgreFolder/build/lib/Release/OgreMain.lib",
    #        "-DOGRE_LIB_DBG:FILEPATH=$OgreFolder/build/lib/Debug/OgreMain_d.lib"
    #    )
	#
    #    # Let's be honest, I got done with MSBuild here. The world would be beautiful if it'd let me define constants
    #    # via CLI, but looks like it's impossible without CMake.
    #    $private:Content = Get-Content -Path "$CeguiFolder\build\cegui\include\CEGUI\Config.h"
    #    $private:Content = $Content -replace "define CEGUI_OGRE_VERSION_MAJOR 0", "define CEGUI_OGRE_VERSION_MAJOR 1"
    #    $private:Content = $Content -replace "define CEGUI_OGRE_VERSION_MINOR 0", "define CEGUI_OGRE_VERSION_MINOR 9"
    #    Set-Content -Path "$CeguiFolder\build\cegui\include\CEGUI\Config.h" -Value $Content
    #    Remove-Variable Content
	#
    #    If ($NDebug) {
    #        Step-VisualStudio -MsBuild $MsBuild -Path "$CeguiFolder\build\cegui.sln" -Configuration "Debug"
    #        Step-CopyToFolder -To $BinaryDirectory -From "cegui" -Paths @(
    #            "$CeguiFolder\build\bin\CEGUIBase-0_d.dll",
    #            "$CeguiFolder\build\bin\CEGUIOgreRenderer-0_d.dll",
    #            "$CeguiBuiltDependencies\bin\freetype_d.dll",
    #            "$CeguiBuiltDependencies\bin\glew_d.dll",
    #            "$CeguiBuiltDependencies\bin\glfw_d.dll",
    #            "$CeguiBuiltDependencies\bin\jpeg_d.dll",
    #            "$CeguiBuiltDependencies\bin\libexpat_d.dll",
    #            "$CeguiBuiltDependencies\bin\libpng_d.dll",
    #            "$CeguiBuiltDependencies\bin\pcre_d.dll",
    #            "$CeguiBuiltDependencies\bin\SILLY_d.dll"
    #        )
    #    }
	#
    #    If ($NRelease) {
    #        Step-VisualStudio -MsBuild $MsBuild -Path "$CeguiFolder\build\cegui.sln" -Configuration "Release"
    #        Step-CopyToFolder -To $BinaryDirectory -From "cegui" -Paths @(
    #            "$CeguiFolder\build\bin\CEGUIBase-0.dll",
    #            "$CeguiFolder\build\bin\CEGUIOgreRenderer-0.dll",
    #            "$CeguiBuiltDependencies\bin\freetype.dll",
    #            "$CeguiBuiltDependencies\bin\glew.dll",
    #            "$CeguiBuiltDependencies\bin\glfw.dll",
    #            "$CeguiBuiltDependencies\bin\jpeg.dll",
    #            "$CeguiBuiltDependencies\bin\libexpat.dll",
    #            "$CeguiBuiltDependencies\bin\libpng.dll",
    #            "$CeguiBuiltDependencies\bin\pcre.dll",
    #            "$CeguiBuiltDependencies\bin\SILLY.dll"
    #        )
    #    }
	#
    #    Remove-Variable CeguiBuiltDependencies
    #}


    # Build project
    If ($BuildProject) {
        If ($NDebug) {
            Step-VisualStudio $MsBuild "$RootFolder\Engine\Untitled-Engine.sln" -ThrowOnError $True -Configuration "Debug" -WarningLevel "3"
        }

        If ($NRelease) {
            Step-VisualStudio $MsBuild "$RootFolder\Engine\Untitled-Engine.sln" -ThrowOnError $True -Configuration "Release" -WarningLevel "3"
        }
    }

    Exit 0
} Catch {
    # Write the exception
    Write-Host -Object $_
    Write-Host -Object $_.Exception
    Write-Host -Object $_.ScriptStackTrace

    Exit 1
} Finally {
    # Unregister modules
    Remove-Module MsBuild
    Remove-Module CMake
    Remove-Module Shared
}
