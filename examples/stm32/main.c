#include "stm32f4_includes.h"

// 任务优先级
#define PrioTask0		1
// 任务堆栈大小
#define StackSizeTask0	512
// 建立任务堆栈
uint32_t StackTask0[StackSizeTask0];
// 任务函数
void Task0(void);


void target_init(void);

int main(int argc, char* argv[])
{
	target_init();
	OS_Init();
	OS_TASK_Create(Task0,&StackTask0[StackSizeTask0-1],PrioTask0);		// 创建任务0
	while(1)
	{
		
	}
}

void Task0(void)
{
	led3_open();
}

void target_init(void)
{
	led_init();
}

void SysTick_Handler(void)
{
	static uint8_t i=0;
	if(i==0){
		led3_open();i=1;
	}
	else if(i==1){
		led3_close();i=0;
	}
	
}
