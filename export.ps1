# check if my.config exists  
if (-not (Test-Path "my.config")) {
    Write-Host "my.config is not found!"
    exit 1
}

# Read configuration file and expand environment variables
$configContent = Get-Content "my.config" | Where-Object { $_ -notmatch '^\s*#' -and $_ -notmatch '^\s*$' }
$config = @{}
foreach ($line in $configContent) {
    if ($line -match '(.+?)=(.+)') {
        $key = $matches[1]
        # Expand both environment variables and existing config variables
        $value = $ExecutionContext.InvokeCommand.ExpandString($matches[2])
        $config[$key] = $value
    }
}

# Get paths from config
$outputDir = $config.ROOT_DIR_EXPORT_LIB
$buildDir = $config.ROOT_DIR_BUILD
Write-Host "outputDir: $outputDir"
Write-Host "buildDir: $buildDir"
# $ROOT_DIR_3rdParty = $config.ROOT_DIR_3rdParty

# Copy files
Write-Host "Copying Debug lib: $buildDir\Debug\CPUPathTracing.lib -> $outputDir\Debug\"   
Copy-Item -Path "$buildDir\Debug\CPUPathTracing.lib" -Destination "$outputDir\Debug\" -Force

Write-Host "Copying Release lib: $buildDir\Release\CPUPathTracing.lib -> $outputDir\bin\"   
Copy-Item -Path "$buildDir\Release\CPUPathTracing.lib" -Destination "$outputDir\bin\" -Force

Write-Host "Export completed!"
