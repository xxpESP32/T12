#include "menu.h"
#include "Ui_Menu.h"
u8 index_cp;
void (*current_operation_func)(void);


static void menu_part_main(void);

static void menu_part_son_one(void);
static void menu_part_son_tow(void);
static void menu_part_son_three(void);

static void menu_part_son_four(void);
static void menu_part_son_five(void);
static void menu_part_son_six(void);
static void menu_part_son_seven(void);
static void menu_part_son_nine(void);

static void menu_part_son_ten(void);

static void menu_part_son_eleven(void);
static void menu_part_son_twelve(void);
static void menu_part_son_thirteen(void);
static void menu_part_son_fourteen(void);
static void menu_part_son_fifteen(void);
static void menu_part_son_sixteen(void);
static void menu_part_son_seventeen(void);
static void menu_part_son_seventeen_CP(void);

static void menu_part_son_nineteen(void);
static void menu_part_son_twenty(void);
static void menu_part_son_twenty_one(void);
static void menu_part_son_twenty_tow(void);
static void menu_part_son_twenty_threen(void);
static void menu_part_son_twenty_four(void);
static void menu_part_son_twenty_five(void);

Menu_Creat M_G[25]={
	
	{0,0,1,0,(*menu_part_main)}, //��һ��
	
	{1,2,4,0,(*menu_part_son_one)},//�ڶ���
	{2,3,9,0,(*menu_part_son_tow)},
	{3,1,10,0,(*menu_part_son_three)},
	
	{4,5,4,1,(*menu_part_son_four)},//������
	{5,6,5,1,(*menu_part_son_five)},
	{6,7,6,1,(*menu_part_son_six)},
	{7,8,7,1,(*menu_part_son_seven)},
	{8,4,8,1,(*menu_part_son_nine)},
	
	{9,9,2,9,(*menu_part_son_ten)},//������ У׼�ӽ���
	
	{10,11,10,3,(*menu_part_son_eleven)},//������ ����->Ƥ���л�����
	{11,12,18,3,(*menu_part_son_twelve)},//������ ����->�¶ȼӼ��������ý���
	{12,13,19,3,(*menu_part_son_thirteen)},//������ ����->�͹���ʱ�����ý���
	{13,14,13,3,(*menu_part_son_fourteen)},//������ ����->��ת���ý���
	{14,15,14,3,(*menu_part_son_fifteen)},//������ ����->��Ӣ���л����ý���
	{15,16,20,3,(*menu_part_son_sixteen)},//������ ����->�ָ������������ý���
	{16,17,21,3,(*menu_part_son_seventeen)},//������ ����->�͹����¶��ý���
	{17,10,22,3,(*menu_part_son_seventeen_CP)},//������ ����->������ʾ����
	
	//{18,18,10,18,(*menu_part_son_nineteen)},
	{18,18,11,18,(*menu_part_son_twenty)},
	{19,19,12,19,(*menu_part_son_twenty_one)},
	{20,23,15,15,(*menu_part_son_twenty_tow)}, //�ָ���������->ȡ��
	{21,21,16,21,(*menu_part_son_twenty_threen)},
	{22,17,17,17,(*menu_part_son_twenty_four)},	
	
	{23,20,23,15,(*menu_part_son_twenty_five)},	//�ָ���������->ȷ��
	
};

void Menu_Loop(void){
			current_operation_func=M_G[index_cp].current_operation;
      current_operation_func();	
	
}

static void menu_part_main(void){
	
	Ui_Menu_Main();
	
}
static void menu_part_son_one(void){
	
	Ui_Menu_Son_Voltage();
}
static void menu_part_son_tow(void){
	
	Ui_Menu_Son_Calibrate();
}
static void menu_part_son_three(void){
	
	Ui_Menu_Son_Set();
}
static void menu_part_son_four(void){
	Ui_Menu_Son_Voltage_5V();
}

static void menu_part_son_five(void){
	Ui_Menu_Son_Voltage_9V();
}
static void menu_part_son_six(void){
	Ui_Menu_Son_Voltage_12V();
}
static void menu_part_son_seven(void){
	Ui_Menu_Son_Voltage_15V();
}
static void menu_part_son_nine(void){
	Ui_Menu_Son_Voltage_20V();
}
static void menu_part_son_ten(void){
	Ui_Menu_Son_Calibrate_set();
}
static void menu_part_son_eleven(void){
	Ui_Menu_Son_Skin_set(0);
}
static void menu_part_son_twelve(void){
	Ui_Menu_Son_Skin_set(1);
}
static void menu_part_son_thirteen(void){
	Ui_Menu_Son_Skin_set(2);
}
static void menu_part_son_fourteen(void){
	Ui_Menu_Son_Skin_set(3);
}
static void menu_part_son_fifteen(void){
	Ui_Menu_Son_Skin_set(4);
}
static void menu_part_son_sixteen(void){
  Ui_Menu_Son_Skin_set(5);
}
static void menu_part_son_seventeen(void){
  Ui_Menu_Son_Skin_set(6);
}
static void menu_part_son_seventeen_CP(void){
	Ui_Menu_Son_Skin_set(7);
}
static void menu_part_son_nineteen(void){
	Ui_Menu_Son_Skin_set_function();
}
static void menu_part_son_twenty(void){
	Ui_Menu_Son_Temp_step_number_set_function();
}
static void menu_part_son_twenty_one(void){
	Ui_Menu_Son_Time_low_power_set_function();
}
static void menu_part_son_twenty_tow(void){
	Ui_Menu_Son_ADJUST_set_function();
}
static void menu_part_son_twenty_threen(void){
	Ui_Menu_Son_Temp_low_power_set_function();
}
static void menu_part_son_twenty_four(void){
	Ui_Menu_Son_About_Information_function();
}
static void menu_part_son_twenty_five(void){
	Ui_Menu_Son_Enter_Key_function();
}