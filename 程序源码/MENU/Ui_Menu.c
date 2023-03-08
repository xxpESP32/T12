#include "Ui_Menu.h"
#include "KEY.h"
#include "bmp.h"
#include "ADC.h"
#include "Timer.h"
#include "PWM.h"

u32 PWM_DAT;
u16 Calibrate_Value=390;

u32 step_number_value;
u32 low_power_value;
u32 Temperature_steps_Value=10;
u16 Low_power_Time_Value=30;
u16 Low_power_Temp_Value=50;
float T12_Voltage_Sum;
u8 Temp_define_Flag=1;
void Ui_Menu_Main(void){
	#if 0
		if(PWM_DAT>=40000){
				PWM_DAT=0;
			}
			PWM_DAT+=1000;
		  TIM_SetCompare3(TIM2,PWM_DAT);
		  ADC_Get_Votage_Value();
		  OLED_ShowString(0,0,"V:",12,0);
		  OLED_ShowFloatNum2(12,0,return_value*27,6,12,0);
	
		  
		   OLED_ShowString(0,12,"A:",12,0);
		  OLED_ShowFloatNum3(12,12,return_value_current,6,12,0);
		  OLED_ShowFloatNum3(64,0,return_value_T12,6,12,0);
		  OLED_ShowNum(64,12,PWM_DAT,6,12,0);
		  //OLED_ShowNum(0, 0,return_value,5,12,0);
		  //OLED_ShowNum(0, 10,ADC_Get_Value(),5,12,0);
			
	#endif
	//if(PWM_DAT>=1000){
				//PWM_DAT=0;
		//	}
			//PWM_DAT+=;
   //检测PID值，PWM值
	/*OLED_ShowString(74,0,"P:",12,1);
	OLED_ShowNum(86,0,Position_PID(400,PWM_Value),6,12,1);
	OLED_ShowString(74,12,"C:",12,1);
	OLED_ShowNum(86,12,PWM_Value,6,12,1);
	*/
	//ADC_Cmd(ADC1,DISABLE);

	
  //Get_T12_ADC();
	//if(RV.return_value_T12*Calibrate_Value<=420){
	//if((RV.return_value_T12[0]-RV.return_value_T12[1])>5){
		//
	//}else{
	    //if((RV.return_value_T12*Calibrate_Value*10)>=T12_Set_Temp && Temp_define_Flag==1){
			//	OLED_ShowNum(1,1,T12_Set_Temp,3,24,0);
			//	Temp_define_Flag=0;
        				
			//}
			//if{      	    
				OLED_ShowNum(1,1,RV.return_value_T12*Calibrate_Value,3,24,0);
				//OLED_ShowFloatNum3(1,1,RV.return_value_T12,6,12,0);
		//	}
	 
	//}
	//显示加热温度
	
		
	//TIM_SetCompare3(TIM2,1000);
	
	//OLED_ShowFloatNum3(1,1,RV.return_value_T12,6,12,0);


	OLED_ShowChinese(37,1,0,16,1);//°
	OLED_ShowString(42,5,"C",16,1);
	//显示设定温度+进度条
	OLED_ShowNum(48,19,T12_Set_Temp,3,8,1);
	OLED_DrawProgress(1,26,59,4,1,T12_Set_Temp);
	//显示热这个中文字
	//OLED_Draw_Rect(54,0,18,17,1);
	if(C_E_cut_Flag==0){
		OLED_ShowChinese(56,1,1,16,0);//热	
	}else{
		OLED_ShowString(58,1,"H",16,0);
	}
	//显示电压电流
	
	OLED_ShowString(74,0,"V:",12,1);
	OLED_ShowFloatNum2(86,0,RV.return_value,6,12,1);
	OLED_ShowString(74,12,"T:",12,1);
	OLED_ShowFloatNum2(86,12,RV.return_value_temp,6,12,1);
	OLED_ShowString(74,24,"P:",8,1);	
	OLED_ShowNum(86,24,PWM_Num,5,8,1);
	
/*	//显示功率
	OLED_ShowString(78-12,24,"W:",8,1);
	OLED_ShowFloatNum_8(78,24,(u16)(RV.return_value)*RV.return_value_current,3,8,1);
	//显示芯片温度
	OLED_ShowString(103,24,"T:",8,1);
	OLED_ShowNum(116,24,RV.return_value_temp,2,8,1);
*/
	OLED_Refresh();
}
//进度条 420°C


