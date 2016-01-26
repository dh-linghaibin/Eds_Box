

#include "Com.h"
#include "Delay.h"


void ComInit(void) {
    //Watch
    PC_DDR_DDR4 = 0;
    PC_CR1_C14 = 0;
    PC_CR2_C24 = 1;
    //Behind
    PC_DDR_DDR3 = 0;
    PC_CR1_C13 = 0;
    PC_CR2_C23 = 1;
    //Rear
    PA_DDR_DDR3 = 0;
    PA_CR1_C13 = 0;
    PA_CR2_C23 = 1;
    
    //外部中断初始化
	EXTI_CR1 &= ~BIT(4);//开启PC口中断
	EXTI_CR1 &= ~BIT(5);

	EXTI_CR1 |= BIT(1);//开启PA口中断
	EXTI_CR1 &= ~BIT(0);
}

#define COM_WATCH_OUT 	    PC_ODR_ODR4
#define COM_WATCH_IN 	 	PC_IDR_IDR4
#define COM_WATCH_DR 		PC_DDR_DDR4
#define COM_WATCH_INT 	    PC_CR2_C24

u8 ComSendWatch(u8 data[]) {
	u16 wait = 0;
	u8 data_t = 0;//保存临时值
	u8 i = 0,j = 0;
	
	COM_WATCH_INT = 0;//中断
	COM_WATCH_DR = 1;//设置为输出
	COM_WATCH_OUT = 0;
	DelayUs(50);//拉低20ms说明总线开始
	COM_WATCH_DR = 0;//设置为输入
	DelayUs(1);//拉低20ms说明总线开始
	while(COM_WATCH_IN == 0) {//等待从机拉高
		if(wait < 50) {
			wait++;
		} else {//超时，退出
			COM_WATCH_INT = 1;//中断
			return 0x44;
		}
	}
	while(COM_WATCH_IN == 0) {
		if(wait < 50) {
			wait++;
		} else {//超时，退出
			COM_WATCH_INT = 1;//中断
			return 0x44;
		}
	}
	COM_WATCH_DR = 1;//设置为输出
	for(j = 0;j < 5;j++) {
		data_t = data[j];
		for(i=0;i<8;i++) {
			COM_WATCH_OUT = 0;
			if(data_t&0x80) {
				DelayUs(40);
			} else {
				DelayUs(20);
			}
			COM_WATCH_OUT = 1;
			DelayUs(10);
			data_t<<=1;
		}
	}
	DelayUs(30);
	COM_WATCH_OUT = 1;
	COM_WATCH_INT = 1;//中断
	COM_WATCH_DR = 0;//设置为输入
	return 0x88;   
}

u8 ComReadWatch(u8 data_s[]) {
    static u16 wait = 0;
    u8 i = 0,j = 0;
	u8 data = 0;
	wait = 0;
	
	COM_WATCH_DR = 0;//设置为输入
	while(COM_WATCH_IN == 0) {
		if(wait < 60) {
			wait++;
		} else {
			return 0x44;
		}
	}
	if(wait > 11) {
		wait = 0;
		COM_WATCH_DR = 1;//设置为输出
		COM_WATCH_OUT = 0;
		DelayUs(1);
		COM_WATCH_DR = 0;//设置为输入
		//开始接受数据
		for(j = 0;j < 5;j++) {
			for(i=0;i<8;i++) {  
				data<<=1; 
				while(COM_WATCH_IN == 1) {
					if(wait < 60) {
						wait++;
					} else {
						return 0x44;
					}
				}
				wait = 0;
				while(COM_WATCH_IN == 0) {
					if(wait < 60) {
						wait++;
					} else {
						return 0x44;
					}
				}
				if(wait > 11) {//为1
					data|=0x01;  
				}
				wait = 0;					
			}
			data_s[j] = data;
			data = 0;
		}
		if(data_s[4] == (data_s[0]+data_s[1]+data_s[2]+data_s[3])) {//累加校验
			return 0x88;
		} else {
			return 0x44;
		}
	} else {//时间不对 推出
		return 0x44;
	}
} 


#define COM_REAR_OUT 	    PC_ODR_ODR3
#define COM_REAR_IN 	 	PC_IDR_IDR3
#define COM_REAR_DR 		PC_DDR_DDR3
#define COM_REAR_INT 	    PC_CR2_C23

