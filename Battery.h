
#ifndef BATTERY_H 
#define BATTERY_H

#include "Type.h"

void BatteryInit(void);
float BattertGetVolate(u8 chx);
void BattertSleep(void);
void BattertOpen(void);
void BattertGet(void);
u8 BattertGetLevel(void);


void BatterSetFlag(u8 data);
u8 BatterGetFlag(void);

#endif

