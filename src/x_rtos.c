#include "x_rtos.h"
#include "defines.h"
#include "os_task_manager.h"

// 包含底层的时钟节拍功能所在的文件
#include "heart_stm32.h"

#define Prio_IdleTask		30
#define StacSizeIdleTask	512
uint32_t Stack_IdleTask[StacSizeIdleTask];

void IdleTask(void)
{

}

// os init
void OS_Init(void)
{
    OS_StartTicker(OS_TICKS_PER_SEC);
    OS_TASK_Create(IdleTask,&Stack_IdleTask[StacSizeIdleTask-1],Prio_IdleTask);
}

// os start
void OS_Start(void)
{

}



void OS_StartTicker(uint32_t os_ticks)
{
    // 此处添加目标板的开启时钟节拍的函数，属于需要通过移植来匹配的功能
    StartTicker(os_ticks);
}
