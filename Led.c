

#include "Led.h"

#define LED_BIT PC_ODR_ODR5

void LedInit(void) {
    PC_DDR_DDR5 = 1;
    PC_CR1_C15 = 1;
    PC_CR2_C25 = 0;
}


void LedSet(u8 cmd) {
    LED_BIT = cmd;
}
/***********************************************变量声明*****************************************************
* 功    能: 模式LED闪烁次数标志位  
* 作    者: by lhb_steven
* 日    期: 2016/3/17
************************************************************************************************************/ 
static u8 led_mode_flag = 2;
/**********************************************函数定义***************************************************** 
* 函数名称: void LedSetModeFlicker(u8 count) 
* 输入参数: u8 count 
* 返回参数: void  
* 功    能: 设置状态灯闪烁  count闪烁几次  
* 作    者: by lhb_steven
* 日    期: 2016/3/17
************************************************************************************************************/ 
void LedSetModeFlicker(u8 count) { 
    led_mode_flag = count;
}
/**********************************************函数定义***************************************************** 
* 函数名称: void LedTimeService(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能: LED动画的服务函数  
* 作    者: by lhb_steven
* 日    期: 2016/3/16
************************************************************************************************************/ 
void LedTimeService(void) { 
    static u16 time_count = 0;
    if(time_count < 20000) {
        time_count++;
    } else {
        time_count = 0;
        if(led_mode_flag > 0) {
            static u8 bit = 0;            
            if(bit == 0) {
                bit = 1;
                led_mode_flag--;
            } else {
                bit = 0;
            }
            LED_BIT = bit;
        }
    }
}