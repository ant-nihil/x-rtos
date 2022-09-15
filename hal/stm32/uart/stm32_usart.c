#include "stm32_usart.h"

#if 1
#pragma import(__use_no_semihosting)             
            
struct __FILE 
{
	int handle; 
}; 

FILE __stdout;
 
void _sys_exit(int x)
{ 
	x = x;
} 

int fputc(int ch, FILE *f)
{
	while((USART1->SR&0X40)==0);
	USART1->DR = (u8) ch;
	return ch;
}
#endif

#if EN_USART1_RX
u8 USART_RX_BUF[USART_REC_LEN];

uint16_t USART_RX_STA=0;

void usart_init(uint32_t bound)
{

    GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
 
	//
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1); //GPIOA9
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1); //GPIOA10
	
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

   //USART1
	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1, &USART_InitStructure);
	
    USART_Cmd(USART1, ENABLE);
	
	//USART_ClearFlag(USART1, USART_FLAG_TC);
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	//Usart1 NVIC
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

}

void USART1_IRQHandler(void)
{
	uint16_t Res;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
        if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
        {
            Res =USART_ReceiveData(USART1);//(USART1->DR);
            
            if((USART_RX_STA&0x8000)==0)
            {
                if(USART_RX_STA&0x4000)
                {
                    if(Res!=0x0a)USART_RX_STA=0;
                    else USART_RX_STA|=0x8000;
                }
                else
                {	
                    if(Res==0x0d)USART_RX_STA|=0x4000;
                    else
                    {
                        USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
                        USART_RX_STA++;
                        if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;	  
                    }		 
                }
            }   		 
        } 
	}

}

#endif
