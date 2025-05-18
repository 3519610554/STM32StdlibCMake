#ifndef _BSP_LED_H
#define _BSP_LED_H

#include "sys.h"

#define LED_PIN                 GPIO_Pin_13
#define LED_PORT                GPIOC

#define LED_TOGGLE(x)           {LED_PORT->ODR ^= x;}
#define LED_ON(x)               GPIO_WriteBit(LED_PORT, x, Bit_RESET)
#define LED_OFF(x)              GPIO_WriteBit(LED_PORT, x, Bit_SET)

void led_Init(void);

#endif
