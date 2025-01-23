# Project Structure

## Core Library Components

### Core Library (`cb2pgnlib/`)
The main C++ library implementation for ChessBase file conversion:

- `db/` - Database handling components
  - Move information and chess position storage
  - Database table implementations
  - Chess move sets and information

- `mstl/` - Custom STL-like implementations
  - Custom list implementation
  - Memory management utilities
  - File operations support

- `util/` - Utility functions and helpers
  - Progress tracking
  - Common utilities

- `zzip/` - Compression handling
  - ZIP file format support
  - File decompression utilities

- `zlib/` - Compression library support
- `sys/` - System-specific implementations
- `universalchardet/` - Character encoding detection
- `minizip/` - ZIP file format handling
- `cb2pgnlib.cpp` - Main library implementation

### JNI Interface (`jni/`)
Native interface layer for Java integration:
- `nativecb.cpp` - Main JNI interface implementation
- Supporting C++ components for JNI bindings
- Depends on `cb2pgnlib`

## Build System
- `CMakeLists.txt` - Main CMake configuration
  - Configures build for AWS Lambda environment
  - Sets up all dependencies and components
  - Manages library linking

- `build.sh` - Build script for easy compilation
- `docker-build.sh` - Docker-specific build script
- `Dockerfile` - Container definition for Amazon Linux 2
- `docker-compose.yml` - Development environment setup
- `run.sh` - Script for running the application

## Documentation (`doc/`)
- `architecture.md` - System architecture design
- `project-status.md` - Project progress tracking
- `project-structure.md` - This file
- `backlog.md` - Project backlog and task tracking

## Testing (`test/`)
- Java test program for JNI interface validation
- Integration tests

## Development
- `.vscode/` - VS Code configuration
- `.gitignore` - Git ignore patterns

## Build Output
- `build/` - Compilation output directory
  - Contains the compiled shared library (`libcb2pgn.so`)
  - Generated during build process 