u8 ComSendRear(u8 data[]) {
    u16 wait = 0;
	u8 data_t = 0;//保存临时值
	u8 i = 0,j = 0;
	
	COM_REAR_INT = 0;//中断
	COM_REAR_DR = 1;//设置为输出
	COM_REAR_OUT = 0;
	DelayUs(50);//拉低20ms说明总线开始
	COM_REAR_DR = 0;//设置为输入
	DelayUs(1);//拉低20ms说明总线开始
	while(COM_REAR_IN == 0) {//等待从机拉高
		if(wait < 50) {
			wait++;
		} else {//超时，退出
			COM_REAR_INT = 1;//中断
			return 0x44;
		}
	}
	while(COM_REAR_IN == 0) {
		if(wait < 50) {
			wait++;
		} else {//超时，退出
			COM_REAR_INT = 1;//中断
			return 0x44;
		}
	}
	COM_REAR_DR = 1;//设置为输出
	for(j = 0;j < 5;j++) {
		data_t = data[j];
		for(i=0;i<8;i++) {
			COM_REAR_OUT = 0;
			if(data_t&0x80) {
				DelayUs(40);
			} else {
				DelayUs(20);
			}
			COM_REAR_OUT = 1;
			DelayUs(10);
			data_t<<=1;
		}
	}
	DelayUs(30);
	COM_REAR_OUT = 1;
	COM_REAR_INT = 1;//中断
	COM_REAR_DR = 0;//设置为输入
	return 0x88;   
}

u8 ComReadRear(u8 data_s[]) {
    static u16 wait = 0;
    u8 i = 0,j = 0;
	u8 data = 0;
	wait = 0;
	
	COM_REAR_DR = 0;//设置为输入
	while(COM_REAR_IN == 0) {
		if(wait < 60) {
			wait++;
		} else {
			return 0x44;
		}
	}
	if(wait > 11) {
		wait = 0;
		COM_REAR_DR = 1;//设置为输出
		COM_REAR_OUT = 0;
		DelayUs(1);
		COM_REAR_DR = 0;//设置为输入
		//开始接受数据
		for(j = 0;j < 5;j++) {
			for(i=0;i<8;i++) {  
				data<<=1; 
				while(COM_REAR_IN == 1) {
					if(wait < 60) {
						wait++;
					} else {
						return 0x44;
					}
				}
				wait = 0;
				while(COM_REAR_IN == 0) {
					if(wait < 60) {
						wait++;
					} else {
						return 0x44;
					}
				}
				if(wait > 11) {//为1
					data|=0x01;  
				}
				wait = 0;					
			}
			data_s[j] = data;
			data = 0;
		}
		if(data_s[4] == (data_s[0]+data_s[1]+data_s[2]+data_s[3])) {//累加校验
			return 0x88;
		} else {
			return 0x44;
		}
	} else {//时间不对 推出
		return 0x44;
	}
}

#define COM_BEHIND_OUT 	    PA_ODR_ODR3
#define COM_BEHIND_IN 	 	PA_IDR_IDR3
#define COM_BEHIND_DR 		PA_DDR_DDR3
#define COM_BEHIND_INT 	    PA_CR2_C23

u8 ComSendBehind(u8 data[]) {
    u16 wait = 0;
	u8 data_t = 0;//保存临时值
	u8 i = 0,j = 0;
	
	COM_BEHIND_INT = 0;//中断
	COM_BEHIND_DR = 1;//设置为输出
	COM_BEHIND_OUT = 0;
	DelayUs(50);//拉低20ms说明总线开始
	COM_BEHIND_DR = 0;//设置为输入
	DelayUs(1);//拉低20ms说明总线开始
	while(COM_BEHIND_IN == 0) {//等待从机拉高
		if(wait < 50) {
			wait++;
		} else {//超时，退出
			COM_BEHIND_INT = 1;//中断
			return 0x44;
		}
	}
	while(COM_BEHIND_IN == 0) {
		if(wait < 50) {
			wait++;
		} else {//超时，退出
			COM_BEHIND_INT = 1;//中断
			return 0x44;
		}
	}
	COM_BEHIND_DR = 1;//设置为输出
	for(j = 0;j < 5;j++) {
		data_t = data[j];
		for(i=0;i<8;i++) {
			COM_BEHIND_OUT = 0;
			if(data_t&0x80) {
				DelayUs(40);
			} else {
				DelayUs(20);
			}
			COM_BEHIND_OUT = 1;
			DelayUs(10);
			data_t<<=1;
		}
	}
	DelayUs(30);
	COM_BEHIND_OUT = 1;
	COM_BEHIND_INT = 1;//中断
	COM_BEHIND_DR = 0;//设置为输入
	return 0x88;   
}

