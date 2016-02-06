
#include "Sys.h"
#include "Led.h"
#include "Battery.h"
#include "Com.h"
#include "Delay.h"
#include "Timer.h"

int main( void ) {
    SysInit();
    LedInit();
    BatteryInit();
    ComInit();
    TimerInit();
    INTEN
    while(1) {
        if(TimerGetTimeFlag() > 5) {
            TimerClearTimeFlag();
            BattertSleep();
        }
        if(ComWatchGetFlag() == 0x80) {
            ComWatchClearFlag();
            TimerClearTimeFlag();
            BattertOpen();
            if(ComWatchGetData(0) != 0x00) {
                BattertOpen();
            }
            switch(ComWatchGetData(0)) {
                case front:
                    switch(ComWatchGetData(1)) {
                        case add_stal:ComRearSendCmd(add_stal,0x00,0x00,0x00);break;
                        case sub_stal:ComRearSendCmd(sub_stal,0x00,0x00,0x00);break;
                        case add_setp:ComRearSendCmd(add_setp,0x00,0x00,0x00);break;
                        case sub_setp:ComRearSendCmd(sub_setp,0x00,0x00,0x00);break;
                        case set_inti:ComRearSendCmd(set_inti,0x00,0x00,0x00);break;
                    }
                break;
                case behind:
                    switch(ComWatchGetData(1)) {
                        case exchange_stal: ComBehindSendCmd(exchange_stal,0x00,0x00,0x00);break;
                        case add_setp:ComBehindSendCmd(add_setp,0x00,0x00,0x00);break;
                        case sub_setp:ComBehindSendCmd(sub_setp,0x00,0x00,0x00);break;
                        case set_inti:ComBehindSendCmd(set_inti,0x00,0x00,0x00);break;
                    }
                break;
                default:break;
            }
        }
        if(ComRearGetFlag() == 0x80) {
            ComRearClearFlag();
            switch(ComRearGetData(0)) {
                case dce_gear:ComWatchSendCmd(behind,dce_gear,ComRearGetData(1),0x00);break;
            }
        }
        if(ComBehindGetFlag() == 0x80) {
            ComBehindClearFlag();
            switch(ComBehindGetData(0)) {
                case dce_gear:ComWatchSendCmd(front,dce_gear,ComBehindGetData(1),0x00);break;
            }
        }
    }
}
