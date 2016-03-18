

#ifndef TIMER_H
#define TIMER_H

#include "Type.h"

void TimerInit(void);
u8 TimerGetTimeFlag(void);
void TimerClearTimeFlag(void);

u8 TimerGetBatteryFlag(void);
void TimerClearBatteryFlag(void);

#endif



