#ifndef __ADC_H
#define __ADC_H
#include "sys.h"
#include "delay.h"
#define I_ADC_GPIO GPIO_Pin_1
#define U_ADC_GPIO GPIO_Pin_7
#define T12_ADC_GPIO GPIO_Pin_0

#define _3V3_2V5_FLAG_  1

struct return_value{
	float return_value;
	float return_value_current;
	float return_value_T12;
	float return_value_temp;
};
extern struct return_value RV;



void ADC_Begin(void);
float ADC_Get_Votage_Value(void);

void ADC_T12_Begin(void);
float ADC_Get_GPIO_Votage_Value(u8 ch);
#endif