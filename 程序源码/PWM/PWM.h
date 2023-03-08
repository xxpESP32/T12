#ifndef __PWM_H
#define __PWM_H
#include "sys.h"

extern u16 PWM_Num;
extern float pt;
void GPIO_Begin(void);
void PWM_init(u32 ARR,u32 PCR);
u16 Position_PID (int Encoder,int Target);
void Get_T12_ADC(u16 Temps);
#endif