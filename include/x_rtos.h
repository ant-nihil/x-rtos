#ifndef __X_RTOS_H
#define __X_RTOS_H

/*
存放关于时钟节拍的内容，OS初始化和OS启动
*/

#include "defines.h"

// 时钟节拍数
#define OS_TICKS_PER_SEC	100

//ASM code
uint32_t OS_CPU_SaveSR	    (void);				/*声明*/
void     OS_CPU_RestoreSR	(uint32_t cpu_sr);	/*声明*/

//临界区资源处理
/*进入临界区*/
#define 	OS_ENTER_CRITICAL()		do{cpu_sr=OS_CPU_SaveSR();	}while(0)		//关闭总中断
/*退出临界区*/
#define 	OS_EXIT_CRITICAL()		do{OS_CPU_RestoreSR(cpu_sr);}while(0)		//恢复中断状态

void OS_Init(void);
void OS_Start(void);

void OS_StartTicker(uint32_t os_ticks);




#endif  // __X_RTOS_H
