#include "KEY.h"
#include "CH224K.h"
#include "menu.h"
#include "oled.h"
#include "FreeRTOS.h"
#include "task.h"
#include "Ui_Menu.h"
#include "AT24C32.h"
//********************************AT24C02�洢��ַ
// 5 Ƥ���л���־λ
// 6 ��Ļ��ת
// 7 ��Ӣ���л�
// 8 �¶Ȳ���
// 9 �͹���ʱ��
// 10 �¶�У׼
u32 KEY_LEFT_FLAG=0;
u32 KEY_RIGHT_FLAG=0;
u32 KEY_ENTER_FLAG=0;

u16 T12_Set_Temp=300;
u8 Voltage_FLAG;
u8 rotation_Flag;
u8 C_E_cut_Flag;
u8 skin_Flag;


static void Calibrate_set_success(void);
static void rotation_set(void);
static void C_E_cut(void);
static void PD_Set(void);
static void skin_set(void);
static void calibration_add(u8 add_or_minus);
static void calibration_set_add_minus(u8 add_or_minus);
static void Low_power_Time_Value_set(u8 add_or_minus);
static void Low_power_Temp_Value_set(u8 add_or_minus);
static void Reset_set_success(void);

void KEY_Begin(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	#if __IQR_POLL_
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	#endif
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);

	
  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin =KEY_LEFT|KEY_RIGHT|KEY_ENTER;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	#if __IQR_POLL_
	//EXTI_15���ⲿ����
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource15);
	EXTI_InitStructure.EXTI_Line =EXTI_Line15;
	EXTI_InitStructure.EXTI_Mode =EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger =EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd =ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	//EXTI_14���ⲿ����
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource14);
	EXTI_InitStructure.EXTI_Line =EXTI_Line14;
	EXTI_InitStructure.EXTI_Mode =EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger =EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd =ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	//EXTI_13���ⲿ����
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource13);
	EXTI_InitStructure.EXTI_Line =EXTI_Line13;
	EXTI_InitStructure.EXTI_Mode =EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger =EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd =ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	//EXTI_13���ж�
	
	NVIC_InitStructure.NVIC_IRQChannel =EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;
	NVIC_InitStructure.NVIC_IRQChannelCmd =ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	#endif
}
//******************************************�жϷ�ʽ***************************
#if __IQR_POLL_
void EXTI15_10_IRQHandler(void){
	delay_ms(200);
	if(EXTI_GetITStatus(EXTI_Line15)!=RESET){
			//delay_ms(200);
		//if(EXTI_GetITStatus(EXTI_Line15)!=RESET){
		 if(index_cp ==0){ //T12�¶����� �Ӱ���
			if(T12_Set_Temp>=420)
				T12_Set_Temp=420;
			else
				T12_Set_Temp+=Temperature_steps_Value;
		Temp_define_Flag=1;
		AT24C32_Write_OneByte(15,T12_Set_Temp);
		AT24C32_Write_OneByte(16,T12_Set_Temp>>8); 	
		OLED_Clear_Progress(64,3);//���������
    }
		 
		calibration_add(0);
		calibration_set_add_minus(0);
		Low_power_Time_Value_set(0);
		Low_power_Temp_Value_set(0);
		
		if(index_cp !=0){
			OLED_Clear();
			//OLED_Clear_Progress(128,4);
			//OLED_Clear();
		}
		//delay_ms(10);
		index_cp=M_G[index_cp].next;
		//CH224K_Set_Output_Voltage(OUTPUT_9V);
		
	 		EXTI_ClearITPendingBit(EXTI_Line15);
			//	while(EXTI_GetFlagStatus(EXTI_Line15)!=RESET);
		//	EXTI_ClearFlag(EXTI_Line15); 
		//}
	}
	else if(EXTI_GetITStatus(EXTI_Line14)!=RESET){
		//delay_ms(200);
		//if(EXTI_GetITStatus(EXTI_Line14)!=RESET){
		if(index_cp ==0){ //T12�¶����� ������
			if(T12_Set_Temp<=50)
				T12_Set_Temp=50;
			else
				T12_Set_Temp-=Temperature_steps_Value;
		Temp_define_Flag=1;
		AT24C32_Write_OneByte(15,T12_Set_Temp);
		AT24C32_Write_OneByte(16,T12_Set_Temp>>8);	
		OLED_Clear_Progress(64,3);//���������
    }			
		calibration_add(1);
		calibration_set_add_minus(1);
		Low_power_Time_Value_set(1);
		Low_power_Temp_Value_set(1);
		
		if(index_cp !=0){
			OLED_Clear();	
			//OLED_Clear();
		}
				//delay_ms(10);
		index_cp=M_G[index_cp].back;

		//CH224K_Set_Output_Voltage(OUTPUT_20V);
		EXTI_ClearITPendingBit(EXTI_Line14);
		//while(EXTI_GetFlagStatus(EXTI_Line14)!=RESET);
		//EXTI_ClearFlag(EXTI_Line14);
	
	//	}
	}
	else if(EXTI_GetITStatus(EXTI_Line13)!=RESET){
		//delay_ms(200);
	  //if(EXTI_GetITStatus(EXTI_Line13)!=RESET){
		Calibrate_set_success();	
		rotation_set();
		C_E_cut();
		PD_Set();
		skin_set();
		Reset_set_success();
			OLED_Clear();
			//
		index_cp=M_G[index_cp].enter;
			
			


		EXTI_ClearITPendingBit(EXTI_Line13);
		//while(EXTI_GetFlagStatus(EXTI_Line13)!=RESET);
			//EXTI_ClearFlag(EXTI_Line13);
		//}
	}
  
}
#endif
//******************************************��ѯ��ʽ***************************
void Key_Menu_Loop(void){
	if(GPIO_ReadInputDataBit(GPIOB,KEY_LEFT)==0){
			delay_ms(100);
		if(GPIO_ReadInputDataBit(GPIOB,KEY_LEFT)==0){
		 if(index_cp ==0){ //T12�¶����� �Ӱ���
			if(T12_Set_Temp>=420)
				T12_Set_Temp=420;
			else
				T12_Set_Temp+=Temperature_steps_Value;
		Temp_define_Flag=1;
		AT24C32_Write_OneByte(15,T12_Set_Temp);
		AT24C32_Write_OneByte(16,T12_Set_Temp>>8); 	
		OLED_Clear_Progress(64,3);//���������
    }
		 
		calibration_add(0);
		calibration_set_add_minus(0);
		Low_power_Time_Value_set(0);
		Low_power_Temp_Value_set(0);
		
		if(index_cp !=0){
			OLED_Clear();
		}

		index_cp=M_G[index_cp].next;

		}
	}
	else if(GPIO_ReadInputDataBit(GPIOB,KEY_RIGHT)==0){
		delay_ms(100);
		if(GPIO_ReadInputDataBit(GPIOB,KEY_RIGHT)==0){
		if(index_cp ==0){ //T12�¶����� ������
			if(T12_Set_Temp<=50)
				T12_Set_Temp=50;
			else
				T12_Set_Temp-=Temperature_steps_Value;
		Temp_define_Flag=1;
		AT24C32_Write_OneByte(15,T12_Set_Temp);
		AT24C32_Write_OneByte(16,T12_Set_Temp>>8);	
		OLED_Clear_Progress(64,3);//���������
    }			
		calibration_add(1);
		calibration_set_add_minus(1);
		Low_power_Time_Value_set(1);
		Low_power_Temp_Value_set(1);
		
		if(index_cp !=0){
			OLED_Clear();	
		}

		index_cp=M_G[index_cp].back;


	
		}
	}
	else if(GPIO_ReadInputDataBit(GPIOB,KEY_ENTER)==0){
		delay_ms(200);
	  if(GPIO_ReadInputDataBit(GPIOB,KEY_ENTER)==0){
		Calibrate_set_success();	
		rotation_set();
		C_E_cut();
		PD_Set();
		skin_set();
		Reset_set_success();
			OLED_Clear();
			//
		index_cp=M_G[index_cp].enter;
			
			

		}
	}
	Menu_Loop();	
}

