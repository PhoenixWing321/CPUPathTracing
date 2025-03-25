# Get paths from env
if (-not $env:ROOT_DIR_EXPORT_LIB) {
    # $env:ROOT_DIR_EXPORT_LIB = "E:\Root"
    Write-Error "Environment variable ROOT_DIR_EXPORT_LIB is not set!"
    exit 1
}
$outputDir = $env:ROOT_DIR_EXPORT_LIB
$buildDir = "./build"

# Copy files
Write-Host "Copying Debug lib: $buildDir\Debug\CPUPathTracing.lib -> $outputDir\debug\"   
Copy-Item -Path "$buildDir\Debug\CPUPathTracing.lib" -Destination "$outputDir\debug\" -Force

Write-Host "Copying Release lib: $buildDir\Release\CPUPathTracing.lib -> $outputDir\bin\"   
    Copy-Item -Path "$buildDir\Release\CPUPathTracing.lib" -Destination "$outputDir\bin\" -Force

Write-Host "Export completed!"
