set(INCLUDE_DIR 
    ${CMAKE_CURRENT_LIST_DIR}/inc
)

file(GLOB SOURCES_FILE
    ${CMAKE_CURRENT_LIST_DIR}/src/*.c
)

add_library(sys STATIC ${SOURCES_FILE})
target_include_directories(sys PUBLIC ${INCLUDE_DIR})
target_link_libraries(sys PRIVATE
    fwlib
)
