#ifndef _DEBUG_H
#define _DEBUG_H

#include "stm32l1xx.h"
#include <stdarg.h>

#define SERIAL_LEN_MAX      (128-1)

typedef struct{
    // 串口发送缓存区
    uint8_t buff[SERIAL_LEN_MAX];   
    // 串口发送忙碌标志位   1 忙碌      0 空闲
    uint8_t busy;                   
}_USART_TX_;

typedef struct{
    // 串口接收缓存区
    uint8_t buff[SERIAL_LEN_MAX];   
    // 串口接收完成标志位   1 接收完成  0 接收未完成
    uint8_t finish;        
    // 串口接收长度         
    uint8_t len;                    
}_USART_RX_;

void    Serial_Init(uint32_t bound);
void    Serial_IRQ_Init(NVIC_InitTypeDef NVIC_InitStructure);
void    Serial_DMA_Send(uint8_t *str,uint16_t len);
uint8_t Serial_ReadData(uint8_t *rx_buff);
void    Debug_Printf(char *format, ...);

#endif
