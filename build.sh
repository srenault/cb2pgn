#!/bin/bash
# build.sh

set -e

# Create build directory
mkdir -p build

# Build and copy the library
echo "Building cb2pgn library..."
docker compose up --build builder

echo "Done! Library is in build/libcb2pgn.so" 
echo "Done! Library is in build/libopenchessbase_jni.so" 