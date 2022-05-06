#include "os_task_manager.h"

Task_Ctr_Block TCB[OS_TASK_NUM+1];

void OS_TASK_IdleTask(void)    //空任务
{
    
}
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
		TCB[TaskID].OSTCBStkPtr=(int32_t)p_Stack;/*将人工堆栈的栈顶保存到堆栈的数组中*/
		
		TCB[TaskID].OSTCBDly=0;					/*初始化任务延时时间参数为0*/
		OS_SetPrioRdy(TaskID);					/*在任务就绪表中登记*/
	}
	else
	{
		//printf("TaskID Error\r\n");
		while(1);
	}
}


void OS_Task_Supend(int8_t prio)  //任务挂起
{

}
void OS_Task_Resume(int8_t prio)  //任务恢复
{

}

void OS_SetPrioRdy(uint8_t task_id)
{
	
}
