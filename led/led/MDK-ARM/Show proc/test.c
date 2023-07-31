/*
	作者:小黄;
	更新时间:2023年7月31日20:08:38;
	程序主要作用:个人UI学习,u8g2库使用
*/

#include "test.h"
#include "stdio.h"

short x , x_t;//字体的X
short y = 11 , y_t = 11;//字体的Y

short box_y,box_y_trg;//框的Y
short box_wid,box_wid_trg;//框的宽

extern char ui_list;
/*---------------------------------*/

typedef struct
{
	char* str;
	int len;
	char over;
}SHOW_LIST;

SHOW_LIST list[]=
{
	{"Home",8,0},
	{"Data",6,0},
	{"Drightnes",12,0},
	{"PID",5,0},
	{"12411",7,0},
	{"   ---It's Over---",17,1}
};

SHOW_LIST fun1[]=
{
	{"Home",8,0},
	{"   ---It's Over---",17,1}
};

/*---------------------------------*/

void ui_data_init()
{
		box_wid = box_wid_trg = list[ui_list].len*7;
}

void up_key(void)
{

	if (ui_list <= 0)
	{
		ui_list	 = 0;
	}
	else
	{
		ui_list --;
		if(box_y_trg > 0)
		{
			box_y_trg -= 15;
		}else{y_t += 16;}
	}
}

void down_key(void)
{
	int list_len = sizeof(list)/sizeof(SHOW_LIST);
	if(ui_list >= list_len)
	{
		ui_list	 = list_len - 1;						
	}
	else
	{
		if (list[ui_list].over == 0){
			ui_list++;
			if(box_y_trg < 45) 				//控制字体上下和方框上下选择
			{
				if(box_y_trg <= 60)
				{
					box_y_trg += 15;
				}
			}
			else{y_t -= 16;}					//到底部不进行增加
		} 
	}
}

/*---------------------------------*/

void ui_run(short *a,short *a_t,char step,char show_step)
{ 
	char temp;
	temp = (*a_t - *a) >step  ? show_step : 1;
	if(*a < *a_t)
	{
		*a += temp;
	}

	else if(*a >*a_t)
	{
		*a -= temp;
	}
}

/*---------------------------------*/

void fun(u8g2_t *u8g2)
{
	int list_len = sizeof(fun1)/sizeof(SHOW_LIST);
	for(int i = 0;i < list_len;i++)
	{ 
		u8g2_DrawStr(u8g2,x+3,y+i*16,fun1[i].str);
	}
}

/*---------------------------------*/

void RollTest_Proc(u8g2_t *u8g2)
{
	int list_len = sizeof(list)/sizeof(SHOW_LIST);
	u8g2_SetFont(u8g2,u8g2_font_ncenB10_tr);
	
	u8g2_ClearBuffer(u8g2);

		for(int i = 0;i < list_len;i++)
		{ 
			u8g2_DrawStr(u8g2,x+3,y+i*16,list[i].str);//字体刷新
		}
		
	u8g2_DrawRFrame(u8g2,x,box_y,box_wid,15,3);//框

	ui_run(&y,&y_t,6,6);
	ui_run(&box_y,&box_y_trg,5,5);
	ui_run(&box_wid,&box_wid_trg,3,5);

	u8g2_SendBuffer(u8g2);
}

void u8g2Dra_init(u8g2_t *u8g2)
{
		RollTest_Proc(u8g2);
}




