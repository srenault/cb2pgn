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

### CGO Support
    Implement a C++ wrapper for the CGO bindings to expose core functionality to Go.
    The interface exposed to Go should be the same as the JNI interface.
    Update build.sh so it builds both the JNI and CGO wrappers.
    The CGO wrapper should have it's own folder and CMakeLists.txt and depends on `cb2pgnlib`.

### CGO testing
- Add a jni directory in test/ to isolate the JNI test program.
- The data in test/ should remain there.
- Add a test program for the CGO wrapper in test/cgo directory. 
- The data in test/cgo should be the same as in test/jni.
- The test program should be setup in a similar way as the JNI test program.

## In Progress 🔄