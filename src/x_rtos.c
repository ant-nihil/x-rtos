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
    uint32_t Idle_Count=0;
    while(1)
    {
        OS_ENTER_CRITICAL();
        Idle_Count++;
        if(Idle_Count==500000) {
            Idle_Count=0;
            printf("OS_IdleTask is running\r\n");
        }
        OS_EXIT_CRITICAL();
        if(OS_RdyTbl!=(0x1<<Prio_IdleTask)) {
            // prtntf("OS_IdleTask is over, enter task sched\r\n");
            OS_Task_Switch();       // 当任务就绪表除了空任务还有其他的任务就绪时，进入任务切换
        }

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

// os start ticker, os layer, realize by call board function
void OS_StartTicker(uint32_t os_ticks)
{
    // 此处添加目标板的开启时钟节拍的函数，属于需要通过移植来匹配的功能
    StartTicker(os_ticks);
}

// interruption service management function, board layer, 


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
