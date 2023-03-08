#include "Timer.h"
#include "oled.h"
#include "ADC.h"
#include "PWM.h"
#include "Ui_Menu.h"
#include "Key.h"
#include "menu.h"


int PWM_Value;
u8 PWM_Display_Flag;
u32 num;
u16 Tim_time;
u16 Tims=0;
void TIM4_Begin(u32 ARR,u32 PCR){
	
	TIM_TimeBaseInitTypeDef TIM_InitSturct;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	
	TIM_InitSturct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_InitSturct.TIM_CounterMode =TIM_CounterMode_Up;
	TIM_InitSturct.TIM_Period = ARR-1;
	TIM_InitSturct.TIM_Prescaler=PCR-1;
	TIM_InitSturct.TIM_RepetitionCounter=DISABLE;
	TIM_TimeBaseInit(TIM4,&TIM_InitSturct);
	TIM_ClearFlag(TIM4,TIM_FLAG_Update);   //清除中断标志
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE); //中断标准位的使能
	TIM_Cmd(TIM4,ENABLE); //TIM计时器的使能
	
	NVIC_InitTypeDef NVIC_InitStruct;
	
	NVIC_InitStruct.NVIC_IRQChannel =TIM4_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd =ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStruct);
	
}

void TIM3_Begin(u16 ARR,u16 PCR){
	
	TIM_TimeBaseInitTypeDef TIM_InitStruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	TIM_InitStruct.TIM_ClockDivision =TIM_CKD_DIV1;
	TIM_InitStruct.TIM_CounterMode =TIM_CounterMode_Up;
	TIM_InitStruct.TIM_Period =ARR-1;
	TIM_InitStruct.TIM_Prescaler=PCR-1;
	TIM_TimeBaseInit(TIM3,&TIM_InitStruct);

	TIM_ClearFlag(TIM3,TIM_FLAG_Update);   //清除中断标志
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //中断标准位的使能

	TIM_Cmd(TIM3,ENABLE); //TIM计时器的使能
	

	NVIC_InitTypeDef NVIC_InitStruct;
	
	NVIC_InitStruct.NVIC_IRQChannel =TIM3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd =ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_InitStruct);

}

void TIM4_IRQHandler(void){
	
	if(TIM_GetITStatus(TIM4,TIM_IT_Update)!=RESET){
		if(PWM_Display_Flag==0){
			if(index_cp==0|index_cp==9){
					Get_T12_ADC(T12_Set_Temp);
			}else{
					TIM_SetCompare3(TIM2,0);
			}
		}
		   
		TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
	}
	
}

void TIM3_IRQHandler(void){
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)!=RESET){
	
		Tim_time++;
		if(Tim_time>=(Low_power_Time_Value*60)){
	
			PWM_Display_Flag =1;
			
			while(Tim_time>=(Low_power_Time_Value*60)){
				//ADC_Get_Votage_Value();
				//PWM_Value=RV.return_value_T12*Calibrate_Value;
      		Get_T12_ADC(Low_power_Temp_Value);  				
				
				
				OLED_Clear();
				OLED_Draw_Rect(28,4,68,24,1);
				OLED_ShowChinese(32,8,35,16,1);//温
				OLED_ShowChinese(16+32,8,36,16,1);//度
				OLED_ShowChinese(32+32,8,37,16,1);//步
				OLED_ShowChinese(48+32,8,38,16,1);//数
				OLED_Refresh();
				if(GPIO_ReadInputDataBit(GPIOB,KEY_LEFT)==0){
							Tim_time=0;
							PWM_Display_Flag=0;
									OLED_Clear();
					}
					if(GPIO_ReadInputDataBit(GPIOB,KEY_RIGHT)==0){
							Tim_time=0;
							PWM_Display_Flag=0;	
							OLED_Clear();						
					}
						if(GPIO_ReadInputDataBit(GPIOB,KEY_ENTER)==0){
							Tim_time=0;
							PWM_Display_Flag=0;		
							OLED_Clear();
					}
			}
			
		}
		
		
		
	
		
		//TIM_SetCompare3(TIM2,0);
		
	
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
	}
}