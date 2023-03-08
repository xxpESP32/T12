#include "delay.h"
#include "sys.h"
#include "oled.h"
//#include "bmp.h"
#include "PWM.h"
#include "KEY.h"
#include "ADC.h"
#include "FreeRTOS.h"
#include "task.h"
#include "CH224K.h"
#include "menu.h"
#include "Timer.h"
#include "Wire.h"
#include "AT24C32.h"
#include "Ui_Menu.h"
#include "usart.h"	
#include "stdio.h"
TaskHandle_t HandlerTask1;

StackType_t xIdle3Static[128];
StaticTask_t xIdleTCB;

void vApplicationGetIdleTaskMemory( StaticTask_t ** ppxIdleTaskTCBBuffer,StackType_t ** ppxIdleTaskStackBuffer,uint32_t * pulIdleTaskStackSize ){
			*ppxIdleTaskTCBBuffer=&xIdleTCB;				
			*ppxIdleTaskStackBuffer=xIdle3Static;
			*pulIdleTaskStackSize=128;
}

void Task1Function( void * param){ 
	
		for(;;){
      Menu_Loop();	  
		  vTaskDelay(200);
	}
}


void Task2Function(void* param){

  for(;;)
  {

		  
  }
}


int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	
	delay_init();
	SystemInit();
	OLED_Init();

	PWM_init(1000,7200); //72MHz/72=1MHz=1000KHz=1us,100*1us=100us;//72/720=100KHZ,
	OLED_Clear();
	KEY_Begin();
	ADC_Begin();
	
	CH224K_Begin();

	TIM4_Begin(7000,7200); //300ms
	TIM3_Begin(10000,7200);//1000ms
  uart_init(115200);
	AT24C32_Begin();
	printf("%d\r\n",AT24C32_Check());
	T12_All_Set_Init();
	OLED_ColorTurn(skin_Flag);//0正常显示，1 反色显示
  OLED_DisplayTurn(rotation_Flag);//0正常显示 1 屏幕翻转显示
	//xTaskCreate(Task1Function,"Task1",100,NULL,2,&HandlerTask1);
  //xTaskCreate(Task2Function,"Task2",100,NULL,2,&HandlerTask1);
	//CH224K_Set_Output_Voltage(OUTPUT_5V);
  //vTaskStartScheduler(); //开始调度

	

	while(1)
	{
   
		 Key_Menu_Loop();
		//Menu_Loop();
		
	}
}