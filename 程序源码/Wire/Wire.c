#include "Wire.h"


void GPIO_inits(void){
	//�����ǳ�ʼ���������ߺ�ʱ������
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);   
	
	GPIO_InitTypeDef GPIO_InitStucture;
	GPIO_InitStucture.GPIO_Mode =GPIO_Mode_Out_PP;
	GPIO_InitStucture.GPIO_Pin = SDA;
	GPIO_InitStucture.GPIO_Speed=GPIO_Speed_50MHz;	
	GPIO_Init(Wrie_GPIO,&GPIO_InitStucture);
	
	GPIO_InitStucture.GPIO_Mode =GPIO_Mode_Out_PP;
	GPIO_InitStucture.GPIO_Pin = SCL;
	GPIO_InitStucture.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(Wrie_GPIO,&GPIO_InitStucture);
	GPIO_SetBits(Wrie_GPIO,SCL|SDA);
	
}

void GPIO_OUT_IN(u8 FLAG){  //�������ߵ������������������ģʽ
	if(FLAG==1){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStucture;
	GPIO_InitStucture.GPIO_Mode =GPIO_Mode_Out_PP;
	GPIO_InitStucture.GPIO_Pin = SDA;
	GPIO_InitStucture.GPIO_Speed=GPIO_Speed_50MHz;	
	GPIO_Init(Wrie_GPIO,&GPIO_InitStucture);
	}else if(FLAG==0){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStucture;
	GPIO_InitStucture.GPIO_Mode =GPIO_Mode_IN_FLOATING;
	GPIO_InitStucture.GPIO_Pin = SDA;
	GPIO_InitStucture.GPIO_Speed=GPIO_Speed_50MHz;	
		
	GPIO_Init(Wrie_GPIO,&GPIO_InitStucture);
	}		

}

void I2C_Strat(void){ 
	//ģʽ���������ģʽ
	GPIO_OUT_IN(1);    //I2C����ʼ�ź����������ߺ�ʱ������ͬʱ����
	SCL_HIGH;          //�ú�����ʱ4us���ú�SDA����
	SDA_HIGH;       //��֮���ǽ����������ɸߵ�ƽתΪ�͵�ƽ
	delay_us(4);
	SDA_LOW;
	delay_us(4);
	SCL_LOW;
}
void I2C_Stopping(void){
	GPIO_OUT_IN(1);
	SDA_LOW;
	delay_us(4);
	SCL_HIGH;
	delay_us(4);
	SDA_HIGH;
	delay_us(4);
}
u8 I2C_ACK_Wait(void){
	u8 Time_err;                 //ACk�ĵȴ����Ƕ�ȡ��ǰACk��״̬
	GPIO_OUT_IN(0);              //��������ģʽ
	SCL_HIGH;delay_us(2);        //��ʼ֮ǰҪ�ɰ��������ߺ�ʱ������ͬʱ����
	//SDA_HIGH;Delay_us(1);          
	
	while(SDA_Read){             //�ж��������ߵ�����״̬Ϊ�߷���1��֮���0ʱҪ
		Time_err++;                //��ʱ�����������ٷ���0
		if(Time_err>250){          //�����
			I2C_Stopping();
			return 1;
		}
	}
	SCL_LOW;
	delay_us(2);
	return 0;

}

void I2C_ACK(void){
	SCL_LOW;
	GPIO_OUT_IN(1);
	SDA_LOW;
	delay_us(2);
	SCL_HIGH;
	delay_us(2);
	SCL_LOW;
}
void I2C_NACK(void){
	SCL_LOW;
	GPIO_OUT_IN(1);
	SDA_HIGH;
	delay_us(2);
	SCL_HIGH;
	delay_us(2);
	SCL_LOW;
}
void I2C_Send_Byte(u8 tx){
	u8 t=0;
	GPIO_OUT_IN(1);
	SCL_LOW;
	for(t=0;t<8;t++){
		if((tx&0x80)>>7){
			SDA_HIGH;
		}else{
			SDA_LOW;
		}
		tx<<=1;
		delay_us(2);
		SCL_HIGH;
		delay_us(2);
		SCL_LOW;
		delay_us(2);
	}
	
	
}
/*
u8 I2C_Read_Byte(u8 ack){ // 1
	u8 i,rece;
	GPIO_OUT_IN(0);
	for(i=0;i<8;i++){
		SCL_LOW;
		Delay_us(2);
		SCL_HIGH;
		rece<<=1;
		if(SDA_Read) rece++;
		Delay_us(1);
	}
	 if(!ack){
		 I2C_NACK();
	 }else{     
		 I2C_ACK();
	 }
	 return rece;
}
*/
u8 I2C_Read_Byte(void){ // 1
	u8 i,rece;
	GPIO_OUT_IN(0);
	for(i=0;i<8;i++){
		SCL_LOW;
		delay_us(2);
		SCL_HIGH;
		rece<<=1;
		if(SDA_Read) rece++;
		delay_us(1);
	}
	 
	 return rece;
}
