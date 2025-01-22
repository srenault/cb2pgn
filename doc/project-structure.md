# Project Structure

## Core Library (`jni/`)
The core C++ library that handles ChessBase file conversion.

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

- `nativecb.cpp` - Main JNI interface implementation

## Build System
- `CMakeLists.txt` - Main CMake configuration
  - Configures build for AWS Lambda environment
  - Sets up all dependencies and components
  - Manages library linking

- `build.sh` - Build script for easy compilation
- `Dockerfile` - Container definition for Amazon Linux 2
- `docker-compose.yml` - Development environment setup

## Documentation (`doc/`)
- `architecture.md` - System architecture design
- `project-status.md` - Project progress tracking
- `project-structure.md` - This file

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