void Ui_Menu_Son_Voltage(void){
	
	
	if(C_E_cut_Flag ==0){
		OLED_ShowString(11+12,4,"<",24,0);
		OLED_ShowChinese(40,4,0,24,0);//电
		OLED_ShowChinese(64,4,1,24,0);//压
	  OLED_Draw_Rect(88,4,1,23,1);
		OLED_ShowString(95,4,">",24,0);
	}else{
		OLED_ShowString(5,4,"<",24,0);
		OLED_ShowString(22,4,"VOLTAGE",24,0);
		OLED_ShowString(104+5,4,">",24,0);
	}

	OLED_Refresh();
}
void Ui_Menu_Son_Calibrate(void){
	if(C_E_cut_Flag ==0){
	OLED_ShowString(11+12,4,"<",24,0);
	OLED_ShowChinese(40,4,2,24,0);//校
  OLED_ShowChinese(64,4,3,24,0);//准
  OLED_Draw_Rect(88,4,1,23,1);
	OLED_ShowString(95,4,">",24,0);
	}else{
		OLED_ShowString(5,4,"<",24,0);
		OLED_ShowString(28,4,"ADJUST",24,0);
		OLED_ShowString(104+5,4,">",24,0);
	}
	OLED_Refresh();
}
void Ui_Menu_Son_Set(void){
	if(C_E_cut_Flag ==0){
	OLED_ShowString(11+12,4,"<",24,0);
	OLED_ShowChinese(40,4,4,24,0);//设
  OLED_ShowChinese(64,4,5,24,0);//置
  OLED_Draw_Rect(88,4,1,23,1);
	OLED_ShowString(95,4,">",24,0);
	}else{
		OLED_ShowString(5,4,"<",24,0);
		OLED_ShowString(46,4,"SET",24,0);
		OLED_ShowString(104+5,4,">",24,0);
	}
	OLED_Refresh();	
}
void Ui_Menu_Son_Voltage_5V(void){
	OLED_ShowString(5,0,"PD 5V 3A ",8,0);
	OLED_ShowString(5,8,"PD QC 9V 3A ",8,1);
	OLED_ShowString(5,16,"QC 12V 3A ",8,1);
	OLED_ShowString(5,24,"PD 15V 3A ",8,1);
	OLED_ShowPicture(88,0,24,24,BMP1,0);

		ADC_Get_Votage_Value();
		if((RV.return_value)<=6 & (RV.return_value)>=4.3){
		OLED_ShowString(80,24,"success",8,1);
		}else{
			OLED_ShowString(80,24,"fsilure",8,1);
		}
	
	OLED_Refresh();
}
void Ui_Menu_Son_Voltage_9V(void){
	OLED_ShowString(5,0,"PD 5V 3A ",8,1);
	OLED_ShowString(5,8,"PD QC 9V 3A ",8,0);
	OLED_ShowString(5,16,"QC 12V 3A ",8,1);
	OLED_ShowString(5,24,"PD 15V 3A ",8,1);
	OLED_ShowPicture(88,0,24,24,BMP1,0);

		ADC_Get_Votage_Value();
		if((RV.return_value)<=9.8 & (RV.return_value)>=8.2){
		OLED_ShowString(80,24,"success",8,1);
		}else{
			OLED_ShowString(80,24,"fsilure",8,1);
		}
	
		OLED_Refresh();

}
void Ui_Menu_Son_Voltage_12V(void){
	OLED_ShowString(5,0,"PD 5V 3A ",8,1);
	OLED_ShowString(5,8,"PD QC 9V 3A ",8,1);
	OLED_ShowString(5,16,"QC 12V 3A ",8,0);
	OLED_ShowString(5,24,"PD 15V 3A ",8,1);
  OLED_ShowPicture(80,0,24,24,BMP1,0);

	ADC_Get_Votage_Value();
	if((RV.return_value)<=12.8 & (RV.return_value)>=11.2){
		OLED_ShowString(80,24,"success",8,1);
		}else{
			OLED_ShowString(80,24,"fsilure",8,1);
		}
	
	OLED_Refresh();

}
void Ui_Menu_Son_Voltage_15V(void){
	OLED_ShowString(5,0,"PD 5V 3A ",8,1);
	OLED_ShowString(5,8,"PD QC 9V 3A ",8,1);
	OLED_ShowString(5,16,"QC 12V 3A ",8,1);
	OLED_ShowString(5,24,"PD 15V 3A ",8,0);
  OLED_ShowPicture(88,0,24,24,BMP1,0);

	ADC_Get_Votage_Value();
	if((RV.return_value)<=15.8 & (RV.return_value)>=14.0){
		OLED_ShowString(80,24,"success",8,1);
		}else{
			OLED_ShowString(80,24,"fsilure",8,1);
		}
	
	OLED_Refresh();
}
void Ui_Menu_Son_Voltage_20V(void){
	OLED_ShowString(5,0,"PD QC 9V 3A ",8,1);
	OLED_ShowString(5,8,"QC 12V 3A ",8,1);
	OLED_ShowString(5,16,"PD 15V 3A ",8,1);	
	OLED_ShowString(5,24,"PD 20V 3.25A ",8,0);
  OLED_ShowPicture(88,0,24,24,BMP1,0);

	ADC_Get_Votage_Value();
	if((RV.return_value)<=20.8 & (RV.return_value)>=18.2){
		OLED_ShowString(80,24,"success",8,1);
		}else{
			OLED_ShowString(80,24,"fsilure",8,1);
		}
	
	OLED_Refresh();
}

