#include "stm32f4xx.h"
#include "led_stm32.h"

int main(int argc, int* argv[])
{
	led_init();
	led_open_all();
	while(1)
	{
		
	}
}
