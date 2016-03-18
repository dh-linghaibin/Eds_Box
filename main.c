
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
        if(TimerGetTimeFlag() > 10) {
            TimerClearTimeFlag();
            BattertSleep();
        }
        if(TimerGetBatteryFlag() > 0x01) {
            TimerClearBatteryFlag();
            if(BatterGetFlag() == 0) {
                BatterSetFlag(1);
                BattertGet();
                ComWatchSendCmd(dce_powe,BattertGetLevel(),0x00,0x00);
            }
        }
        LedTimeService();
        if(ComWatchGetFlag() == 0x80) {
            ComWatchClearFlag();
            TimerClearTimeFlag();
            BattertOpen();
            BatterSetFlag(0);//可以获取电量
            if(ComWatchGetData(0) != 0x00) {
                BattertOpen();
            }
            LedSetModeFlicker(1);
            if(BattertGetLevel() > 0) {
                switch(ComWatchGetData(0)) {//电量不足
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
            } else {
                
            }
        }
        if(ComRearGetFlag() == 0x80) {
            ComRearClearFlag();
            switch(ComRearGetData(0)) {
                case dce_gear:
                    ComBehindSendCmd(ask_rear,ComRearGetData(1),0x00,0x00);
                    ComWatchSendCmd(behind,dce_gear,ComRearGetData(1),BattertGetLevel());
                break;
                case stuck:
                    ComWatchSendCmd(stuck,dce_gear,ComRearGetData(1),BattertGetLevel());
                break;
                default:break;
            }
        }
        if(ComBehindGetFlag() == 0x80) {
            ComBehindClearFlag();
            switch(ComBehindGetData(0)) {
                case dce_gear:
                    ComWatchSendCmd(front,dce_gear,ComBehindGetData(1),BattertGetLevel());
                break;
                case stuck:
                    ComWatchSendCmd(stuck,dce_gear,ComBehindGetData(1),BattertGetLevel());
                break;
                default:break;
            }
        }
    }
}