void Ui_Menu_Son_Calibrate_set(void){
	OLED_ShowString(35+20,0,"Calibrate",8,1);
	OLED_ShowNum(44+11,8,Calibrate_Value,4,24,1);
	//OLED_ShowString(1,1,"C_V_T",8,1);	
	OLED_ShowFloatNum3(0,8+1,RV.return_value_T12,6,12,1);
	OLED_ShowString(0+42,8+1,"V",12,1);
	OLED_ShowNum(0,20,RV.return_value_T12*Calibrate_Value,3,12,1);
	OLED_ShowString(0+18,20,"C",12,1);	
	OLED_Refresh();
}

void Ui_Menu_Son_Skin_set(u8 Menu_Flag){
	if(C_E_cut_Flag ==0){
	if(Menu_Flag ==0){
		OLED_ShowString(0,0,">",16,1);
		OLED_ShowChinese(20,0,2,16,1);//热
		OLED_ShowChinese(16+20,0,3,16,1);//热
		OLED_ShowChinese(16+20,0,3,16,1);//热
		
		OLED_ShowChinese(20,16,4,16,1);//热
		OLED_ShowChinese(16+20,16,5,16,1);//热
		OLED_ShowChinese(32+20,16,6,16,1);//热
		OLED_ShowChinese(48+20,16,7,16,1);//热
	}
	if(Menu_Flag ==1){
		OLED_ShowString(0,16,">",16,1);
		OLED_ShowChinese(20,0,2,16,1);//热
		OLED_ShowChinese(16+20,0,3,16,1);//热
		OLED_ShowChinese(20,16,4,16,1);//热
		OLED_ShowChinese(16+20,16,5,16,1);//热
		OLED_ShowChinese(32+20,16,6,16,1);//热
		OLED_ShowChinese(48+20,16,7,16,1);//热
	}
	if(Menu_Flag ==2){
		OLED_ShowString(0,16,">",16,1);
		OLED_ShowChinese(20,0,4,16,1);//热
		OLED_ShowChinese(16+20,0,5,16,1);//热
		OLED_ShowChinese(32+20,0,6,16,1);//热
		OLED_ShowChinese(48+20,0,7,16,1);//热
		OLED_ShowChinese(20,16,8,16,1);//温
		OLED_ShowChinese(16+20,16,9,16,1);//度
		OLED_ShowChinese(32+20,16,10,16,1);//步
		OLED_ShowChinese(48+20,16,11,16,1);//数
		OLED_ShowChinese(64+20,16,12,16,1);//数
		
	}
		if(Menu_Flag ==3){
		OLED_ShowString(0,16,">",16,1);
		OLED_ShowChinese(20,0,8,16,1);//温
		OLED_ShowChinese(16+20,0,9,16,1);//度
		OLED_ShowChinese(32+20,0,10,16,1);//步
		OLED_ShowChinese(48+20,0,11,16,1);//数
		OLED_ShowChinese(64+20,0,12,16,1);//数
		OLED_ShowChinese(20,16,13,16,1);//温
		OLED_ShowChinese(16+20,16,14,16,1);//度
		OLED_ShowChinese(32+20,16,15,16,1);//步
		OLED_ShowChinese(48+20,16,16,16,1);//数
	}if(Menu_Flag ==4){
		OLED_ShowString(0,16,">",16,1);
		OLED_ShowChinese(20,0,13,16,1);//温
		OLED_ShowChinese(16+20,0,14,16,1);//度
		OLED_ShowChinese(32+20,0,15,16,1);//步
		OLED_ShowChinese(48+20,0,16,16,1);//数
		OLED_ShowChinese(20,16,17,16,1);//温
		OLED_ShowChinese(16+20,16,18,16,1);//度
		OLED_ShowChinese(32+20,16,19,16,1);//步
		OLED_ShowChinese(48+20,16,20,16,1);//数
	}if(Menu_Flag ==5){
		OLED_ShowString(0,16,">",16,1);
		OLED_ShowChinese(20,0,17,16,1);//温
		OLED_ShowChinese(16+20,0,18,16,1);//度
		OLED_ShowChinese(32+20,0,19,16,1);//步
		OLED_ShowChinese(48+20,0,20,16,1);//数
		OLED_ShowChinese(20,16,21,16,1);//温
		OLED_ShowChinese(16+20,16,22,16,1);//度
		OLED_ShowChinese(32+20,16,23,16,1);//步
		OLED_ShowChinese(48+20,16,24,16,1);//数
		OLED_ShowChinese(64+20,16,25,16,1);//步
		OLED_ShowChinese(80+20,16,26,16,1);//数
	}
	if(Menu_Flag ==6){
		OLED_ShowString(0,16,">",16,1);
		OLED_ShowChinese(20,0,21,16,1);//温
		OLED_ShowChinese(16+20,0,22,16,1);//度
		OLED_ShowChinese(32+20,0,23,16,1);//步
		OLED_ShowChinese(48+20,0,24,16,1);//数
		OLED_ShowChinese(64+20,0,25,16,1);//步
		OLED_ShowChinese(80+20,0,26,16,1);//数
		OLED_ShowChinese(20,16,8,16,1);//温
		OLED_ShowChinese(16+20,16,9,16,1);//度
		OLED_ShowChinese(32+20,16,10,16,1);//步
		OLED_ShowChinese(48+20,16,4,16,1);//数
		OLED_ShowChinese(64+20,16,5,16,1);//步
	
	}if(Menu_Flag ==7){
		OLED_ShowString(0,16,">",16,1);
		OLED_ShowChinese(20,0,8,16,1);//温
		OLED_ShowChinese(16+20,0,9,16,1);//度
		OLED_ShowChinese(32+20,0,10,16,1);//步
		OLED_ShowChinese(48+20,0,4,16,1);//数
		OLED_ShowChinese(64+20,0,5,16,1);//步
		OLED_ShowChinese(20,16,27,16,1);//温
		OLED_ShowChinese(16+20,16,28,16,1);//度
	
	}
 }else{
	 if(Menu_Flag ==0){
		 OLED_ShowString(0,0,">",16,1);
		 OLED_ShowString(20,0,"Skin",16,1);
		 OLED_ShowString(20,16,"Temp Steps",16,1);
	 }
	 if(Menu_Flag ==1){
		 OLED_ShowString(0,16,">",16,1);
		 OLED_ShowString(20,0,"Skin",16,1);
		 OLED_ShowString(20,16,"Temp Steps",16,1);
	 }
	 if(Menu_Flag ==2){
		 OLED_ShowString(0,16,">",16,1);
		 OLED_ShowString(20,0,"Temp Steps",16,1);
		 OLED_ShowString(20,16,"Low Power Ti",16,1);
	 }
	 if(Menu_Flag ==3){
		 OLED_ShowString(0,16,">",16,1);
		 OLED_ShowString(20,0,"Low Power Ti",16,1);
		 OLED_ShowString(20,16,"Rotation",16,1);
	 }
	 if(Menu_Flag ==4){
		 OLED_ShowString(0,16,">",16,1);
		 OLED_ShowString(20,0,"Rotation",16,1);
		 OLED_ShowString(20,16,"Language Cut",16,1);
	 }
	 if(Menu_Flag ==5){
		 OLED_ShowString(0,16,">",16,1);
		 OLED_ShowString(20,0,"Language Cut",16,1);
		 OLED_ShowString(20,16,"Reset Data",16,1);
	 }
	 if(Menu_Flag ==6){
		 OLED_ShowString(0,16,">",16,1);
		 OLED_ShowString(20,0,"Reset Data",16,1);
		 OLED_ShowString(20,16,"Low Power Te",16,1);
	 }
	 if(Menu_Flag ==7){
		 OLED_ShowString(0,16,">",16,1);
		 OLED_ShowString(20,0,"Low Power Te",16,1);
		 OLED_ShowString(20,16,"In Regard To",16,1);
	 }
 }
	OLED_Refresh();
}

