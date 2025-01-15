file(GLOB ZLIB_SOURCES "*.c")
file(GLOB ZLIB_HEADERS "*.h")

add_library(zlib STATIC ${ZLIB_SOURCES} ${ZLIB_HEADERS})

target_include_directories(zlib PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
) 