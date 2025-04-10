#include "sys.h"
#include "debug.h"
#include "Timer.h"

void NVIC_Config(void){

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

    // 全局时间中断
    NVIC_InitStructure.NVIC_IRQChannel = timer_GetIRQChannel();
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_Init(&NVIC_InitStructure);

    // 串口
    NVIC_InitStructure.NVIC_IRQChannel = U1_IRQChannel();
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStructure);
}
