# Create build directory if it doesn't exist
# 用VsCode的面板进行build目录的初始化，就不要下面这句了
# cmake -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE --no-warn-unused-cli -S$PSScriptRoot -B$PSScriptRoot\build -G "Visual Studio 17 2022" -T host=x64 -A x64

# Build Debug version
Write-Output "Building Debug version..."
cmake --build build --config Debug --target ALL_BUILD -j 26 --

# Build Release version
Write-Output "Building Release version..."
cmake --build build --config Release --target ALL_BUILD -j 26 --
