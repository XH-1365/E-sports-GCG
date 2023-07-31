/*
	����:С��;
	����ʱ��:2023��7��31��20:08:38;
	������Ҫ����:����UIѧϰ,u8g2��ʹ��
*/

#include "test.h"
#include "stdio.h"

short x , x_t;
short y = 11 , y_t = 11;//�����Y

short box_y,box_y_trg;//���Y
short box_wid,box_wid_trg;//��Ŀ�

char ui_list = 0;//�б�λ��ȷ��
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
	{"-It's Over-",12,1}
};
/*---------------------------------*/
void ui_data()
{
		box_wid = box_wid_trg = list[ui_list].len*7;
}

void up_key(int list_len)
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

void down_key(int list_len)
{
	if(ui_list >= list_len)
	{
		ui_list	 = list_len - 1;						
	}
	else
	{
		if (list[ui_list].over == 0){
			ui_list++;
			if(box_y_trg < 45) 				//�����������ºͷ�������ѡ��
			{
				if(box_y_trg <= 60)
				{
					box_y_trg += 15;
				}
			}
			else{y_t -= 16;}					//���ײ�����������
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

void RollTest_Proc(u8g2_t *u8g2)
{
	int list_len = sizeof(list)/sizeof(SHOW_LIST);
	u8g2_SetFont(u8g2,u8g2_font_ncenB10_tr);
	
	u8g2_ClearBuffer(u8g2);

		for(int i = 0;i < list_len;i++)
		{ 
			u8g2_DrawStr(u8g2,x+3,y+i*16,list[i].str);//����ˢ��
		}
		
	u8g2_DrawRFrame(u8g2,x,box_y,box_wid,15,3);//��

	ui_run(&y,&y_t,6,6);
	ui_run(&box_y,&box_y_trg,4,5);
	ui_run(&box_wid,&box_wid_trg,3,5);

	u8g2_SendBuffer(u8g2);
}
/*
	���������Ҫ�����ڰ�ť��ѡ������ϵ�
*/
void key_proc()
{
		int list_len = sizeof(list)/sizeof(SHOW_LIST);
		if(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin) == 0)
		{
			HAL_Delay(150);
			if(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin) == 0){
				down_key(list_len);
			}
		}
		else if(HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin) == 0)
		{
			HAL_Delay(150);
			if(HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin) == 0){
				up_key(list_len);
			}
		}
}



void u8g2DrawTest(u8g2_t *u8g2)
{
		ui_data();
		RollTest_Proc(u8g2);
		key_proc();
}




