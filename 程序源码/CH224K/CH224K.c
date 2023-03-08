#include "CH224K.h"

enum OUTPUT_Volage OUTPUT_Volage_Value;


void CH224K_Begin(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin =CFG1|CFG2|CFG3;
	GPIO_InitStructure.GPIO_Speed =GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_SetBits(GPIOB,CFG1);
	GPIO_ResetBits(GPIOB,CFG2);
	GPIO_ResetBits(GPIOB,CFG3);
}

u8 CH224K_Set_Output_Voltage(u8 Output_FLAG){
	if(Output_FLAG == OUTPUT_5V){
		GPIO_SetBits(GPIOB,CFG1);
		GPIO_ResetBits(GPIOB,CFG2);
		GPIO_ResetBits(GPIOB,CFG3);
		return 1;
	}
	if(Output_FLAG == OUTPUT_9V){
		GPIO_ResetBits(GPIOB,CFG1);
		GPIO_ResetBits(GPIOB,CFG2);
		GPIO_ResetBits(GPIOB,CFG3);
		return 2;
	}
	if(Output_FLAG == OUTPUT_12V){
		GPIO_ResetBits(GPIOB,CFG1);
		GPIO_ResetBits(GPIOB,CFG2);
		GPIO_SetBits(GPIOB,CFG3);
		return 3;
	}
	if(Output_FLAG == OUTPUT_15V){
		GPIO_ResetBits(GPIOB,CFG1);
		GPIO_SetBits(GPIOB,CFG2);
		GPIO_SetBits(GPIOB,CFG3);
		return 4;
	}
	if(Output_FLAG == OUTPUT_20V){
		GPIO_ResetBits(GPIOB,CFG1);
		GPIO_SetBits(GPIOB,CFG2);
		GPIO_ResetBits(GPIOB,CFG3);
		return 5;
	}
	return 0;
}