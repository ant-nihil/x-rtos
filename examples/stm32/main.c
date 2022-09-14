#include "includes.h"

// 任务优先级
#define PrioTask0		1
// 任务堆栈大小
#define StackSizeTask0	512
// 建立任务堆栈
uint32_t StackTask0[StackSizeTask0];
// 任务函数
void Task0(void);


// 任务优先级
#define PrioTask1		2
// 任务堆栈大小
#define StackSizeTask1	512
// 建立任务堆栈
uint32_t StackTask1[StackSizeTask1];
// 任务函数
void Task1(void);

void board_config_init(void);
void delay(int count);

int main(int argc, char* argv[])
{
	board_config_init();
	OS_Init();
	OS_TASK_Create(Task0,&StackTask0[StackSizeTask0-1],PrioTask0);		// 创建任务0
	
	OS_Start();
	return 0;
}

void Task0(void)
{
	OS_TASK_Create(Task1,&StackTask1[StackSizeTask1-1],PrioTask1);
	while(1)
	{
		led3_open();

	}
}

void Task1(void)
{
	while(1)
	{
		// led3_close();

	}
}

void board_config_init(void)
{
	led_init();
}

//延时函数
void delay(int count)
{
	int i;
	for(i=1;i<=count;)
	{
		i++;
	}
}


void SysTick_Handler(void)
{
	static uint8_t i;
//	OSTime++;
	static uint16_t iCount=0;
	iCount++;
	if(iCount==500)
	{
		iCount=0;
		// printf("5s has come\r\n");
	}
	
	//UArt_SendByte(T);
	for(i=0;i<OS_TASK_NUM+1;i++)				/*Ë¢ÐÂ¸÷ÈÎÎñÊ±ÖÓ*/
	{
		if(TCB[i].OS_TCB_Dly)
		{
			TCB[i].OS_TCB_Dly--;
			if(TCB[i].OS_TCB_Dly==0)		/*µ±ÈÎÎñÊ±ÖÓµ½´ïÊ±£¬±ØÐëÊÇÓÉ¶¨Ê±Æ÷¼õÊ±µÄ²ÅÐÐ*/
			{
				OS_SetPrioRdy(i);		/*Ê¹ÈÎÎñ¿ÉÒÔÖØÐÂÔËÐÐ*/
			}
		}
	}
}
