#include "bsp_led.h"

void led_Init(void){

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;   
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;                   
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;            
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;          
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;         
    GPIO_Init(GPIOC, &GPIO_InitStructure);  

    LED_OFF(LED_PIN);   
}