void Ui_Menu_Son_Skin_set_function(void){

}
void Ui_Menu_Son_Temp_step_number_set_function(void){
	OLED_ShowString(12,0,"Temperature steps",8,1);
	OLED_ShowNum(44,8,Temperature_steps_Value,3,24,1);
	OLED_Refresh();	
}

void Ui_Menu_Son_Time_low_power_set_function(void){
	OLED_ShowString(22,0,"Low powor Time",8,1);
	OLED_ShowNum(44,8,Low_power_Time_Value,3,24,1);
	OLED_Refresh();	
		
}
void Ui_Menu_Son_ADJUST_set_function(void){

	
	OLED_ShowString(38,8,"X",12,1);
	OLED_ShowString(84,8,"OK",12,1);
	OLED_Draw_Rect(30,6,20,16,1);
	//OLED_Draw_Rect(80,6,20,20,1);
	OLED_Refresh();
}

void Ui_Menu_Son_Temp_low_power_set_function(void){
	OLED_ShowString(22,0,"Low powor Temp",8,1);
	OLED_ShowNum(44,8,Low_power_Temp_Value,3,24,1);
	OLED_Refresh();	
}
void Ui_Menu_Son_About_Information_function(void){
	OLED_ShowString(0,0,"Versions 1.1",8,1);
	OLED_ShowString(0,8,"Updated 2023/1/2",8,1);
	OLED_ShowString(0,16,"Name T12 Golden Crow",8,1);	
	OLED_ShowString(0,24,"Author Xiao Xia ",8,1);	
	OLED_Refresh();	
}

void Ui_Menu_Son_Enter_Key_function(void){
	OLED_ShowString(38,8,"X",12,1);
	OLED_ShowString(84,8,"OK",12,1);
	//OLED_Draw_Rect(30,6,20,16,1);
	OLED_Draw_Rect(80,6,20,16,1);
	OLED_Refresh();	
}