#ifndef __OLED_H
#define __OLED_H 

#include "sys.h"
#include "stdlib.h"	

//-----------------OLED端口定义---------------- 

#define OLED_SCL_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_5)//SCL
#define OLED_SCL_Set() GPIO_SetBits(GPIOA,GPIO_Pin_5)

#define OLED_SDA_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_6)//DIN
#define OLED_SDA_Set() GPIO_SetBits(GPIOA,GPIO_Pin_6)

#define OLED_RES_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_2)//RES
#define OLED_RES_Set() GPIO_SetBits(GPIOA,GPIO_Pin_2)


#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据

void OLED_ClearPoint(u8 x,u8 y);
void OLED_ColorTurn(u8 i);
void OLED_DisplayTurn(u8 i);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_WaitAck(void);
void Send_Byte(u8 dat);
void OLED_WR_Byte(u8 dat,u8 mode);
void OLED_DisPlay_On(void);
void OLED_DisPlay_Off(void);
void OLED_Refresh(void);
void OLED_Clear(void);
void OLED_Clear_Anti(void);
void OLED_Clear_Progress(u8 x,u8 y); //清除特定的区域
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_DrawLine(u8 x1,u8 y1,u8 x2,u8 y2,u8 mode);
void OLED_Draw_Rect(u8 x,u8 y,u8 w,u8 h,u8 mode);//画矩形
void OLED_DrawProgress(u8 x,u8 y,u8 w,u8 h,u8 mode,u16 set_Value);//画进度条
void OLED_DrawCircle(u8 x,u8 y,u8 r);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size1,u8 mode);
void OLED_ShowChar6x8(u8 x,u8 y,u8 chr,u8 mode);
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 size1,u8 mode);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size1,u8 mode);
void OLED_ShowFloatNum_8(u16 x,u16 y,float num,u8 len,u8 size1,u8 mode);
void OLED_ShowFloatNum1(u16 x,u16 y,float num,u8 len,u8 size1,u8 mode);
void OLED_ShowFloatNum2(u16 x,u16 y,float num,u8 len,u8 size1,u8 mode);
void OLED_ShowFloatNum3(u16 x,u16 y,double num,u8 len,u8 size1,u8 mode);
void OLED_ShowChinese(u8 x,u8 y,u8 num,u8 size1,u8 mode);
void OLED_ScrollDisplay(u8 num,u8 space,u8 mode);
void OLED_ShowPicture(u8 x,u8 y,u8 sizex,u8 sizey,u8 BMP[],u8 mode);
void OLED_Init(void);

#endif