u8 ComReadBehind(u8 data_s[]) {
    static u16 wait = 0;
    u8 i = 0,j = 0;
	u8 data = 0;
	wait = 0;
	
	COM_BEHIND_DR = 0;//设置为输入
	while(COM_BEHIND_IN == 0) {
		if(wait < 60) {
			wait++;
		} else {
			return 0x44;
		}
	}
	if(wait > 11) {
		wait = 0;
		COM_BEHIND_DR = 1;//设置为输出
		COM_BEHIND_OUT = 0;
		DelayUs(1);
		COM_BEHIND_DR = 0;//设置为输入
		//开始接受数据
		for(j = 0;j < 5;j++) {
			for(i=0;i<8;i++) {  
				data<<=1; 
				while(COM_BEHIND_IN == 1) {
					if(wait < 60) {
						wait++;
					} else {
						return 0x44;
					}
				}
				wait = 0;
				while(COM_BEHIND_IN == 0) {
					if(wait < 60) {
						wait++;
					} else {
						return 0x44;
					}
				}
				if(wait > 11) {//为1
					data|=0x01;  
				}
				wait = 0;					
			}
			data_s[j] = data;
			data = 0;
		}
		if(data_s[4] == (data_s[0]+data_s[1]+data_s[2]+data_s[3])) {//累加校验
			return 0x88;
		} else {
			return 0x44;
		}
	} else {//时间不对 推出
		return 0x44;
	}
}

static u8 com_date_watch[5];
static u8 com_date_rear[5];
static u8 com_date_behind[5];

static u8 rs_ok_watch = 0;//whether it has received data
static u8 rs_ok_rear = 0;//whether it has received data
static u8 rs_ok_behind = 0;//whether it has received data

//watch
u8 ComWatchGetData(u8 num) {
    return com_date_watch[num];
}

u8 ComWatchGetFlag(void) {
    return rs_ok_watch;
}

void ComWatchClearFlag(void) {
    rs_ok_watch = 0;
}

void ComWatchSendCmd(u8 cmd,u8 par1,u8 par2,u8 par3) {
    u8 com_t_data[5] = {0,0,0,0,0};//前拨
	//u16 com_check = 0;//保存累加校验值
	//com_check = cmd+par1+par2+par3+par4;
	com_t_data[0] = cmd; //cmd
	com_t_data[1] = par1;
	com_t_data[2] = par2;
	com_t_data[3] = par3;
    com_t_data[4] = com_t_data[0]+com_t_data[1]+com_t_data[2]
                                    +com_t_data[3];
    INTOFF
	ComSendWatch(com_t_data);
    INTEN
}
//rear
u8 ComRearGetData(u8 num) {
    return com_date_rear[num];
}

u8 ComRearGetFlag(void) {
    return rs_ok_rear;
}

void ComRearClearFlag(void) {
    rs_ok_rear = 0;
}

void ComRearSendCmd(u8 cmd,u8 par1,u8 par2,u8 par3) {
    u8 com_t_data[5] = {0,0,0,0,0};//前拨
	//u16 com_check = 0;//保存累加校验值
	//com_check = cmd+par1+par2+par3+par4;
	com_t_data[0] = cmd; //cmd
	com_t_data[1] = par1;
	com_t_data[2] = par2;
	com_t_data[3] = par3;
    com_t_data[4] = com_t_data[0]+com_t_data[1]+com_t_data[2]
                                    +com_t_data[3];
    INTOFF
	ComSendRear(com_t_data);
    INTEN
}
//behind
u8 ComBehindGetData(u8 num) {
    return com_date_behind[num];
}

u8 ComBehindGetFlag(void) {
    return rs_ok_behind;
}

void ComBehindClearFlag(void) {
    rs_ok_behind = 0;
}

void ComBehindSendCmd(u8 cmd,u8 par1,u8 par2,u8 par3) {
    u8 com_t_data[5] = {0,0,0,0,0};//前拨
	//u16 com_check = 0;//保存累加校验值
	//com_check = cmd+par1+par2+par3+par4;
	com_t_data[0] = cmd; //cmd
	com_t_data[1] = par1;
	com_t_data[2] = par2;
	com_t_data[3] = par3;
    com_t_data[4] = com_t_data[0]+com_t_data[1]+com_t_data[2]
                                    +com_t_data[3];
    INTOFF
	ComSendBehind(com_t_data);
    INTEN
}

#pragma vector=5
__interrupt void EXTI_PORTA_IRQHandler(void)
{
    INTOFF
    if(ComReadRear(com_date_rear) == 0x88) {
        rs_ok_rear = 0x80;
    }
    INTEN
}


#pragma vector=7
__interrupt void EXTI_PORTC_IRQHandler(void)
{
    INTOFF
    if(ComReadWatch(com_date_watch) == 0x88) {
        rs_ok_watch = 0x80;
    }
    if(ComReadBehind(com_date_behind) == 0x88) {
        rs_ok_behind = 0x80;
    }
    INTEN
}


