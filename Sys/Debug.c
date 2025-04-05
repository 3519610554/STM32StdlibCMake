#include "Debug.h"
#include <stdio.h>
#include <string.h>

#define WAKE_UP_THE_SERIAL_PORT

#ifdef WAKE_UP_THE_SERIAL_PORT

#define USART_CLK_CMD           RCC_APB2PeriphClockCmd
#define USART_CLK               RCC_APB2Periph_USART1
#define USART                   USART1     
#define USART_IRQ               USART1_IRQn
#define USART_IRQHandler        USART1_IRQHandler
#define USART_DMA_CLK_CMD       RCC_AHBPeriphClockCmd
#define USART_DMA_CLK           RCC_AHBPeriph_DMA1
#define USART_DMA               DMA1_Channel4
#define USART_DMA_IT            DMA1_FLAG_TC4
#define USART_DMA_IRQ           DMA1_Channel4_IRQn
#define USART_DMA_IRQHandler    DMA1_Channel4_IRQHandler

#define GPIO_CLK_CMD            RCC_AHBPeriphClockCmd
#define GPIO_CLK                RCC_AHBPeriph_GPIOA
#define GPIO_PORT               GPIOA
#define GPIO_AF                 GPIO_AF_USART1
#define GPIO_TX_PIN             GPIO_Pin_9
#define GPIO_TX_AF_PIN          GPIO_PinSource9
#define GPIO_RX_PIN             GPIO_Pin_10
#define GPIO_RX_AF_PIN          GPIO_PinSource10

static _USART_TX_ serial_tx = {0};
static _USART_RX_ serial_rx = {0};

#endif

/**
 * @brief 串口 配置
 * 
 * @param bound 波特率
 */
void Serial_Config(uint32_t bound){

    #ifdef WAKE_UP_THE_SERIAL_PORT

    GPIO_CLK_CMD(GPIO_CLK, ENABLE);  // 使能GPIOA时钟
    USART_CLK_CMD(USART_CLK, ENABLE); // 使能USART1时钟

    // USART1端口配置
    GPIO_PinAFConfig(GPIO_PORT,GPIO_TX_AF_PIN,GPIO_AF);
    GPIO_PinAFConfig(GPIO_PORT,GPIO_RX_AF_PIN,GPIO_AF);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_TX_PIN | GPIO_RX_PIN;   
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;                   
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;            
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;          
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;         
    GPIO_Init(GPIO_PORT, &GPIO_InitStructure);              

    // USART 初始化设置
    USART_InitTypeDef USART_InitStructure;
    USART_InitStructure.USART_BaudRate = bound;                                     // 波特率设置
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;                     // 字长为8位数据格式
    USART_InitStructure.USART_StopBits = USART_StopBits_1;                          // 一个停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;                             // 无奇偶校验位
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 无硬件数据流控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;                 // 收发模式
    USART_Init(USART, &USART_InitStructure);                                        // 初始化串口

    USART_ITConfig(USART, USART_IT_RXNE, ENABLE);
    USART_ITConfig(USART, USART_IT_IDLE, ENABLE);

    USART_Cmd(USART, ENABLE); // 使能串口

    #endif
}

/**
 * @brief 串口DMA 配置
 * 
 */
void Serial_DMA_Config(void){
	
    #ifdef WAKE_UP_THE_SERIAL_PORT

	USART_DMA_CLK_CMD(USART_DMA_CLK,ENABLE);

    DMA_InitTypeDef DMA_InitStructure;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART->DR;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)serial_tx.buff;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
	DMA_InitStructure.DMA_BufferSize = SERIAL_LEN_MAX;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_Init(USART_DMA, &DMA_InitStructure);
    DMA_ITConfig(USART_DMA, DMA_IT_TC, ENABLE);  

    #endif
}

/**
 * @brief 串口初始化
 * 
 * @param bound 波特率
 */
