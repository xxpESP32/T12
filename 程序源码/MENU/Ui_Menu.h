#ifndef __Ui_Menu_H
#define __Ui_Menu_H

#include "delay.h"
#include "sys.h"
#include "oled.h"
#include "ADC.h"
#include "PWM.h"

void Ui_Menu_Main(void);
void Ui_Menu_Son_Voltage(void);
void Ui_Menu_Son_Calibrate(void);
void Ui_Menu_Son_Set(void);

void Ui_Menu_Son_Voltage_5V(void);
void Ui_Menu_Son_Voltage_9V(void);
void Ui_Menu_Son_Voltage_12V(void);
void Ui_Menu_Son_Voltage_15V(void);
void Ui_Menu_Son_Voltage_20V(void);

extern u16 Calibrate_Value;
void Ui_Menu_Son_Calibrate_set(void);

void Ui_Menu_Son_Skin_set(u8 Menu_Flag);

extern u8 C_E_cut_Flag;
extern u32 Temperature_steps_Value;
extern u16 Low_power_Time_Value;
extern u16 Low_power_Temp_Value;
extern u8 Temp_define_Flag;

void Ui_Menu_Son_Skin_set_function(void);
void Ui_Menu_Son_Temp_step_number_set_function(void);
void Ui_Menu_Son_Time_low_power_set_function(void);

void Ui_Menu_Son_ADJUST_set_function(void);
void Ui_Menu_Son_Temp_low_power_set_function(void);
void Ui_Menu_Son_About_Information_function(void);
void Ui_Menu_Son_Enter_Key_function(void);
#endif