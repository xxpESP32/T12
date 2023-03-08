#include "PWM.h"
#include "delay.h"
#include "Ui_Menu.h"
#include "KEY.h"
#include "ADC.h"
#include "Timer.h"
TIM_TimeBaseInitTypeDef TIM_InitStrcuture; //����ṹ��
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
	GPIO_Begin(); //��ʼ��GPIO�ʹ�AFIO����ʱ��
	//GPIO_WriteBit(GPIOA,GPIO_Pin_2,0);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//��RCC_APB1��TIM2��ʱ��

  
	
	TIM_InitStrcuture.TIM_Period=ARR-1; //��װ��ֵ
	TIM_InitStrcuture.TIM_Prescaler=PCR-1; //Ԥ��Ƶϵ��
	TIM_InitStrcuture.TIM_CounterMode=TIM_CounterMode_Up; //������ʽ�����ϼ���
	TIM_InitStrcuture.TIM_ClockDivision=DISABLE; //ʱ�ӷָ���벶���ã�
	TIM_InitStrcuture.TIM_RepetitionCounter=DISABLE; //�߼���ʱ��ʹ��
	TIM_TimeBaseInit(TIM2,&TIM_InitStrcuture); //��ʼ��TIM2
	//ע������ʹ�õ���ͨ�ü�ʱ��TIM2~TIM5
	//�߼���ʱ�� TIM1��TIM8
	//������ʱ�� TIM6��TIM7
	//��������ʹ��GPIO_PA1��ΪTIM2_CH2(TIM2��ʱ���ĵڶ���ͨ��������
	//ʹ��TIM_OC2Init����ΪTIM2_CH3��ΪTIM_OC3Init
	//TIM_OC2PreloadConfig();Ҳ��Ҫ��TIM2_CH2

	PWM_InitSturcture.TIM_OCMode=TIM_OCMode_PWM1;  //PWM���������ģʽ�����������PWM1��
	PWM_InitSturcture.TIM_OutputState=TIM_OutputState_Enable; //PWM�ıȽ����ʹ��
	PWM_InitSturcture.TIM_OCPolarity=TIM_OCPolarity_High; //PWM���������
	TIM_OC3Init(TIM2,&PWM_InitSturcture);
	TIM_OC3PreloadConfig(TIM2,TIM_OCPreload_Enable); //PWM_OC2��ʹ��
	TIM_Cmd(TIM2,ENABLE);
}

u16 Position_PID (int Encoder,int Target)
{
	static float Bias,Pwm,Integral_bias,Last_Bias;
	Bias=Encoder-Target; //����ƫ��Ŀ��-ʵ��
	Integral_bias+=Bias; //���ƫ��͵Ļ���
	Pwm=Position_KP*Bias+Position_KI*Integral_bias+Position_KD*(Bias-Last_Bias); //λ��ʽPID������
	Last_Bias=Bias; //������һ��ƫ��
	
	if(Pwm<=0){
		Pwm=0;
		Integral_bias=0;
		//Integral_bias=0;		
	}
	if(Pwm>=1000){
		Pwm =1000;
		Integral_bias=0;
	}
	return Pwm; //�������
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
