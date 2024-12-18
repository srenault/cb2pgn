file(GLOB MSTL_SOURCES "*.cpp")
file(GLOB MSTL_HEADERS "*.h" "*.ipp")

# Remove custom stdio implementations since we're using system ones
list(REMOVE_ITEM MSTL_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/fmemopen.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/fopencookie.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/open_memstream.c"
)

add_library(mstl STATIC ${MSTL_SOURCES} ${MSTL_HEADERS})

target_include_directories(mstl PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
)

if(BUILD_LAMBDA)
    target_compile_definitions(mstl PUBLIC
        _GNU_SOURCE  # Enable GNU extensions including fopencookie
    )
endif()
  