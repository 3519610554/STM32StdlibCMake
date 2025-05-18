#ifndef _TIMER_H
#define _TIMER_H

#include "sys.h"

void        Timer_Init(void);
void        Timer_IRQ_Init(NVIC_InitTypeDef NVIC_InitStructure);
uint16_t    Timer_get(void);
uint16_t    Timer_get_sub(uint16_t c);
void        Timer_loading(uint16_t *loading_time, uint16_t time);

#endif
