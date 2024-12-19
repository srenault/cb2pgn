#!/bin/bash
set -e

# Create build directory if it doesn't exist
mkdir -p build

# Build using Docker
echo "Building cb2pgn library..."
chmod +x docker-build.sh
docker compose up --build builder

echo "Done! Library is in build/libcbvextractor.so and build/libcb2pgn_jni.so" 