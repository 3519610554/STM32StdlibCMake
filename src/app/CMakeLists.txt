include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/sys
    ${CMAKE_CURRENT_SOURCE_DIR}/hal
)

file(GLOB_RECURSE SRC_LIST "*.c")
file(GLOB_RECURSE HEADERS "*.h")

add_library(app STATIC ${SRC_LIST} ${HEADERS})
target_link_libraries(app PRIVATE fwlib)

add_executable(${CMAKE_PROJECT_NAME} ${SRC_LIST}) 
target_link_libraries(${CMAKE_PROJECT_NAME} fwlib)

set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES ADDITIONAL_CLEAN_FILES ${CMAKE_PROJECT_NAME}.map)

add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND arm-none-eabi-objcopy -O binary ${CMAKE_PROJECT_NAME}.elf ${CMAKE_PROJECT_NAME}.bin
    COMMENT "Generating ${CMAKE_PROJECT_NAME}.bin"
)

set(BIN_PATH "${CMAKE_SOURCE_DIR}/build/src/app")
set(SCRIPTS_PATH ${CMAKE_SOURCE_DIR}/scripts)

add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E env python ${SCRIPTS_PATH}/util_copy.py ${BIN_PATH}/${CMAKE_PROJECT_NAME}.bin ${CMAKE_INSTALL_PREFIX}
        
    COMMENT "Running Python script after build"
)

add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E env python ${SCRIPTS_PATH}/util_copy.py ${BIN_PATH}/${CMAKE_PROJECT_NAME}.elf ${CMAKE_INSTALL_PREFIX}
        
    COMMENT "Running Python script after build"
)

add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E env python ${SCRIPTS_PATH}/util_json.py ${CMAKE_BUILD_TYPE} ${CMAKE_SOURCE_DIR} ${CMAKE_INSTALL_PREFIX} ${CMAKE_PROJECT_NAME}
        
    COMMENT "Running Python script after build"
)

