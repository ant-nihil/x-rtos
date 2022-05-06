#ifndef __OS_TASK_MANAGER_H
#define __OS_TASK_MANAGER_H

#include "defines.h"

#define OS_TASK_NUM 30

typedef struct _TaskCtrBlock_T {    //任务控制块
	uint32_t	OSTCBStkPtr;        //保存任务的堆栈顶
	uint32_t	OSTCBDly;           //任务延时时间的存储参数
}Task_Ctr_Block;



void OS_TASK_IdleTask(void);        //空任务
void OS_TASK_Create(void(*Task)(void),uint32_t *p_Stack,uint32_t TaskID);    //任务创建


void OS_Task_Supend(int8_t prio);   //任务挂起
void OS_Task_Resume(int8_t prio);   //任务恢复

void OS_SetPrioRdy(uint8_t task_id);

#endif  // __OS_TASK_MANAGER_H
