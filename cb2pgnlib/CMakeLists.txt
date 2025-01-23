cmake_minimum_required(VERSION 3.10)
project(cb2pgnlib_root)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable PIC for all targets
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Add subdirectories for all components
add_subdirectory(mstl)
add_subdirectory(db)
add_subdirectory(util)
add_subdirectory(zlib)
add_subdirectory(minizip)
add_subdirectory(zzip)
add_subdirectory(universalchardet)

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

# Create the composite shared library
add_library(cb2pgnlib SHARED cb2pgnlib.cpp)  # Need a dummy source file for shared library

# Link all dependencies
target_link_libraries(cb2pgnlib
    PUBLIC  # Changed to PUBLIC so dependents can access these libraries
        mstl
        db
        util
        zlib
        minizip
        zzip
        universalchardet
        ${LZO_LIBRARIES}
)

# Include directories
target_include_directories(cb2pgnlib
    PUBLIC  # Changed to PUBLIC to expose headers to dependents
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${LZO_INCLUDE_DIRS}
)

# Set library output name
set_target_properties(cb2pgnlib PROPERTIES
    OUTPUT_NAME "cb2pgnlib"
    PREFIX "lib"
)

# Lambda-specific settings
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")