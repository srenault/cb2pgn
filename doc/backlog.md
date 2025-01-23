# Project Backlog

## Done ✅

### Core Library
- Convert Android.mk to CMakeLists.txt
- Add missing C++ libraries (LZO, JNI)
- Adapt C++ code for Linux environment
- Set up Docker build environment with Amazon Linux 2
- Implement Java test program
- Verify JNI integration

### Build System
- Create Dockerfile for Amazon Linux 2
- Set up docker-compose for development
- Configure CMake build system
- Add Lambda build configuration
- Create build automation script

## In Progress 🔄

### CGO Implementation
    Implement CGO bindings to expose core functionality to Go.
    Refactor build system to produce a single shared library (`libcb2pgn.so`).
    Update JNI and CGO implementations to link against the shared library.
    Split Docker configuration into separate Java and Go build environments.
