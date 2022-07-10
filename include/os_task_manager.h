#ifndef __OS_TASK_MANAGER_H
#define __OS_TASK_MANAGER_H

/*
存放任务管理相关内容
*/
#include "defines.h"

#define OS_TASK_NUM 30

extern uint32_t OS_RdyTbl;       					//任务就绪表，只支持32个任务
extern uint32_t OS_Rdy_HighPrio,OS_Rdy_NextTaskPrio;

typedef struct _TaskCtrBlock_T {    //任务控制块
	uint32_t	OS_TCB_StkPtr;        //保存任务的堆栈顶
	uint32_t	OS_TCB_Dly;           //任务延时时间的存储参数
}Task_Ctr_Block;


//在就绪表中登记任务
#define SetPrioRdy(prio) {	    \
	OS_RdyTbl|=(0x01<<prio);	\
}

//在就绪表中删除任务/挂起任务
#define DelPrioRdy(prio) {	    \
	OS_RdyTbl&=~(0x01<<prio);	\
}

#define OS_Task_GetHighRdy()				\
{											\
	for(OS_Rdy_NextTaskPrio=0;				\
	   (OS_Rdy_NextTaskPrio<OS_TASK_NUM)&&(!(OS_RdyTbl&(0x01<<OS_Rdy_NextTaskPrio)));\
		OS_Rdy_NextTaskPrio++);				\
	OS_Rdy_HighPrio=OS_Rdy_NextTaskPrio;	\
}

//ASM code
void OS_TASK_StartHighRdy	(void);

void OS_TASK_IdleTask(void);        //空任务
void OS_TASK_Create(void(*Task)(void),uint32_t *p_Stack,uint32_t TaskID);    //任务创建

void OS_Task_Start(void);			//任务开始

void OS_Task_Supend(int8_t prio);   //任务挂起
void OS_Task_Resume(int8_t prio);   //任务恢复

void OS_SetPrioRdy(uint8_t task_id);

#endif  // __OS_TASK_MANAGER_H
