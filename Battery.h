
#ifndef BATTERY_H 
#define BATTERY_H

#include "Type.h"

void BatteryInit(void);
float BattertGetVolate(u8 chx);
void BattertSleep(void);
void BattertOpen(void);

#endif

