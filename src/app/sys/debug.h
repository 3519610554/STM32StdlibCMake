#ifndef _DEBUG_H
#define _DEBUG_H

#include "sys.h"
#include <stdarg.h>

#define U1_TX_SIZE          (2*1024)
#define U1_RX_SIZE          (2*1024)
#define U1_RX_MAX           256
#define U1_NUM              10

typedef struct{
    uint16_t        UxCounter;
    UCB_URxBuffptr  URxDataPtr[U1_NUM];
    UCB_URxBuffptr  *URxDataIN;
    UCB_URxBuffptr  *URxDataOUT;
    UCB_URxBuffptr  *URxDataEND;
}U1_CB;

extern U1_CB  U1CB;
extern uint8_t U1_RxBuff[U1_RX_SIZE];

void        U1_Init(uint32_t bound);
uint8_t     U1_IRQChannel(void);
void        debug_Printf(char *format, ...);

#endif
