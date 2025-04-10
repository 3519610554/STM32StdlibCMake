cmake_minimum_required(VERSION 3.16)

#工程名
set(CMAKE_PROJECT_NAME Demo)

#gcc-arm 工具链
include("${CMAKE_SOURCE_DIR}/scripts/gcc-arm-none-eabi.cmake")

#定 C 语言标准，这里设定的是 C11（2011 版标准）
set(CMAKE_C_STANDARD 11)            
#作用：强制使用 CMAKE_C_STANDARD 指定的标准
set(CMAKE_C_STANDARD_REQUIRED ON)
#作用：允许使用编译器的扩展特性（比如 GNU C 的 -std=gnu11）
set(CMAKE_C_EXTENSIONS ON)
#生成 compile_commands.json 文件，主要用于代码分析和智能补全
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

project(${CMAKE_PROJECT_NAME})
message(STATUS "FRAMEWORK_NAME: ${CMAKE_PROJECT_NAME}")

#告诉CMake 需要支持C 和 汇编
enable_language(C ASM)

add_executable(${PROJECT_NAME})

add_subdirectory(lib)
add_subdirectory(src)

set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES ADDITIONAL_CLEAN_FILES ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_PROJECT_NAME}.map)

if((CMAKE_C_STANDARD EQUAL 90) OR (CMAKE_C_STANDARD EQUAL 99))
    message(ERROR "Generated code requires C11 or higher")
endif()

add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND arm-none-eabi-objcopy -O binary ${CMAKE_PROJECT_NAME}.elf ${CMAKE_PROJECT_NAME}.bin
    COMMENT "Generating ${CMAKE_PROJECT_NAME}.bin"
)

add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E env python ${CMAKE_SOURCE_DIR}/scripts/OpenocdTools.py debug ${CMAKE_BUILD_TYPE} ${CMAKE_SOURCE_DIR} ${CMAKE_PROJECT_NAME}
        
    COMMENT "Running Python script after build"
)
