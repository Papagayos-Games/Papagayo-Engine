function New-Directory([string[]] $Path) {
	If (!(Test-Path -Path $Path)) {
		New-Item -Path $Path -Force -ItemType Directory | Out-Null
	}
}

function Step-CopyToFolder {
	param (
		[string] $To,
		[string] $From,
		[string[]] $Paths
	)
	Write-Host "# Now copying " -ForegroundColor Blue -NoNewline
	Write-Host $Paths.Length    -ForegroundColor Cyan -NoNewline
	Write-Host " file(s) from " -ForegroundColor Blue -NoNewline
	Write-Host $From            -ForegroundColor Cyan -NoNewline
	Write-Host " to '"          -ForegroundColor Blue -NoNewline
	Write-Host $To -ForegroundColor Cyan -NoNewline
	Write-Host "'... "          -ForegroundColor Blue -NoNewLine

	Copy-Item -Path $Paths -Destination $To

	Write-Host "Finished!"      -ForegroundColor Green
}

Export-ModuleMember -Function New-Directory
Export-ModuleMember -Function Step-CopyToFolder
