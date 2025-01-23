cmake_minimum_required(VERSION 3.10)
project(cb2pgn_jni)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find JNI package
find_package(JNI REQUIRED)

# If building as part of the main project, we can use the library directly
if(TARGET cb2pgnlib)
    set(CB2PGNLIB_LIBRARY cb2pgnlib)
    set(CB2PGNLIB_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/cb2pgnlib)
else()
    # Otherwise find the installed library
    find_library(CB2PGNLIB_LIBRARY
        NAMES cb2pgnlib libcb2pgnlib
        PATHS ${CB2PGNLIB_DIR}/lib
              ${CMAKE_PREFIX_PATH}/lib
              ${CMAKE_INSTALL_PREFIX}/lib
        DOC "The cb2pgnlib library"
    )

    if(NOT CB2PGNLIB_LIBRARY)
        message(FATAL_ERROR "cb2pgnlib not found. Please build and install cb2pgnlib first, or set CB2PGNLIB_DIR to point to its installation.")
    endif()

    # Find cb2pgnlib headers
    find_path(CB2PGNLIB_INCLUDE_DIR
        NAMES db_database.h
        PATHS ${CB2PGNLIB_DIR}/include
              ${CMAKE_PREFIX_PATH}/include
              ${CMAKE_INSTALL_PREFIX}/include
              ${CMAKE_SOURCE_DIR}/../cb2pgnlib
        DOC "The cb2pgnlib include directory"
    )

    if(NOT CB2PGNLIB_INCLUDE_DIR)
        message(FATAL_ERROR "cb2pgnlib headers not found. Please set CB2PGNLIB_DIR to point to its installation.")
    endif()
endif()

# Create JNI wrapper library
add_library(openchessbase_jni SHARED
    nativecp.cpp
)

# Link with cb2pgnlib and JNI
target_link_libraries(openchessbase_jni
    PRIVATE
        ${CB2PGNLIB_LIBRARY}
        ${JNI_LIBRARIES}
)

# Include directories
target_include_directories(openchessbase_jni
    PRIVATE
        ${JNI_INCLUDE_DIRS}
        ${CB2PGNLIB_INCLUDE_DIR}
)

# Set library output name
set_target_properties(openchessbase_jni PROPERTIES
    OUTPUT_NAME "openchessbase_jni"
    PREFIX "lib"
)