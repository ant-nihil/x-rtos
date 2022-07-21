#include "x_rtos.h"
#include "defines.h"
#include "os_task_manager.h"

// 包含底层的时钟节拍功能所在的文件
#include "heart_stm32.h"

uint32_t cpu_sr;    //进入临界代码区时保存CPU状态


#define Prio_IdleTask		30
#define StacSize_IdleTask	512
uint32_t Stack_IdleTask[StacSize_IdleTask];

void OS_IdleTask(void)
{
    while(1)
    {
        
    }
}

// os init
void OS_Init(void)
{
    OS_StartTicker(OS_TICKS_PER_SEC);
    OS_TASK_Create(OS_IdleTask,&Stack_IdleTask[StacSize_IdleTask-1],Prio_IdleTask);
}

// os start
void OS_Start(void)
{
    OS_Task_GetHighRdy();   //找出优先级最高的任务
    OS_Rdy_CurPrio=OS_Rdy_HighPrio;     //将最高优先级的任务标志赋给当前任务标志
    p_OS_TCB_HighRdy=&TCB[OS_Rdy_HighPrio];
    p_OS_TCB_Cur=p_OS_TCB_HighRdy;
    OS_TASK_StartHighRdy();
    // led3_open();

}

void OS_StartTicker(uint32_t os_ticks)
{
    // 此处添加目标板的开启时钟节拍的函数，属于需要通过移植来匹配的功能
    StartTicker(os_ticks);
}

void OS_Sched(void)
{
    OS_ENTER_CRITICAL();
    OS_Task_GetHighRdy();
    if(OS_Rdy_CurPrio!=OS_Rdy_HighPrio)
    {
        p_OS_TCB_Cur=&TCB[OS_Rdy_CurPrio];
        p_OS_TCB_HighRdy=&TCB[OS_Rdy_HighPrio];
        OS_Rdy_CurPrio=OS_Rdy_HighPrio;

        OS_EXIT_CRITICAL();

        OS_SW();
    }
}
