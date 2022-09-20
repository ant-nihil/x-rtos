#include "os_task_manager.h"
#include "x_rtos.h"

uint32_t OS_RdyTbl=0;       					//任务就绪表，只支持32个任务
uint32_t OS_Rdy_HighPrio,OS_Rdy_NextTaskPrio;
uint32_t OS_Rdy_CurPrio;						//当前任务的优先级

Task_Ctr_Block TCB[OS_TASK_NUM+1];

Task_Ctr_Block *p_OS_TCB_Cur;		//指向当前任务控制块的指针
Task_Ctr_Block *p_OS_TCB_HighRdy;	//指向最高优先级任务控制块的指针

void OS_TASK_Create(void(*Task)(void),uint32_t *p_Stack,uint32_t TaskID)    //任务创建
{
    if(TaskID<=OS_TASK_NUM)
	{
		*(p_Stack) = (int32_t)Task;				/*PC*/
		*(--p_Stack)=(int32_t)13;				/*LR*/
		*(--p_Stack)=(int32_t)12;				/*R12*/
		*(--p_Stack)=(int32_t)11;				/*R11*/
		*(--p_Stack)=(int32_t)10;				/*R10*/
		*(--p_Stack)=(int32_t)9;				/*R9*/
		*(--p_Stack)=(int32_t)8;				/*R8*/
		*(--p_Stack)=(int32_t)7;				/*R7*/
		*(--p_Stack)=(int32_t)6;				/*R6*/
		*(--p_Stack)=(int32_t)5;				/*R5*/
		*(--p_Stack)=(int32_t)4;				/*R4*/
		*(--p_Stack)=(int32_t)3;				/*R3*/
		*(--p_Stack)=(int32_t)2;				/*R2*/
		*(--p_Stack)=(int32_t)1;				/*R1*/
		*(--p_Stack)=(int32_t)0;				/*R0*/
//		*(--p_Stack)=(int32_t)(SVCMODE|0X0);	/*PSR保存在任务栈中*/
		TCB[TaskID].OS_TCB_StkPtr=(int32_t)p_Stack;/*将人工堆栈的栈顶保存到堆栈的数组中*/
		
		TCB[TaskID].OS_TCB_Dly=0;					/*初始化任务延时时间参数为0*/
		OS_SetPrioRdy(TaskID);					/*在任务就绪表中登记*/
	}
	else
	{
		//printf("TaskID Error\r\n");
		while(1);
	}
}

void OS_Task_Start(void)
{
	OS_Task_GetHighRdy();
	OS_Rdy_CurPrio=OS_Rdy_HighPrio;
	p_OS_TCB_HighRdy=&TCB[OS_Rdy_HighPrio];
	p_OS_TCB_Cur=&TCB[OS_Rdy_CurPrio];
	OS_TASK_StartHighRdy();						//开启最高优先级任务
}

void OS_Task_Switch(void)				// 任务切换
{
	OS_ENTER_CRITICAL();

	OS_EXIT_CRITICAL();
}

void OS_Task_Supend(int8_t prio)  //任务挂起
{
	OS_ENTER_CRITICAL();
	TCB[prio].OS_TCB_Dly=0;			//
	OS_DelPrioRdy(prio);
	OS_EXIT_CRITICAL();
}
void OS_Task_Resume(int8_t prio)  //任务恢复
{
	OS_ENTER_CRITICAL();
	OS_SetPrioRdy(prio);
	TCB[prio].OS_TCB_Dly=0;
	OS_EXIT_CRITICAL();
}
void OS_Task_TimeDly(uint32_t ticks)
{
	if(ticks>0)
	{
		OS_ENTER_CRITICAL();
		OS_DelPrioRdy(OS_Rdy_CurPrio);
		TCB[OS_Rdy_CurPrio].OS_TCB_Dly=ticks;
		OS_EXIT_CRITICAL();

		OS_Sched();		//任务调度
	}
}
