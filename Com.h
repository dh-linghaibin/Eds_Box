

#ifndef COM_H
#define COM_H

#include "Type.h"

void ComInit(void);
u8 ComWatchGetData(u8 num);
u8 ComWatchGetFlag(void);
void ComWatchClearFlag(void);
void ComWatchSendCmd(u8 cmd,u8 par1,u8 par2,u8 par3);

u8 ComRearGetData(u8 num);
u8 ComRearGetFlag(void);
void ComRearClearFlag(void);
void ComRearSendCmd(u8 cmd,u8 par1,u8 par2,u8 par3);

u8 ComBehindGetData(u8 num);
u8 ComBehindGetFlag(void);
void ComBehindClearFlag(void);
void ComBehindSendCmd(u8 cmd,u8 par1,u8 par2,u8 par3);

#endif
