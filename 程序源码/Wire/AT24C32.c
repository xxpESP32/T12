#include "AT24C32.h"
#include "delay.h"

void AT24C32_Begin(void){
	GPIO_inits();
	GPIO_SetBits(Wrie_GPIO,SDA|SCL);	
}
u8 AT24C32_ACK(void){
	u8 ack=0;
	I2C_Strat();
	I2C_Send_Byte(AT24C32_ADDR);
	ack=I2C_ACK_Wait();
	I2C_Stopping();
	return ack;
}
void AT24C32_Write_OneByte(u16 Addr,u8 Data){
	I2C_Strat();
	I2C_Send_Byte(AT24C32_Write);
	I2C_ACK_Wait();
	I2C_Send_Byte(Addr);	
	I2C_ACK_Wait();	
	I2C_Send_Byte(Data);	
	I2C_ACK_Wait();
  I2C_Stopping();	
	delay_ms(5); //一定要加延时
}



u8 AT24C32_Read_OneByte(u16 Addr){
	u8 callback_Vslue;
	I2C_Strat();
	I2C_Send_Byte(AT24C32_ADDR);
	I2C_ACK_Wait();
	I2C_Send_Byte(Addr);	
	I2C_ACK_Wait();
	
	I2C_Strat();
	I2C_Send_Byte(AT24C32_Read);	
	I2C_ACK_Wait();	
  callback_Vslue=I2C_Read_Byte();
	I2C_NACK();
	I2C_Stopping();
  return 	callback_Vslue;
}

u8 AT24C32_Check(void){
	AT24C32_Write_OneByte(1,0xFE);
	if(AT24C32_Read_OneByte(1)==0XFE){
		return 1;
	}
	  return 0;
}