file(GLOB HYPHENATE_SOURCES "*.cpp")
file(GLOB HYPHENATE_HEADERS "*.h")

add_library(hyphenate STATIC ${HYPHENATE_SOURCES} ${HYPHENATE_HEADERS})

target_include_directories(hyphenate PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../../sys
)

target_link_libraries(hyphenate
    PRIVATE
        mstl
) 