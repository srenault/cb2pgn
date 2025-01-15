cmake_minimum_required(VERSION 3.10)
project(cb2pgn)

# Options
option(BUILD_LAMBDA "Build for AWS Lambda" ON)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable PIC for all targets
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Find JNI
find_package(JNI REQUIRED)

# Add subdirectories for all components
add_subdirectory(jni/mstl)
add_subdirectory(jni/db)
add_subdirectory(jni/util)
add_subdirectory(jni/zlib)
add_subdirectory(jni/minizip)
add_subdirectory(jni/zzip)
add_subdirectory(jni/universalchardet)

# Find LZO package
find_package(PkgConfig REQUIRED)
pkg_check_modules(LZO lzo2)
if(NOT LZO_FOUND)
    # Fallback to manual library detection
    find_library(LZO_LIBRARIES NAMES lzo2 lzo)
    find_path(LZO_INCLUDE_DIRS NAMES lzo/lzo1x.h)
    if(NOT LZO_LIBRARIES OR NOT LZO_INCLUDE_DIRS)
        message(FATAL_ERROR "LZO library not found. Please install lzo-devel or liblzo2-dev package.")
    endif()
endif()

# Main library target
add_library(cb2pgn SHARED
    jni/nativecb.cpp
)

# Link dependencies
target_link_libraries(cb2pgn
    PRIVATE
        mstl
        db
        util
        zlib
        minizip
        zzip
        universalchardet
        ${LZO_LIBRARIES}
        ${JAVA_JVM_LIBRARY}
)

# Include directories
target_include_directories(cb2pgn
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/jni
        ${LZO_INCLUDE_DIRS}
        ${JNI_INCLUDE_DIRS}
)

# Set library output name
set_target_properties(cb2pgn PROPERTIES
    OUTPUT_NAME "cb2pgn"
    PREFIX "lib"
)

# Lambda-specific settings
if(BUILD_LAMBDA)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
endif() 