void Serial_Init(uint32_t bound){

    #ifdef WAKE_UP_THE_SERIAL_PORT
    Serial_Config(bound);
    USART_DMACmd(USART, USART_DMAReq_Tx, ENABLE);
    Serial_DMA_Config();
    #endif
}

/**
 * @brief 串口中断通道初始化
 * 
 * @param NVIC_InitStructure 中断结构体
 */
void Serial_IRQ_Init(NVIC_InitTypeDef NVIC_InitStructure){

    #ifdef WAKE_UP_THE_SERIAL_PORT
    NVIC_InitStructure.NVIC_IRQChannel = USART_DMA_IRQ;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = USART_IRQ;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_Init(&NVIC_InitStructure);
    #endif
}

/**
 * @brief 串口DMA发送
 * 
 * @param str   字符串
 * @param ndtr  长度
 */
void Serial_DMA_Send(uint8_t *str,uint16_t len) {

    #ifdef WAKE_UP_THE_SERIAL_PORT
    while(serial_tx.busy){
        
    }
	DMA_Cmd(USART_DMA, DISABLE);                        //关闭DMA传输
    memcpy(serial_tx.buff, str, len);                   //复制传输数据
	DMA_SetCurrDataCounter(USART_DMA,len);              //数据传输量  
	DMA_Cmd(USART_DMA, ENABLE);                         //开启DMA传输 
	serial_tx.busy = 1;                                 //DMA数据忙碌置一
    #endif
}

/**
 * @brief Debug 打印函数与printf用法一样
 * 
 * @param format    指定要显示的格式化字符串，范围：ASCII码可见字符组成的字符串
 * @param ...       格式化字符串参数列表
 */
void Debug_Printf(char *format, ...){
    #ifdef WAKE_UP_THE_SERIAL_PORT
	char String[SERIAL_LEN_MAX];						// 定义字符数组
    uint8_t str_len = 0;                                // 转化后字符串长度
	va_list arg;							            // 定义可变参数列表数据类型的变量arg
	va_start(arg, format);					            // 从format开始，接收参数列表到arg变量
	str_len = vsprintf(String, format, arg);			// 使用vsprintf打印格式化字符串和参数列表到字符数组中
	va_end(arg);							            // 结束变量arg

    Serial_DMA_Send((uint8_t *)String, str_len);
    #endif
}

/**
 * @brief 读取串口数据
 * 
 * @param rx_buff   读取数组
 * @return uint8_t  0   串口无数据      1   串口有数据
 */
uint8_t Serial_ReadData(uint8_t *rx_buff){

    #ifdef WAKE_UP_THE_SERIAL_PORT
    if (!serial_rx.finish)
        return 0;
    serial_rx.finish = 0;
    memcpy(rx_buff, serial_rx.buff, sizeof(serial_rx.buff));
    return 1;
    #else
    return 0;
    #endif
}

/**
 * @brief DMA 中断
 * 
 */
void USART_DMA_IRQHandler(void){

    #ifdef WAKE_UP_THE_SERIAL_PORT
    if(DMA_GetITStatus(USART_DMA_IT) != RESET)   
    {  
        /* 清除标志位 */
        DMA_ClearFlag(USART_DMA_IT);  
        /* 关闭DMA */
        DMA_Cmd(USART_DMA,DISABLE);
        serial_tx.busy = 0;
    } 
    #endif 
}

/**
 * @brief 串口中断
 * 
 */
void USART_IRQHandler(void){

    #ifdef WAKE_UP_THE_SERIAL_PORT
    if (USART_GetITStatus(USART, USART_IT_RXNE) != RESET){
        serial_rx.buff[serial_rx.len ++] = USART_ReceiveData(USART);
        USART_ClearITPendingBit(USART, USART_IT_RXNE);
        serial_rx.len %= SERIAL_LEN_MAX;
    }
    else if (USART_GetITStatus(USART, USART_IT_IDLE) != RESET){

        serial_rx.buff[serial_rx.len] = '\0';
        serial_rx.finish = 1;
        serial_rx.len = 0;
        USART_ReceiveData(USART);
    }
    #endif
}
