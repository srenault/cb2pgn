cmake_minimum_required(VERSION 3.10)
project(cb2pgn)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable PIC for all targets
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Build cb2pgnlib first
add_subdirectory(cb2pgnlib)

# Set CB2PGNLIB_DIR to point to the build directory
set(CB2PGNLIB_DIR ${CMAKE_BINARY_DIR}/cb2pgnlib)

# Now build the JNI wrapper
add_subdirectory(jni)

# Build the CGO wrapper
add_subdirectory(cgo)