#ifndef __AT24C32_H
#define __AT24C32_H

#include "delay.h"
#include "sys.h"
#include "Wire.h"

#define AT24C32_ADDR  0xA0
#define AT24C32_Write 0XA0
#define AT24C32_Read  0xA1

void AT24C32_Begin(void);
u8 AT24C32_ACK(void);
void AT24C32_Write_OneByte(u16 Addr,u8 Data);
u8 AT24C32_Read_OneByte(u16 Addr);
u8 AT24C32_Check(void);

#endif