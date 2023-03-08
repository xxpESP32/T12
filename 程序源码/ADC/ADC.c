#include "ADC.h"
u16 BUff[9];


struct return_value RV;
static void GPIO_Begin(void);
static void MY_ADC_DMA_Begin(void);
u8 number;
static void GPIO_Begin(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin=I_ADC_GPIO|U_ADC_GPIO;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin=T12_ADC_GPIO;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
}
static void MY_ADC_DMA_Begin(void){
	DMA_InitTypeDef DNA_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	DMA_DeInit(DMA1_Channel1);
	
	DNA_InitStructure.DMA_BufferSize =9;
	DNA_InitStructure.DMA_PeripheralBaseAddr =(uint32_t)&(ADC1->DR);
	DNA_InitStructure.DMA_MemoryBaseAddr=(u32)&BUff;
	DNA_InitStructure.DMA_PeripheralDataSize =DMA_PeripheralDataSize_HalfWord;
	DNA_InitStructure.DMA_MemoryDataSize =DMA_MemoryDataSize_HalfWord;
	DNA_InitStructure.DMA_DIR=DMA_DIR_PeripheralSRC;
	DNA_InitStructure.DMA_M2M=DMA_M2M_Disable;
	DNA_InitStructure.DMA_MemoryInc =DMA_MemoryInc_Enable;
	DNA_InitStructure.DMA_PeripheralInc =DMA_PeripheralInc_Disable;
	DNA_InitStructure.DMA_Mode =DMA_Mode_Circular;
	DNA_InitStructure.DMA_Priority =DMA_Priority_High;
	DMA_Init(DMA1_Channel1,&DNA_InitStructure);
	
	DMA_Cmd(DMA1_Channel1,ENABLE);
	
}


void ADC_Begin(void){
	

	ADC_InitTypeDef ADC_InitSStructure;
	GPIO_Begin();
	MY_ADC_DMA_Begin();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
	ADC_InitSStructure.ADC_ContinuousConvMode =ENABLE;
	ADC_InitSStructure.ADC_ScanConvMode =ENABLE;
	ADC_InitSStructure.ADC_DataAlign =ADC_DataAlign_Right;
	ADC_InitSStructure.ADC_Mode =ADC_Mode_Independent;
	ADC_InitSStructure.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;
	ADC_InitSStructure.ADC_NbrOfChannel=3;
	ADC_Init(ADC1,&ADC_InitSStructure);
	ADC_TempSensorVrefintCmd(ENABLE);
	
	//ADC_RegularChannelConfig(ADC1,ADC_Channel_1,1,ADC_SampleTime_1Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_7,1,ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_8,2,ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_16,3,ADC_SampleTime_239Cycles5);
	
	ADC_DMACmd(ADC1,ENABLE);
	ADC_Cmd(ADC1,ENABLE);  //ADC使能
	ADC_ResetCalibration(ADC1); //重置ADC
	while(ADC_GetResetCalibrationStatus(ADC1)); //判断ADC重置是否完成
	
	ADC_StartCalibration(ADC1); //校验ADC
	while(ADC_GetSoftwareStartConvStatus(ADC1)); //判断ADC校验是否完成
	ADC_SoftwareStartConvCmd(ADC1,ENABLE); //使能软件触发
		
}

float ADC_Get_Votage_Value(void){
	float temp_cp;
   #if _3V3_2V5_FLAG_
		RV.return_value=((BUff[0]*2.5)/4095)*23.255;
		RV.return_value_T12=(BUff[1]*2.5)/4095;
		temp_cp =((float)BUff[2]*2.5)/4095;
		RV.return_value_temp =(float)((1.43-temp_cp)/0.0043+25);  
	#elif
		RV.return_value=((BUff[0]*2.5)/4095)*23.255;
		RV.return_value_T12=(BUff[1]*2.5)/4095;
		temp_cp =((float)BUff[2]*2.5)/4095;
		RV.return_value_temp =(float)((1.43-temp_cp)/0.0043+25);   
	#endif
	ADC_SoftwareStartConvCmd(ADC1,DISABLE);
}
//----------------------------非DMA方式------------------------------
void ADC_T12_Begin(void){
	

	ADC_InitTypeDef ADC_InitSStructure;
	GPIO_Begin();
	//MY_ADC_DMA_Begin();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	ADC_DeInit(ADC1);
	ADC_InitSStructure.ADC_Mode =ADC_Mode_Independent;
	ADC_InitSStructure.ADC_ContinuousConvMode =DISABLE;
	ADC_InitSStructure.ADC_ScanConvMode =DISABLE;
	ADC_InitSStructure.ADC_DataAlign =ADC_DataAlign_Right;
	ADC_InitSStructure.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;
	ADC_InitSStructure.ADC_NbrOfChannel=1;
	ADC_Init(ADC1,&ADC_InitSStructure);
	//ADC_TempSensorVrefintCmd(ENABLE);
	
	//ADC_RegularChannelConfig(ADC1,ADC_Channel_1,1,ADC_SampleTime_1Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_7,1,ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_8,1,ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_16,1,ADC_SampleTime_239Cycles5);
	
	//ADC_DMACmd(ADC1,ENABLE);
	ADC_Cmd(ADC1,ENABLE);  //ADC使能
	ADC_ResetCalibration(ADC1); //重置ADC
	while(ADC_GetResetCalibrationStatus(ADC1)); //判断ADC重置是否完成
	
	ADC_StartCalibration(ADC1); //校验ADC
	while(ADC_GetSoftwareStartConvStatus(ADC1)); //判断ADC校验是否完成
	//ADC_SoftwareStartConvCmd(ADC1,ENABLE); //使能软件触发
		
}
float ADC_Get_GPIO_Votage_Value(u8 ch){
		ADC_RegularChannelConfig(ADC1,ch,1,ADC_SampleTime_239Cycles5);
	  ADC_SoftwareStartConvCmd(ADC1,ENABLE);
	 while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));
	return ADC_GetConversionValue(ADC1);
}

