#include "sys.h"
#include "Debug.h"
#include "delay.h"
#include "bsp_led.h"
#include "Timer.h"
#include <stdio.h>

uint8_t rx_buff[SERIAL_LEN_MAX];
uint16_t led_Timer = 0;


int main(void){

    NVIC_Config();
    Serial_Init(115200);
    led_Init();
    Timer_Init();
    Debug_Printf("STM32 模板实验\r\n");
    while(1){
        if (Timer_get_sub(led_Timer) == 0){
            LED_TOGGLE(LED_PIN);
            Debug_Printf("你好世界\r\n");
            Timer_loading(&led_Timer, 500);
        }
        if (Serial_ReadData(rx_buff)){
            Debug_Printf("%s\r\n", rx_buff);
        }
    }
}
