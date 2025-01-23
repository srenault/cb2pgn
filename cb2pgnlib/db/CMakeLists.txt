file(GLOB DB_SOURCES "*.cpp" "cbh/*.cpp" "sci/*.cpp")
file(GLOB DB_HEADERS "*.h" "cbh/*.h" "sci/*.h")

add_library(db STATIC ${DB_SOURCES} ${DB_HEADERS})

target_include_directories(db PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/..  # For sys directory
    ${CMAKE_CURRENT_SOURCE_DIR}/cbh  # For cbh_codec.h
    ${CMAKE_CURRENT_SOURCE_DIR}/sci  # For sci_codec.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../universalchardet  # For nsUniversalDetector.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../util/libTeXt  # For T_Controller.h and T_TokenP.h
)

target_link_libraries(db PUBLIC
    mstl
    util
    universalchardet
) 