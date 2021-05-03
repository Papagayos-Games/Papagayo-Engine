# Asserts that the variable assigned to $MsBuild is a valid file path, discarding files that do not exist and folders.
function Assert-MsBuildPath([string] $MsBuild) {
    If (($MsBuild -Eq "") -Or !(Test-Path -LiteralPath $MsBuild -PathType Leaf)) {
        Write-Host "I was not able to find MSBuild.exe, please check https://docs.microsoft.com/visualstudio/msbuild/msbuild?view=vs-2019 for more information." -ForegroundColor Red
        Write-Host "  # Please specify the route to the MSBuild.exe by doing " -ForegroundColor Yellow -NoNewline
        Write-Host ".\scripts\build.ps1 `"Path\To\MSBuild.exe`""               -ForegroundColor Cyan   -NoNewline
        Write-Host " or "                                                      -ForegroundColor Yellow -NoNewline
        Write-Host ".\scripts\build.ps1 -MsBuild `"Path\To\MSBuild.exe`""      -ForegroundColor Cyan   -NoNewline
        Write-Host " to set the path."                                         -ForegroundColor Yellow
        Write-Host "  # Alternatively, do "                                    -ForegroundColor Yellow -NoNewline
        Write-Host "`$Env:MsBuild=`"Path\To\MSBuild.exe`""                     -ForegroundColor Cyan   -NoNewline
        Write-Host ", afterwards you will be able to execute "                 -ForegroundColor Yellow -NoNewline
        Write-Host ".\scripts\build.ps1"                                       -ForegroundColor Cyan   -NoNewline
        Write-Host " normally."                                                -ForegroundColor Yellow
        Exit 1
    }

    return $MsBuild
}

<#
    .Synopsis
    Finds MSBuild from the system

    .Description
    Provides functions to find and assert the MSBuild path, which is found from
    the environmental variables, falling back to command (from PATH) and finding
    it manually from the filesystem.

    .Example
    $local:MsBuild = Find-MsBuild
#>

# Finds MSBuild.exe from the user's input, falling back in the following order:
#  - Environmental Variable
#  - Get-Command (PATH)
#  - Program Files typical installation path scan
function Find-MsBuild {
    param (
        [string] $MsBuildPath
    )

    # Check if a path was given:
    if ($MsBuildPath.Length -Eq 0) {
        # Find from environmental variable:
        If ($Env:MsBuild) {
            $MsBuild = (Resolve-Path $Env:MsBuild)[0].Path
            Write-Host "MsBuild not provided, using '"           -ForegroundColor Blue -NoNewline
            Write-Host $MsBuild                                  -ForegroundColor Cyan -NoNewline
            Write-Host "' from environmental variables instead." -ForegroundColor Blue
            return Assert-MsBuildPath $MsBuild;
        }

        # Find from PATH environmental variables:
        If (Get-Command "MSBuild.exe" -ErrorAction SilentlyContinue) {
            $MsBuild = (Get-Command "MSBuild.exe").Path;
            Write-Host "MsBuild not provided, using '" -ForegroundColor Blue -NoNewline
            Write-Host $MsBuild                        -ForegroundColor Cyan -NoNewline
            Write-Host "' from PATH instead."          -ForegroundColor Blue
            return Assert-MsBuildPath $MsBuild;
        }

        # Find from ProgramFiles:
        $local:PossibleMsBuild = Resolve-Path "${Env:ProgramFiles(x86)}\Microsoft Visual Studio\2019\*\MSBuild\*\Bin\MSBuild.exe" -ErrorAction SilentlyContinue
        If (($PossibleMsBuild) -And ($PossibleMsBuild.Length -Ge 0)) {
            $MsBuild = $PossibleMsBuild[0].Path;
            Write-Host "MsBuild not provided, using '" -ForegroundColor Blue -NoNewline
            Write-Host $MsBuild                        -ForegroundColor Cyan -NoNewline
            Write-Host "' instead."                    -ForegroundColor Blue
            return Assert-MsBuildPath $MsBuild;
        }
    }
    Else {
        $MsBuild = $MsBuildPath;
        return Assert-MsBuildPath $MsBuild;
    }
}

# Build a MSVC project given a path and optional arguments
function Step-VisualStudio {
    param (
        [string] $MsBuild,
        [string] $Path,
        [string] $Type = "build",
        [string] $Configuration = "Debug",
        [string] $Platform = "x64",
        [string] $WarningLevel = "0",
        [string] $Verbosity = "minimal",
        [bool] $ThrowOnError = $false
    )

    Write-Host "# Now building '"     -ForegroundColor Blue -NoNewline
    Write-Host $Path                  -ForegroundColor Cyan -NoNewline
    Write-Host "' as $Configuration." -ForegroundColor Blue

    # Run the process
    $private:startTime = Get-Date
    & $MsBuild $Path @("-t:$Type", "-p:Configuration=$Configuration;Platform=$Platform;WarningLevel=$WarningLevel", "-verbosity:$Verbosity", "-m", "-noLogo")
    $private:exitTime = Get-Date

    # Print information to the screen
    $private:duration = $exitTime - $startTime
    If ($LastExitCode -Eq 0) {
        Write-Host "# Finished building '" -ForegroundColor Green -NoNewLine
        Write-Host $Path                   -ForegroundColor Cyan  -NoNewLine
        Write-Host "'. Took: "             -ForegroundColor Green -NoNewLine
        Write-Host ("{0:g}" -f $duration)  -ForegroundColor Cyan  -NoNewLine
        Write-Host "."                     -ForegroundColor Green
    }
    Else {
        Write-Host "# Errored when building '"        -ForegroundColor Red  -NoNewLine
        Write-Host $Path                              -ForegroundColor Cyan -NoNewLine
        Write-Host "' with code $LastExitCode Took: " -ForegroundColor Red  -NoNewLine
        Write-Host ("{0:g}" -f $duration)             -ForegroundColor Cyan -NoNewLine
        Write-Host "."                                -ForegroundColor Red
        If ($ThrowOnError) {
            Throw "Failed to build project project, please read the logs above.";
        }
    }
}

Export-ModuleMember -Function Find-MsBuild
Export-ModuleMember -Function Step-VisualStudio
