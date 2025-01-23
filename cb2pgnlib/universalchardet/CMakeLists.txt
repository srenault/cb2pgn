file(GLOB CHARDET_SOURCES "*.cpp")
file(GLOB CHARDET_HEADERS "*.h")

add_library(universalchardet STATIC ${CHARDET_SOURCES} ${CHARDET_HEADERS})

target_include_directories(universalchardet PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
) 