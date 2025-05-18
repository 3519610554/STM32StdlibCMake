enable_language(C ASM)

set(FWLIB_DEFINE 
    STM32L1XX_MD 
	USE_STDPERIPH_DRIVER
)

set(INCLUDE_DIR 
    ${CMAKE_CURRENT_LIST_DIR}/CMSIS/startup
    ${CMAKE_CURRENT_LIST_DIR}/CMSIS
    ${CMAKE_CURRENT_LIST_DIR}/STM32L1xx_StdPeriph_Driver/inc
)

file(GLOB_RECURSE SOURCES_FILE
    ${CMAKE_CURRENT_LIST_DIR}/CMSIS/startup/startup_stm32l1xx_md.s
    ${CMAKE_CURRENT_LIST_DIR}/*.c
)

# 排除不想要的文件
# list(FILTER SOURCES_FILE EXCLUDE REGEX ".*stm32f4xx_(dma2d|fmc|ltdc)\\.c$")

add_library(fwlib STATIC ${SOURCES_FILE})
target_compile_definitions(fwlib PUBLIC ${FWLIB_DEFINE})
target_include_directories(fwlib PUBLIC ${INCLUDE_DIR})

include_directories(${INCLUDE_DIR})
