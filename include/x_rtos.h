#ifndef __X_RTOS_H
#define __X_RTOS_H

#include "defines.h"

// 时钟节拍数
#define OS_TICKS_PER_SEC	100

void OS_Init(void);
void OS_Start(void);

void OS_StartTicker(uint32_t os_ticks);


#endif  // __X_RTOS_H
