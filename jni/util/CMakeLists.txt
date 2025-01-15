file(GLOB UTIL_SOURCES "*.cpp")
file(GLOB UTIL_HEADERS "*.h")

# Add libhyphenate subdirectory
add_subdirectory(libhyphenate)

add_library(util STATIC ${UTIL_SOURCES} ${UTIL_HEADERS})

target_include_directories(util PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/..  # For sys directory
    ${CMAKE_CURRENT_SOURCE_DIR}/libhyphenate  # Correct path to Hyphenator.h
    ${CMAKE_CURRENT_SOURCE_DIR}/libTeXt  # Add libTeXt directory
    ${CMAKE_CURRENT_SOURCE_DIR}/../sys
)

target_link_libraries(util
    PRIVATE
        mstl
        zlib
        minizip
        zzip
        hyphenate  # Link against libhyphenate
) 