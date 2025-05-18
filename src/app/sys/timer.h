# ifndef _TIMER_H
# define _TIMER_H

# include "sys.h"

void        timer_Init(void);
uint8_t     timer_GetIRQChannel(void);
uint16_t    timer_get(void);
uint16_t    timer_get_sub(uint16_t c);
void        timer_loading(uint16_t *loading_time, uint16_t time);

# endif
