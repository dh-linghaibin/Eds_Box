

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
