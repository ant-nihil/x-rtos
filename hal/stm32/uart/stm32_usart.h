#ifndef __STM32_USART_H
#define __STM32_USART_H

#include <stm32f4xx.h>
#include "stdio.h"

#define USART_REC_LEN  			200  	//
#define EN_USART1_RX 			1


extern u8  USART_RX_BUF[USART_REC_LEN]; //
extern u16 USART_RX_STA;         		//

void usart_init(uint32_t bound);

#endif  // __STM32_USART_H
