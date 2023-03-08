#ifndef __CH224K_H
#define __CH224K_H

#include "sys.h"
#include "delay.h"

#define CFG1 GPIO_Pin_7
#define CFG2 GPIO_Pin_6
#define CFG3 GPIO_Pin_5


enum OUTPUT_Volage{
	 OUTPUT_5V =1,
	 OUTPUT_9V,
   OUTPUT_12V,
   OUTPUT_15V,
   OUTPUT_20V
	
};
extern enum OUTPUT_Volage OUTPUT_Volage_Value;

void CH224K_Begin(void);
u8 CH224K_Set_Output_Voltage(u8 Output_FLAG);
#endif