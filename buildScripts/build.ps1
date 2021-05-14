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
    
	
    # Build LUA
    
	
	# Build Ogre
    
	
    # Build Bullet
	
	
    # Build CEGUI's dependencies

    # Build CEGUI
    If ($BuildCegui) {
		#Expand-Archive -Path $DependenciesRoot\cegui.zip -DestinationPath $DependenciesRoot
        $local:CeguiBuiltDependencies = Join-Path -Path $CeguiDependenciesFolder -ChildPath "build/dependencies"
		
        If ($NDebug) {
            Step-VisualStudio -MsBuild $MsBuild -Path "$CeguiFolder\build\cegui.sln" -Configuration "Debug"
            Step-CopyToFolder -To $BinaryDirectory -From "cegui" -Paths @(
				#dll
                "$CeguiFolder\build\bin\CEGUIBase-0_d.dll",
                "$CeguiFolder\build\bin\CEGUIOgreRenderer-0_d.dll",
                "$CeguiBuiltDependencies\bin\freetype_d.dll",
                "$CeguiBuiltDependencies\bin\glew_d.dll",
                "$CeguiBuiltDependencies\bin\glfw_d.dll",
                "$CeguiBuiltDependencies\bin\jpeg_d.dll",
                "$CeguiBuiltDependencies\bin\libexpat_d.dll",
                "$CeguiBuiltDependencies\bin\libpng_d.dll",
                "$CeguiBuiltDependencies\bin\pcre_d.dll",
                "$CeguiBuiltDependencies\bin\SILLY_d.dll",
				#lib
				"$CeguiFolder\build\lib\CEGUIBase-0_d.lib",
                "$CeguiFolder\build\lib\CEGUIOgreRenderer-0_d.lib",
                "$CeguiBuiltDependencies\lib\static\freetype_d.lib",
                "$CeguiBuiltDependencies\lib\static\glew_d.lib",
                "$CeguiBuiltDependencies\lib\static\glfw_d.lib",
                "$CeguiBuiltDependencies\lib\static\jpeg_d.lib",
                "$CeguiBuiltDependencies\lib\static\libexpat_d.lib",
                "$CeguiBuiltDependencies\lib\static\libpng_d.lib",
                "$CeguiBuiltDependencies\lib\static\pcre_d.lib",
                "$CeguiBuiltDependencies\lib\static\SILLY_d.lib"
            )
        }
		
        If ($NRelease) {
            Step-VisualStudio -MsBuild $MsBuild -Path "$CeguiFolder\build\cegui.sln" -Configuration "Release"
            Step-CopyToFolder -To $BinaryDirectory -From "cegui" -Paths @(
				#dll
                "$CeguiFolder\build\bin\CEGUIBase-0.dll",
                "$CeguiFolder\build\bin\CEGUIOgreRenderer-0.dll",
                "$CeguiBuiltDependencies\bin\freetype.dll",
                "$CeguiBuiltDependencies\bin\glew.dll",
                "$CeguiBuiltDependencies\bin\glfw.dll",
                "$CeguiBuiltDependencies\bin\jpeg.dll",
                "$CeguiBuiltDependencies\bin\libexpat.dll",
                "$CeguiBuiltDependencies\bin\libpng.dll",
                "$CeguiBuiltDependencies\bin\pcre.dll",
                "$CeguiBuiltDependencies\bin\SILLY.dll",
				#lib
				"$CeguiFolder\build\lib\CEGUIBase-0.lib",
                "$CeguiFolder\build\lib\CEGUIOgreRenderer-0.lib",
				"$CeguiBuiltDependencies\lib\static\freetype.lib",
                "$CeguiBuiltDependencies\lib\static\glew.lib",
                "$CeguiBuiltDependencies\lib\static\glfw.lib",
                "$CeguiBuiltDependencies\lib\static\jpeg.lib",
                "$CeguiBuiltDependencies\lib\static\libexpat.lib",
                "$CeguiBuiltDependencies\lib\static\libpng.lib",
                "$CeguiBuiltDependencies\lib\static\pcre.lib",
                "$CeguiBuiltDependencies\lib\static\SILLY.lib"
            )
        }
		
        Remove-Variable CeguiBuiltDependencies
    }
	
	
    #Build project
    If ($BuildProject) {
        If ($NDebug) {
            Step-VisualStudio $MsBuild "$RootFolder\Engine\Papagayo-Engine.sln" -ThrowOnError $True -Configuration "Debug" -WarningLevel "3"
        }
	
        If ($NRelease) {
            Step-VisualStudio $MsBuild "$RootFolder\Engine\Papagayo-Engine.sln" -ThrowOnError $True -Configuration "Release" -WarningLevel "3"
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
