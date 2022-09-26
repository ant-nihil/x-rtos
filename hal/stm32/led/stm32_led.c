#include "stm32_led.h"

//LED初始化
void led_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    //打开需要用到的引脚所在通道的时钟
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

    //把LED引脚口全部配置成输出模式(推挽输出)
    /*LED_GREEN_L PA6	LED_RED_L PA7*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

	/*LED_BLUE_L PB12*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

	/*LED_GREEN_R PC13	LED_RED_R PC14*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	led_all_close();	//关闭所有LED灯
}

//关闭所有LED灯
void led_all_close(void)
{
    /*关闭左后方蓝色灯，右后方蓝色灯不受stm32f4控制*/
	GPIO_ResetBits(GPIOB,  GPIO_Pin_12); //LED_BLUE_L
	/*关闭前面两个双色灯*/
	GPIO_SetBits(GPIOA,  GPIO_Pin_6 ); //LED_GREEN_L
	GPIO_SetBits(GPIOA,  GPIO_Pin_7 ); //LED_RED_L
	GPIO_SetBits(GPIOC,  GPIO_Pin_13); //LED_GREEN_R
	GPIO_SetBits(GPIOC,  GPIO_Pin_14); //LED_RED_R
}

//打开所有LED灯
void led_all_open(void)
{
    /*打开蓝色 LED*/
	GPIO_SetBits(  GPIOB,  GPIO_Pin_12); //LED_BLUE_L
	
	/*打开前面的两个LED为绿色*/
	GPIO_SetBits(  GPIOA,  GPIO_Pin_6 ); //LED_GREEN_L
	GPIO_ResetBits(GPIOA,  GPIO_Pin_7 ); //LED_RED_L
	GPIO_SetBits(  GPIOC,  GPIO_Pin_13); //LED_GREEN_R
	GPIO_ResetBits(GPIOC,  GPIO_Pin_14); //LED_RED_R
}

// led1_red
void led1_open_red(void)
{
	GPIO_ResetBits(  GPIOC,  GPIO_Pin_13); 	//LED_GREEN_R
	GPIO_SetBits(GPIOC,  GPIO_Pin_14); 		//LED_RED_R
}

// led1_green
void led1_open_green(void)
{
	GPIO_SetBits(  GPIOC,  GPIO_Pin_13); 	//LED_GREEN_R
	GPIO_ResetBits(GPIOC,  GPIO_Pin_14); 	//LED_RED_R
}

// led1_close
void led1_close(void)
{
	GPIO_SetBits(  GPIOC,  GPIO_Pin_13); 	//LED_GREEN_R
	GPIO_SetBits(GPIOC,  GPIO_Pin_14); 		//LED_RED_R
}

// led3_open:bule
void led3_open(void)
{
	GPIO_SetBits(  GPIOB,  GPIO_Pin_12); 	//LED_BLUE_L
}

// led3_close:none
void led3_close(void)
{
	GPIO_ResetBits(  GPIOB,  GPIO_Pin_12); 	//LED_BLUE_L
}

// led4_red
void led4_open_red(void)
{
	GPIO_ResetBits(  GPIOA,  GPIO_Pin_6 ); 	//LED_GREEN_L
	GPIO_SetBits(GPIOA,  GPIO_Pin_7 ); 		//LED_RED_L
}

// led4_green
void led4_open_green(void)
{
	GPIO_SetBits(  GPIOA,  GPIO_Pin_6 ); 	//LED_GREEN_L
	GPIO_ResetBits(GPIOA,  GPIO_Pin_7 ); 	//LED_RED_L
}

// led4_close
void led4_close(void)
{
	GPIO_SetBits(  GPIOA,  GPIO_Pin_6 ); 	//LED_GREEN_L
	GPIO_SetBits(GPIOA,  GPIO_Pin_7 ); 		//LED_RED_L
}
