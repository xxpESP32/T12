#include "PWM.h"
#include "delay.h"
#include "Ui_Menu.h"
#include "KEY.h"
#include "ADC.h"
#include "Timer.h"
TIM_TimeBaseInitTypeDef TIM_InitStrcuture; //定义结构体
TIM_OCInitTypeDef PWM_InitSturcture;

float Position_KP=15;
float Position_KI =6;
float Position_KD =20;
u16 PWM_Num;
float pt=0;
void GPIO_Begin(void);
void GPIO_Begin(void){
 
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);
  
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed =GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
}

void PWM_init(u32 ARR,u32 PCR){
	GPIO_Begin(); //初始化GPIO和打开AFIO复用时钟
	//GPIO_WriteBit(GPIOA,GPIO_Pin_2,0);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//打开RCC_APB1的TIM2的时钟

  
	
	TIM_InitStrcuture.TIM_Period=ARR-1; //重装载值
	TIM_InitStrcuture.TIM_Prescaler=PCR-1; //预分频系数
	TIM_InitStrcuture.TIM_CounterMode=TIM_CounterMode_Up; //计数方式，向上计数
	TIM_InitStrcuture.TIM_ClockDivision=DISABLE; //时钟分割（输入捕获用）
	TIM_InitStrcuture.TIM_RepetitionCounter=DISABLE; //高级计时器使用
	TIM_TimeBaseInit(TIM2,&TIM_InitStrcuture); //初始化TIM2
	//注意我们使用的是通用计时器TIM2~TIM5
	//高级计时器 TIM1，TIM8
	//基本计时器 TIM6，TIM7
	//本案例是使用GPIO_PA1即为TIM2_CH2(TIM2定时器的第二个通道）所以
	//使用TIM_OC2Init，若为TIM2_CH3即为TIM_OC3Init
	//TIM_OC2PreloadConfig();也需要是TIM2_CH2

	PWM_InitSturcture.TIM_OCMode=TIM_OCMode_PWM1;  //PWM脉冲输出的模式（舵机智能是PWM1）
	PWM_InitSturcture.TIM_OutputState=TIM_OutputState_Enable; //PWM的比较输出使能
	PWM_InitSturcture.TIM_OCPolarity=TIM_OCPolarity_High; //PWM的输出极性
	TIM_OC3Init(TIM2,&PWM_InitSturcture);
	TIM_OC3PreloadConfig(TIM2,TIM_OCPreload_Enable); //PWM_OC2的使能
	TIM_Cmd(TIM2,ENABLE);
}

u16 Position_PID (int Encoder,int Target)
{
	static float Bias,Pwm,Integral_bias,Last_Bias;
	Bias=Encoder-Target; //计算偏差目标-实际
	Integral_bias+=Bias; //求出偏差和的积分
	Pwm=Position_KP*Bias+Position_KI*Integral_bias+Position_KD*(Bias-Last_Bias); //位置式PID控制器
	Last_Bias=Bias; //保存上一次偏差
	
	if(Pwm<=0){
		Pwm=0;
		Integral_bias=0;
		//Integral_bias=0;		
	}
	if(Pwm>=1000){
		Pwm =1000;
		Integral_bias=0;
	}
	return Pwm; //增量输出
}

void Get_T12_ADC(u16 Temps){
  
	TIM_SetCompare3(TIM2,0);
	delay_ms(220);
	ADC_Get_Votage_Value();
	pt=Temps-(RV.return_value_T12*Calibrate_Value);
//	 if((RV.return_value_T12*Calibrate_Value)<=Temps){
//		 		TIM_SetCompare3(TIM2,1000);
//	 }else{
//				TIM_SetCompare3(TIM2,0);
//	 }

			PWM_Num=Position_PID (Temps,RV.return_value_T12*Calibrate_Value);
			TIM_SetCompare3(TIM2,PWM_Num);
	

	
//	}
	//delay_ms(200);
//  if(pt>=0){
//		TIM_SetCompare3(TIM2,1000);
//		PWM_Num=1000;
//	}
//	else if(pt<0){
//			TIM_SetCompare3(TIM2,0);
//				PWM_Num=0;
//	}
	
}
