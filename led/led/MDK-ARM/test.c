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
	{"12411",7},
};

void ui_data()
{
	box_wid = box_wid_trg = list[ui_list].len*7;
}

/*---------------------------------*/

void ui_run(short *a,short *a_t,char step,char show_step)
{ 
	char temp;
	temp = (*a_t - *a) > show_step ? step : 1;
	if(*a < *a_t)
	{
		*a += temp;
	}

	else if(*a >*a_t)
	{
		*a -= temp;
	}
}

void RollTest_Proc(u8g2_t *u8g2)
{
	u8g2_SetFont(u8g2,u8g2_font_ncenB10_tr);
	
	u8g2_ClearBuffer(u8g2);

		for(int i = 0;i < 4;i++)
		{ 
			
			u8g2_DrawStr(u8g2,x+3,y+i*16,list[i].str);//字体刷新
		}
		
	u8g2_DrawRFrame(u8g2,x,box_y,box_wid,13,3);//框

	ui_run(&y,&y_t,5,5);
	ui_run(&box_y,&box_y_trg,4,5);
	ui_run(&box_wid,&box_wid_trg,3,5);

	u8g2_SendBuffer(u8g2);
}
/*
	这个区域主要是用在按钮的选择界面上的
*/
void key_proc()
{
		int list_len = sizeof(list)/sizeof(SHOW_LIST);
		if(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin) == 0)
		{
			HAL_Delay(150);
			if(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin) == 0){
				
					if(ui_list >= list_len)
					{
						ui_list	 = list_len - 1;
						
					}else
					{
						ui_list++;
						if(box_y_trg < 45) 				//控制字体上下和方框上下选择
						{
							if(box_y_trg <= 60)
							{
								box_y_trg += 15;
							}
						}else{y_t -= 15;}
					}
			}
		}
		else if(HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin) == 0)
		{
			
				HAL_Delay(150);
				if(HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin) == 0){
					if (ui_list <= 0)
					{
						ui_list	 = 0;
					}else
					{
						ui_list --;
						if(box_y_trg > 0)
						{
							box_y_trg -= 15;
						}else{y_t += 15;}
					}
			}
		}
}



void u8g2DrawTest(u8g2_t *u8g2)
{
		ui_data();
		RollTest_Proc(u8g2);
		key_proc();
}




