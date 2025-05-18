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
SET(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/target")

project(${CMAKE_PROJECT_NAME})
message(STATUS "FRAMEWORK_NAME: ${CMAKE_PROJECT_NAME}")

#告诉CMake 需要支持C 和 汇编
enable_language(C ASM)

add_subdirectory(lib)
add_subdirectory(src/app)

if((CMAKE_C_STANDARD EQUAL 90) OR (CMAKE_C_STANDARD EQUAL 99))
    message(ERROR "Generated code requires C11 or higher")
endif()

INSTALL(TARGETS ${CMAKE_PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

