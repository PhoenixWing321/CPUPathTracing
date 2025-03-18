#!/bin/bash

# Check if my.config exists
if [ ! -f "my.config" ]; then
    echo "my.config is not found!"
    exit 1
fi

# Read configuration file
# Filter out comments and empty lines, then process key-value pairs
while IFS='=' read -r key value || [ -n "$key" ]; do
    # Skip comments and empty lines
    [[ $key =~ ^[[:space:]]*# ]] && continue
    [[ -z $key ]] && continue
    
    # Trim whitespace and remove carriage returns
    key=$(echo "$key" | tr -d '\r' | xargs)
    value=$(echo "$value" | tr -d '\r' | xargs)
    
    # Evaluate the value to expand environment variables
    eval "expanded_value=\"$value\""
    
    # Export variables
    export "$key=$expanded_value"
done < "my.config"

echo "ROOT_DIR_BUILD: $ROOT_DIR_BUILD"
echo "ROOT_DIR_EXPORT_LIB: $ROOT_DIR_EXPORT_LIB"

# Copy files
echo "Copying Debug lib: $ROOT_DIR_BUILD/Debug/libCPUPathTracing.a -> $ROOT_DIR_EXPORT_LIB/Debug/"
mkdir -p "$ROOT_DIR_EXPORT_LIB/Debug"
cp -f "$ROOT_DIR_BUILD/Debug/libCPUPathTracing.a" "$ROOT_DIR_EXPORT_LIB/Debug/"

echo "Copying Release lib: $ROOT_DIR_BUILD/Release/libCPUPathTracing.a -> $ROOT_DIR_EXPORT_LIB/bin/"
mkdir -p "$ROOT_DIR_EXPORT_LIB/bin"
cp -f "$ROOT_DIR_BUILD/Release/libCPUPathTracing.a" "$ROOT_DIR_EXPORT_LIB/bin/"

echo "Export completed!" 