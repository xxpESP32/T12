#ifndef __KEY_H
#define __KEY_H
#include "sys.h"
#include "delay.h"

#define __IQR_POLL_  0

#define KEY_LEFT GPIO_Pin_15
#define KEY_RIGHT GPIO_Pin_14
#define KEY_ENTER GPIO_Pin_13

extern u32 KEY_LEFT_FLAG;
extern u32 KEY_RIGHT_FLAG;
extern u32 KEY_ENTER_FLAG;

#define KEY_FLAG_SET 0

extern u16 T12_Set_Temp;
extern u8 Voltage_FLAG;

extern u8 rotation_Flag;
extern u8 C_E_cut_Flag;
extern u8 skin_Flag;

void KEY_Begin(void);
u32 KEY_LEFT_OUTPUT(void);
u32 KEY_RIGHT_OUTPUT(void);
u32 KEY_ENTER_OUTPUT(void);
void T12_All_Set_Init(void);
void EXTI15_10_IRQHandler(void);
void Key_Menu_Loop(void);
#endif