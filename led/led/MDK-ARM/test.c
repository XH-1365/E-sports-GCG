#include "test.h"
#include "stdio.h"

short x , x_t;
short y = 10 , y_t = 10;//字体的Y

short box_y,box_y_trg;//框的Y
short box_wid,box_wid_trg;//框的宽


char ui_list = 0;//列表位置确认


/*---------------------------------*/
typedef struct
{
	char* str;
	int len;
}SHOW_LIST;

SHOW_LIST list[]=
{
	{"Home",8},
	{"Data",6},
	{"Drightnes",12},
	{"PID",5},
};

/*---------------------------------*/

void ui_run(short *a,short *a_t)
{

	
	if(*a < *a_t)
	{
		*a += 1;
	}
	else if(*a >*a_t)
	{
		*a -= 1;
	}
}

void RollTest_Proc(u8g2_t *u8g2)
{
	//y_t = 0;
	u8g2_SetFont(u8g2,u8g2_font_ncenB10_tr);
	int list_len = sizeof(list)/sizeof(SHOW_LIST);
	
	
	u8g2_ClearBuffer(u8g2);
	
	for(int i = 0;i<list_len;i++)
	{ 
		u8g2_DrawStr(u8g2,x+3,y+i*16,list[i].str);//字体刷新
	}
	
	u8g2_DrawRFrame(u8g2,x,box_y,box_wid,13,3);//框
	//HAL_Delay(100);
	ui_run(&box_y,&box_y_trg);
	ui_run(&box_wid,&box_wid_trg);
	u8g2_SendBuffer(u8g2);
}

void key_proc()
{
		int list_len = sizeof(list)/sizeof(SHOW_LIST);
		if(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin) == 0)
		{
			HAL_Delay(150);
			if(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin) == 0){
					ui_list++;
					box_y_trg += 15;
					if(ui_list >= list_len){
						ui_list	 = list_len - 1;
				}
			}
		}
		else if(HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin) == 0)
		{
			
				HAL_Delay(150);
				if(HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin) == 0){
					ui_list--;
					box_y_trg -= 15;
					if(ui_list <= 0){
							ui_list	 = 0;
				}
			}
		}
	box_wid	= list[ui_list].len*7;
}

void u8g2DrawTest(u8g2_t *u8g2)
{
	box_wid = box_wid_trg = list[ui_list].len*7;
	RollTest_Proc(u8g2);
	key_proc();
	
}



