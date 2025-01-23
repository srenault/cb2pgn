file(GLOB MINIZIP_SOURCES "*.c")
file(GLOB MINIZIP_HEADERS "*.h")

add_library(minizip STATIC ${MINIZIP_SOURCES} ${MINIZIP_HEADERS})

target_include_directories(minizip PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(minizip PUBLIC
    zlib
) 