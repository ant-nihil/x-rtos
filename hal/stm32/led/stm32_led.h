#ifndef __STM32_LED_H
#define __STM32_LED_H

#include <stm32f4xx.h>

void led_init(void);
void led_all_close(void);
void led_all_open(void);

void led1_open_red(void);
void led1_open_green(void);
void led1_close(void);

void led3_open(void);
void led3_close(void);

void led4_open_red(void);
void led4_open_green(void);
void led4_close(void);

#endif // __STM32_LED_H
