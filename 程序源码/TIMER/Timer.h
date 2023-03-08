#ifndef __Timer_H
#define __Timer_H
#include "delay.h"
#include "sys.h"
extern int PWM_Value;
extern u8 PWM_Display_Flag;
void TIM4_Begin(u32 ARR,u32 PCR);
void TIM3_Begin(u16 ARR,u16 PCR);
#endif