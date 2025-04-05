#include "sys.h"
#include "Debug.h"
#include "Timer.h"
#include <stddef.h>

extern char __heap_start;  /* 从链接脚本导入 */
extern char __heap_limit;  /* 从链接脚本导入 */

static char *heap_end = NULL;

void *_sbrk(int incr) {
    char *prev_heap_end;

    if (heap_end == NULL) {
        heap_end = &__heap_start;  // 确保 `heap_end` 从正确的地址开始
    }

    prev_heap_end = heap_end;
    if (heap_end + incr > &__heap_limit) {
        // 超出堆的限制
        return (void *)-1;
    }

    heap_end += incr;
    return (void *)prev_heap_end;
}

/**
 * @brief 中断通道初始化
 * 
 */
void NVIC_Config(void){

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

    // 全局时间
    Timer_IRQ_Init(NVIC_InitStructure);

    // 串口
    Serial_IRQ_Init(NVIC_InitStructure);
}
