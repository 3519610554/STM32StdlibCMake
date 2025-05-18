#include "main.h"
#include "delay.h"
#include "timer.h"
#include "debug.h"

uint16_t tx_Timer = 0;

int main(void){

    NVIC_Config();
    timer_Init();
    U1_Init(115200);
    timer_loading(&tx_Timer, 2000);

    while(1){
        if (timer_get_sub(tx_Timer) == 0){
            debug_Printf("你好 CMake\r\n");
            timer_loading(&tx_Timer, 2000);
        }
        if (U1CB.URxDataIN != U1CB.URxDataOUT){
            debug_Printf("本次接收了%d字节数据\r\n", U1CB.URxDataOUT->end - U1CB.URxDataOUT->start + 1);
            debug_Printf("%s\r\n", U1CB.URxDataOUT->start);
            U1CB.URxDataOUT ++;
            if (U1CB.URxDataOUT == U1CB.URxDataEND){
                U1CB.URxDataOUT = &U1CB.URxDataPtr[0];
            }

        }
    }
}
