#!/bin/bash
set -e

# Build uncbv
cargo build --release --target x86_64-unknown-linux-gnu -p uncbv

# Build the uncbv JNI library
cargo build --release --target x86_64-unknown-linux-gnu -p uncbv-jni

# Create build directories
mkdir -p build
mkdir -p test/build

# Copy the libraries to the output directory
cp target/x86_64-unknown-linux-gnu/release/libcbvextractor.so build/
cp target/x86_64-unknown-linux-gnu/release/uncbv build/

# Compile Java classes
javac -d test/build test/org/chess/cb/*.java

echo "Build complete! Libraries are in build/ directory" 