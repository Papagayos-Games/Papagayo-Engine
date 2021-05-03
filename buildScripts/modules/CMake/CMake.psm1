# Asserts that the variable assigned to $CMake is a valid file path, discarding files that do not exist and folders.
function Assert-CMakePath([string] $CMake) {
	If (($CMake -Eq "") -Or !(Test-Path -LiteralPath $CMake -PathType Leaf)) {
		Write-Host "I was not able to find cmake.exe, please download the binary at https://cmake.org." -ForegroundColor Red
		Write-Host "  # Please specify the route to the cmake.exe by doing " -ForegroundColor Yellow -NoNewline
		Write-Host ".\scripts\build.ps1 -CMake `"Path\To\cmake.exe`""        -ForegroundColor Cyan   -NoNewline
		Write-Host " to set the path."                                       -ForegroundColor Yellow
		Write-Host "  # Alternatively, do "                                  -ForegroundColor Yellow -NoNewline
		Write-Host "`$Env:CMake=`"Path\To\cmake.exe`""                       -ForegroundColor Cyan   -NoNewline
		Write-Host ", afterwards you will be able to execute "               -ForegroundColor Yellow -NoNewline
		Write-Host ".\scripts\build.ps1"                                     -ForegroundColor Cyan   -NoNewline
		Write-Host " normally."                                              -ForegroundColor Yellow
		Exit 1
	}

	return $CMake
}

# Finds cmake.exe from the user's input, falling back in the following order:
#  - Environmental Variable
#  - Get-Command (PATH)
#  - Program Files typical installation path scan
function Find-CMake {
	param (
		[string] $CMakePath
	)

	# Check if a path was given:
	if ($CMakePath.Length -Eq 0) {
		# Find from environmental variable:
		If ($Env:CMake) {
			$CMake = (Resolve-Path $Env:CMake)[0].Path
			Write-Host "CMake not provided, using '"             -ForegroundColor Blue -NoNewline
			Write-Host $CMake                                    -ForegroundColor Cyan -NoNewline
			Write-Host "' from environmental variables instead." -ForegroundColor Blue
			return Assert-CMakePath $CMake;
		}

		# Find from PATH environmental variables:
		If (Get-Command "cmake.exe" -ErrorAction SilentlyContinue) {
			$CMake = (Get-Command "cmake.exe").Path;
			Write-Host "CMake not provided, using '" -ForegroundColor Blue -NoNewline
			Write-Host $CMake                        -ForegroundColor Cyan -NoNewline
			Write-Host "' from PATH instead."        -ForegroundColor Blue
			return Assert-CMakePath $CMake;
		}

		# Find from ProgramFiles:
		$local:PossibleCMake = Resolve-Path "${Env:ProgramFiles}\CMake\bin\cmake.exe" -ErrorAction SilentlyContinue
		If (($PossibleCMake) -And ($PossibleCMake.Length -Ge 0)) {
			$CMake = $PossibleCMake[0].Path
			Write-Host "MsBuild not provided, using '" -ForegroundColor Blue -NoNewline
			Write-Host $CMake                          -ForegroundColor Cyan -NoNewline
			Write-Host "' instead."                    -ForegroundColor Blue
			return Assert-CMakePath $CMake;
		}
	}
	Else {
		$CMake = $CMakePath;
		return Assert-CMakePath $CMake;
	}
}

# Find and assert CMake
function Step-CMake([string] $CMake, [string] $Path, [string[]] $Arguments) {
	Write-Host "# Generating CMake Project for '" -ForegroundColor Blue -NoNewline
	Write-Host $Path                              -ForegroundColor Cyan -NoNewline
	Write-Host "'."                               -ForegroundColor Blue

	New-Directory -Path "$Path\build"
	$private:startTime = Get-Date
	& $CMake -S $Path -B "$Path\build" $Arguments -Wno-dev
	$private:exitTime = Get-Date

	# Print information to the screen
	$private:duration = $exitTime - $startTime
	If ($LastExitCode -Eq 0) {
		Write-Host "# Finished generating '" -ForegroundColor Green -NoNewLine
		Write-Host $Path                     -ForegroundColor Cyan  -NoNewLine
		Write-Host "'. Took: "               -ForegroundColor Green -NoNewLine
		Write-Host ("{0:g}" -f $duration)    -ForegroundColor Cyan  -NoNewLine
		Write-Host "."                       -ForegroundColor Green
	}
	Else {
		Write-Host "# Errored when generating '"       -ForegroundColor Red  -NoNewLine
		Write-Host $Path                               -ForegroundColor Cyan -NoNewLine
		Write-Host "' with code $LastExitCode Took: " -ForegroundColor Red  -NoNewLine
		Write-Host ("{0:g}" -f $duration)              -ForegroundColor Cyan -NoNewLine
		Write-Host "."                                 -ForegroundColor Red
		Throw "Failed to generate CMake project, please read the logs above.";
	}
}

Export-ModuleMember -Function Find-CMake
Export-ModuleMember -Function Step-CMake
