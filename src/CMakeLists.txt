add_subdirectory(sys)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE 
    fwlib
    sys
    # hardware
)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR})
target_sources(${CMAKE_PROJECT_NAME} PRIVATE main.c)
