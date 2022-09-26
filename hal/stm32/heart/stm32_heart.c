#include "stm32_heart.h"

uint32_t StartTicker(uint32_t TicksPerSec) // 每秒的节拍数
{
// 	uint32_t reload=21000000/TicksPerSec;
// 	if ((reload - 1) > SysTick_LOAD_RELOAD_Msk)  return (1);    /* Reload value impossible */

// //  NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1); /* set Priority for Systick Interrupt */


// 	SysTick->LOAD =reload-1;
// 	SysTick->VAL  = 0;
// 	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
// 	SysTick->CTRL|=(0x01<<1)
// 				 |(0x01<<0);			// 打开systick的中断和使能
// 	return (0);
	uint32_t reload=6720000/TicksPerSec; // 暂定为此数，后面需要从原理验证
	if ((reload - 1) > SysTick_LOAD_RELOAD_Msk)  return (1);      /* Reload value impossible */

//  NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);  /* set Priority for Systick Interrupt */


	SysTick->LOAD =reload-1;
	SysTick->VAL  = 0;
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
	SysTick->CTRL|=(0x01<<1)
				 |(0x01<<0);			// 打开systick的中断和使能
	return (0);
}
