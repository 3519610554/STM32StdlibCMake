# include "timer.h"

#define TIMER                   TIM7
#define TIMER_CLK_CMD           RCC_APB1PeriphClockCmd
#define TIMER_CLK               RCC_APB1Periph_TIM7
#define TIMER_IRQ               TIM7_IRQn
#define TIMER_IRQHandler        TIM7_IRQHandler


static uint16_t global_times = 0;

/**
 * @brief 全局时间初始化
 * 
 */
void timer_Init(void){

    TIM_InternalClockConfig(TIMER);

    TIMER_CLK_CMD(TIMER_CLK,ENABLE);

    TIM_TimeBaseInitTypeDef TIM_InitStructure;
    TIM_InitStructure.TIM_ClockDivision = TIM_CKD_DIV4;
    TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_InitStructure.TIM_Prescaler = 42-1;
    TIM_InitStructure.TIM_Period = 1000-1;
    TIM_InitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIMER, &TIM_InitStructure);

    TIM_ITConfig(TIMER,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIMER, ENABLE);
}

/**
 * @brief 获取全局时间中断通道
 * 
 * @return uint8_t 返回中断通道
 */
uint8_t timer_GetIRQChannel(void){

    return TIMER_IRQ;
}

/**
 * @brief 获取全局时间
 * 
 * @return uint32_t 
 */
uint16_t timer_get(void){

    return global_times;
}

/**
 * @brief 判断时间周期
 * 
 * @param c 设置的时间周期
 * @return uint32_t c与时间周期剩余的时间
 */
uint16_t timer_get_sub(uint16_t c){

    if(c > global_times)
		c -= global_times;
	else
		c = 0;
	return c;
}

/**
 * @brief 定时器时间装载
 * 
 * @param loading_time  需要装载的时间
 * @param time          设置的周期
 */
void timer_loading(uint16_t *loading_time, uint16_t time){

    *loading_time = global_times + time;
}

/**
 * @brief 中断函数
 * 
 */
void TIMER_IRQHandler(void)
{
	if(TIM_GetITStatus(TIMER,TIM_IT_Update) == SET) {   
        TIM_ClearITPendingBit(TIMER,TIM_IT_Update);
		global_times++;
	}
}
