#!/bin/bash

# Get the directory where the script is located
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

# Note: CMake initialization is handled by VSCode panels, so we skip the cmake configure step
# cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -S. -Bbuild -G "Unix Makefiles"

# Build Debug version
echo "Building Debug version..."
cmake --build build --config Debug --target all -j 26 --

# Build Release version
echo "Building Release version..."
cmake --build build --config Release --target all -j 26 --

# export
bash "$SCRIPT_DIR/export.sh" 