cmake_minimum_required(VERSION 3.22)
# Enable CMake support for ASM and C languages
enable_language(C ASM)
# STM32CubeMX generated symbols (macros)
set(MX_Defines_Syms 
    STM32L1XX_MD 
	USE_STDPERIPH_DRIVER
    $<$<CONFIG:Debug>:DEBUG>
)

# STM32CubeMX generated include paths
set(MX_Include_Dirs
    ${CMAKE_SOURCE_DIR}/Hardware
    ${CMAKE_SOURCE_DIR}/Sys
    ${CMAKE_SOURCE_DIR}/User
    ${CMAKE_SOURCE_DIR}/Libraries/CMSIS/startup
    ${CMAKE_SOURCE_DIR}/Libraries/CMSIS
    ${CMAKE_SOURCE_DIR}/Libraries/STM32L1xx_StdPeriph_Driver/inc
)

# STM32CubeMX generated application sources
file(GLOB MX_Application_Src
    ${CMAKE_SOURCE_DIR}/Hardware/*.c
    ${CMAKE_SOURCE_DIR}/Sys/*.c
    ${CMAKE_SOURCE_DIR}/User/*.c
)
# STM32 HAL/LL Drivers
file(GLOB STM32_Drivers_Src
    ${CMAKE_SOURCE_DIR}/Libraries/CMSIS/startup/startup_stm32l1xx_md.s
    ${CMAKE_SOURCE_DIR}/Libraries/CMSIS/*.c
    ${CMAKE_SOURCE_DIR}/Libraries/STM32L1xx_StdPeriph_Driver/src/*.c
)

# Link directories setup
set(MX_LINK_DIRS

)
# Project static libraries
set(MX_LINK_LIBS 
    STM32_Drivers
    
)

# Interface library for includes and symbols
add_library(stm32cubemx INTERFACE)
target_include_directories(stm32cubemx INTERFACE ${MX_Include_Dirs})
target_compile_definitions(stm32cubemx INTERFACE ${MX_Defines_Syms})

# Create STM32_Drivers static library
add_library(STM32_Drivers OBJECT)
target_sources(STM32_Drivers PRIVATE ${STM32_Drivers_Src})
target_link_libraries(STM32_Drivers PUBLIC stm32cubemx)

# Add STM32CubeMX generated application sources to the project
target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${MX_Application_Src})

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE ${MX_LINK_DIRS})

# Add libraries to the project
target_link_libraries(${CMAKE_PROJECT_NAME} ${MX_LINK_LIBS})

# Add the map file to the list of files to be removed with 'clean' target
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES ADDITIONAL_CLEAN_FILES ${CMAKE_PROJECT_NAME}.map)

# Validate that STM32CubeMX code is compatible with C standard
if((CMAKE_C_STANDARD EQUAL 90) OR (CMAKE_C_STANDARD EQUAL 99))
    message(ERROR "Generated code requires C11 or higher")
endif()
