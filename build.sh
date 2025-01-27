#!/bin/bash
# build.sh

set -e

# Create build directory
mkdir -p build

# Build and copy the library
echo "Building cb2pgn library..."
docker compose up --build builder

echo "Done! Libraries built:"
echo " - build/libcb2pgn.so"
echo " - build/libopenchessbase_jni.so"
echo " - build/libopenchessbase_cgo.so" 