//У׼�ɹ���ʾ
static void Calibrate_set_success(void){
	if(index_cp ==9){
		
		OLED_Clear();
		if(C_E_cut_Flag ==0){
			OLED_Draw_Rect(28,4,68,24,1);
			OLED_ShowChinese(32,8,29,16,1);//��
			OLED_ShowChinese(16+32,8,30,16,1);//��
			OLED_ShowChinese(32+32,8,31,16,1);//��
			OLED_ShowChinese(48+32,8,32,16,1);//��
		}else{
			OLED_Draw_Rect(30,4,64,24,1);		
			OLED_ShowString(35,8,"Calibrate",8,1);
			OLED_ShowString(43,16,"Success",8,1);			
		}
		OLED_Refresh();
		AT24C32_Write_OneByte(10,Calibrate_Value);
		AT24C32_Write_OneByte(14,Calibrate_Value>>8);    		
		delay_ms(1000);
	}
}
//Ƥ���л�
static void skin_set(void){
	if(index_cp ==10){
		skin_Flag=!skin_Flag;
		OLED_ColorTurn(skin_Flag);
		AT24C32_Write_OneByte(5,skin_Flag);
	}
	
}
//��ת���ý���
static void rotation_set(void){
	if(index_cp ==13){
		rotation_Flag=!rotation_Flag;
		OLED_DisplayTurn(rotation_Flag);
		AT24C32_Write_OneByte(6,rotation_Flag);
	}
}
//��Ӣ���л�
static void C_E_cut(void){
	if(index_cp ==14){
		C_E_cut_Flag=!C_E_cut_Flag;
    AT24C32_Write_OneByte(7,C_E_cut_Flag);
	}
}
//PD��ƭģʽ����
static void PD_Set(void){
	if(index_cp ==4) Voltage_FLAG=Voltage_FLAG=CH224K_Set_Output_Voltage(OUTPUT_5V);
	if(index_cp ==5) Voltage_FLAG=Voltage_FLAG=CH224K_Set_Output_Voltage(OUTPUT_9V);
	if(index_cp ==6) Voltage_FLAG=Voltage_FLAG=CH224K_Set_Output_Voltage(OUTPUT_12V);
	if(index_cp ==7) Voltage_FLAG=Voltage_FLAG=CH224K_Set_Output_Voltage(OUTPUT_15V);
	if(index_cp ==8) Voltage_FLAG=Voltage_FLAG=CH224K_Set_Output_Voltage(OUTPUT_20V);
	
}
///У׼�¶ȼӰ���
static void calibration_add(u8 add_or_minus){
	 if(add_or_minus ==0){
			if(index_cp ==9){ //У׼����  �Ӱ���
			if(Calibrate_Value>=2000)
				Calibrate_Value=0;
			else
				Calibrate_Value++;
	
    }
	}
	else if(add_or_minus ==1){
		 if(index_cp ==9){ //У׼����  �Ӱ���
			if(Calibrate_Value<=0)
				Calibrate_Value=0;
			else
				Calibrate_Value--;
	
    }
	 }
	//AT24C32_Write_OneByte(1,5);
}
static void calibration_set_add_minus(u8 add_or_minus){
		 if(add_or_minus ==0){
				if(index_cp ==18){ //У׼����  �Ӱ���
				if(Temperature_steps_Value>=20)
					Temperature_steps_Value=20;
				else{
					Temperature_steps_Value++;
				 }
				AT24C32_Write_OneByte(8,Temperature_steps_Value);				 
			  }
		}
	  else if(add_or_minus ==1){
			 if(index_cp ==18){ //У׼����  �Ӱ���
				if(Temperature_steps_Value<=0)
					Temperature_steps_Value=0;
				else
					Temperature_steps_Value--;
				AT24C32_Write_OneByte(8,Temperature_steps_Value);
			 }
	  }
}
//����->�͹���ʱ��
static void Low_power_Time_Value_set(u8 add_or_minus){
		 if(add_or_minus ==0){
				if(index_cp ==19){ //У׼����  �Ӱ���
				if(Low_power_Time_Value>=255)
					Low_power_Time_Value=0;
				else{
					Low_power_Time_Value++;
				 }
				AT24C32_Write_OneByte(9,Low_power_Time_Value);				
			  }
		}
	  else if(add_or_minus ==1){
			 if(index_cp ==19){ //У׼����  ������
				if(Low_power_Time_Value<=0)
					Low_power_Time_Value=0;
				else
					Low_power_Time_Value--;
			 }
			 	AT24C32_Write_OneByte(9,Low_power_Time_Value);	
	  }
		
}
//����->�͹����¶�
static void Low_power_Temp_Value_set(u8 add_or_minus){
		 if(add_or_minus ==0){
				if(index_cp ==21){ //У׼����  �Ӱ���
				if(Low_power_Temp_Value>=200)
					Low_power_Temp_Value=0;
				else{
					Low_power_Temp_Value++;
				 }
				AT24C32_Write_OneByte(11,Low_power_Temp_Value);
			  }
		}
	  else if(add_or_minus ==1){
			 if(index_cp ==21){ //У׼����  �Ӱ���
				if(Low_power_Temp_Value<=0)
					Low_power_Temp_Value=0;
				else
					Low_power_Temp_Value--;
			 }
			AT24C32_Write_OneByte(11,Low_power_Temp_Value);
	  }
}

