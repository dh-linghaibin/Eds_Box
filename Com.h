

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

#define add_stal 0xe1//�ӵ�
#define sub_stal 0xe2//����
#define exchange_stal 0xe3//����
#define add_setp 0x03//������
#define sub_setp 0x04//������
#define dce_gear 0x05//��ѯ��ǰ��λ
#define dce_powe 0x06//��ѯ����
#define set_inti 0x07//���ó�ʼλ
#define set_end 0x08//���ý���λ
#define reset 0x09//��λ
#define stuck 0x0a//����

#define front 0x0b //ǰ��
#define behind 0x0c //��
#define stopwatch 0x0d //���
#define null 0x00 //���κ�

#define ask_rear 0xa1//����ǰ����λ

#endif
