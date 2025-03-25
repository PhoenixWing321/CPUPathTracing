#!/bin/bash

# Get paths from env
if [ -z "$ROOT_DIR_EXPORT_LIB" ]; then
    # export ROOT_DIR_EXPORT_LIB="~/export"
    echo "Error: Environment variable ROOT_DIR_EXPORT_LIB is not set!"
    exit 1
fi

outputDir=$ROOT_DIR_EXPORT_LIB
buildDir="./build"

echo "buildDir: $buildDir"
echo "outputDir: $outputDir"

# Copy files
echo "Copying Debug lib: $buildDir/Debug/libCPUPathTracing.a -> $outputDir/debug/"
mkdir -p "$outputDir/Debug"
cp -f "$buildDir/Debug/libCPUPathTracing.a" "$outputDir/debug/"

echo "Copying Release lib: $buildDir/Release/libCPUPathTracing.a -> $outputDir/bin/"
mkdir -p "$outputDir/bin"
cp -f "$buildDir/Release/libCPUPathTracing.a" "$outputDir/bin/"

echo "Export completed!" 