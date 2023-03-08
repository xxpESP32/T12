#ifndef __MENU_H
#define __MENU_H
#include "sys.h"
#include "delay.h"

typedef struct { 
	u8 index;
	u8 next;
	u8 enter;
	u8 back;
	void (*current_operation)(void);	
}Menu_Creat;
extern Menu_Creat M_G[25];

extern void (*current_operation_func)(void);
extern u8 index_cp;

void Menu_Loop(void);
#endif