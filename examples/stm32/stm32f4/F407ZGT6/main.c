#include <includes.h>


void board_init(void);

int main(int argc, char* argv[])
{
	board_init();
	
	printf("code start\r\n");
	while(1)
	{
		
	}
}

void board_init(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	usart_init(115200);
	
}

