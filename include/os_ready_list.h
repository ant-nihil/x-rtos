#ifndef __OS_READY_LIST_H
#define __OS_READY_LIST_H

#include "defines.h"

extern int32_t OSRdyTbl;

//在就绪表中等级任务
#define SetPrioRdy(prio) {	        \
	OS_TASK_RdyTbl|=(0x01<<prio);	\
}

//在就绪表中删除任务/挂起任务
#define DelPrioRdy(prio) {	        \
	OS_TASK_RdyTbl&=~(0x01<<prio);	\
}

//在就绪表中查找任务优先级更高的任务
#define OSGetHighRdy()				\
{									\
	for(OSNextTaskPrio=0;			\
	   (OSNextTaskPrio<OS_TASKS)&&(!(OSRdyTbl&(0x01<<OSNextTaskPrio)));\
		OSNextTaskPrio++);			\
	OSPrioHighRdy=OSNextTaskPrio;	\
}

#endif  // __OS_READY_LIST_H
