#include "os_task_manager.h"

Task_Ctr_Block TCB[OS_TASK_NUM+1];

void OS_TASK_IdleTask(void)    //空任务
{
    
}
void OS_TASK_Create(void(*Task)(void),int32_t *p_Stack,int8_t TaskID)    //任务创建
{

}


void OS_Task_Supend(int8_t prio)  //任务挂起
{

}
void OS_Task_Resume(int8_t prio)  //任务恢复
{

}
