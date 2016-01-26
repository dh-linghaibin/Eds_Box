
#include "Sys.h"
#include "Led.h"
#include "Battery.h"
#include "Com.h"
#include "Delay.h"

int main( void ) {
    SysInit();
    LedInit();
    BatteryInit();
    ComInit();
    INTEN
    while(1) {
        if(ComWatchGetFlag() == 0x80) {
            ComWatchClearFlag();
            DelayMs(300);
            ComWatchSendCmd(0x01,0x02,0x03,0x04);
            DelayMs(300);
            ComRearSendCmd(0x01,0x02,0x03,0x04);
            DelayMs(300);
            ComBehindSendCmd(0x01,0x02,0x03,0x04);
        }
    }
}