//�ָ��������óɹ�����
//��ӻָ��������õ����á�
static void Reset_set_success(void){
	if(index_cp ==23){
		OLED_Clear();
		if(C_E_cut_Flag ==0){
			skin_Flag =0;
			rotation_Flag =0;
			C_E_cut_Flag =0;
			Temperature_steps_Value=10;
			Low_power_Time_Value=15;
			Calibrate_Value = 387;
			Low_power_Temp_Value=50;
			AT24C32_Write_OneByte(5,skin_Flag);
			AT24C32_Write_OneByte(6,rotation_Flag);
			AT24C32_Write_OneByte(7,C_E_cut_Flag);		
			AT24C32_Write_OneByte(8,Temperature_steps_Value);			
			AT24C32_Write_OneByte(9,Low_power_Time_Value);
			AT24C32_Write_OneByte(10,Calibrate_Value);
			AT24C32_Write_OneByte(11,Low_power_Temp_Value);
			OLED_Draw_Rect(28,4,68,24,1);
			OLED_ShowChinese(32,8,33,16,1);//��
			OLED_ShowChinese(16+32,8,34,16,1);//��
			OLED_ShowChinese(32+32,8,31,16,1);//��
			OLED_ShowChinese(48+32,8,32,16,1);//��
		}else{
			skin_Flag =0;
			rotation_Flag =0;
			C_E_cut_Flag =0;
			Temperature_steps_Value=1;
			Low_power_Time_Value=5;
			Calibrate_Value = 387;
			Low_power_Temp_Value=50;
			T12_Set_Temp = 300;
			AT24C32_Write_OneByte(5,skin_Flag);
			AT24C32_Write_OneByte(6,rotation_Flag);
			AT24C32_Write_OneByte(7,C_E_cut_Flag);		
			AT24C32_Write_OneByte(8,Temperature_steps_Value);			
			AT24C32_Write_OneByte(9,Low_power_Time_Value);
			AT24C32_Write_OneByte(10,Calibrate_Value);
			AT24C32_Write_OneByte(11,Low_power_Temp_Value);
			OLED_Draw_Rect(30,4,64,24,1);		
			OLED_ShowString(50,8,"Reset",8,1);
			OLED_ShowString(43,16,"Success",8,1);						
		}
		OLED_Refresh();
		delay_ms(1000);
	}
}

