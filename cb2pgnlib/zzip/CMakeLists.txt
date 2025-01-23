file(GLOB ZZIP_SOURCES "*.c")
file(GLOB ZZIP_HEADERS "*.h")

add_library(zzip STATIC ${ZZIP_SOURCES} ${ZZIP_HEADERS})

target_include_directories(zzip PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(zzip PUBLIC
    zlib
) 