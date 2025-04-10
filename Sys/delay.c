#include "delay.h"

/**
 * @brief 微秒级延时
 * 
 * @param xus 延时时长, 范围：0~233015
 */
void delay_us(uint32_t xus){

    SysTick->LOAD = (SystemCoreClock/1000000) * xus;                    //设置定时器重装值
    SysTick->VAL = 0x00;                                                //清除当前计数值
    SysTick->CTRL = 0x00000005;                                         //设置时钟源为HCLK，启动定时器
    while(!(SysTick->CTRL & 0x00010000));                               //等待计数到0
    SysTick->CTRL = 0x00000004;                                         //关闭定时器
}

/**
 * @brief 毫秒级延时
 * 
 * @param xms 延时时长, 范围: 0~4294967295
 */
void delay_ms(uint32_t xms){

    while(xms --){
        delay_us(1000);
    }
}
 
/**
 * @brief 秒级延时
 * 
 * @param xs 延时时长, 范围: 0~4294967295
 */
void delay_s(uint32_t xs){
    
    while(xs --){
        
        delay_ms(1000);
    }
}