void T12_All_Set_Init(void){
	skin_Flag =AT24C32_Read_OneByte(5);
	rotation_Flag =AT24C32_Read_OneByte(6);
	C_E_cut_Flag =AT24C32_Read_OneByte(7);
	Temperature_steps_Value=AT24C32_Read_OneByte(8);
	Low_power_Time_Value=AT24C32_Read_OneByte(9);
	Calibrate_Value = ((u16)AT24C32_Read_OneByte(14)<<8)|AT24C32_Read_OneByte(10);//��8λ
	Low_power_Temp_Value=AT24C32_Read_OneByte(11);
	T12_Set_Temp=((u16)AT24C32_Read_OneByte(16)<<8)|AT24C32_Read_OneByte(15);//��8λ
}
#if KEY_FLAG_SET
u32 KEY_LEFT_OUTPUT(void){

	if(GPIO_ReadInputDataBit(GPIOB,KEY_LEFT)==0){
		return 1;		
	}
	return 0;	
}
u32 KEY_RIGHT_OUTPUT(void){

	if(GPIO_ReadInputDataBit(GPIOB,KEY_RIGHT)==0){
		return 1;		
	}
	return 0;	
}
u32 KEY_ENTER_OUTPUT(void){

	if(GPIO_ReadInputDataBit(GPIOB,KEY_ENTER)==0){
		return 1;		
	}
	return 0;	
}
#endif