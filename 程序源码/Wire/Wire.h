#ifndef __Wire_H
#define __Wire_H

#include "delay.h"
#include "sys.h"

#define SDA  GPIO_Pin_4
#define SCL  GPIO_Pin_3
#define Wrie_GPIO  GPIOA
#define SDA_LOW   GPIO_ResetBits(Wrie_GPIO,SDA);
#define SDA_HIGH  GPIO_SetBits(Wrie_GPIO,SDA);
#define SCL_LOW   GPIO_ResetBits(Wrie_GPIO,SCL);
#define SCL_HIGH  GPIO_SetBits(Wrie_GPIO,SCL);
#define SDA_Read  GPIO_ReadInputDataBit(Wrie_GPIO,SDA)

void GPIO_inits(void);
void GPIO_OUT_IN(u8 FLAG);
void I2C_Strat(void);
void I2C_Stopping(void);
u8 I2C_ACK_Wait(void);
void I2C_ACK(void);
void I2C_NACK(void);
void I2C_Send_Byte(u8 tx);
//u8 I2C_Read_Byte(u8 ack);
u8 I2C_Read_Byte(void);
#endif
