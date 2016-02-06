

#include "Battery.h"
#include "Led.h"
#include "Delay.h"

#define BATTERY_EN PD_ODR_ODR5

void BatteryInit(void) {
    PD_DDR_DDR5 = 1;
    PD_CR1_C15 = 1;
    PD_CR2_C25 = 0;
    
    PD_DDR_DDR6 = 0;
    PD_CR1_C16 = 0;
    PD_CR2_C26 = 0;
    
    ADC_CSR &= ~BIT(6);
	ADC_CSR &= ~BIT(4);
	ADC_CR1 |= BIT(1);
	ADC_CR2 |= BIT(1);
	ADC_TDRL = 0x01;
    
    BATTERY_EN = 1;
}

static u8 sleep_bit = 0;

void BattertSleep(void) {
    LedSet(1);
    BATTERY_EN = 0;
    sleep_bit = 1;
    DelayMs(100);
    MCUSLEEP
}

void BattertOpen(void) {
    if(sleep_bit == 1) {
        sleep_bit = 0;
        LedSet(0);
        BATTERY_EN = 1;
    }
}

float BattertGetVolate(u8 chx) {
    float volate = 0;
    u16 ad_value;
    u8 ad_h = 0;
    u8 ad_l = 0;
	u8 i;
	ADC_CSR = chx;
	ADC_CR1 = 0x01; // CR1 �Ĵ��������λ��1��ʹ��ADC ת��
	for(i=0;i<100;i++); // ��ʱһ��ʱ�䣬����7uS����֤ADC ģ����ϵ����
	ADC_CR1 = ADC_CR1 | 0x01; // �ٴν�CR1 �Ĵ��������λ��1
	while((ADC_CSR & 0x80) == 0); // �ȴ�ADC ����
    ad_h = ADC_DRH;
    ad_l = ADC_DRL;
	ad_value = (ad_h<<8) + ad_l;
    volate = (3.3*ad_value)/0xffff;
    return volate;
}

