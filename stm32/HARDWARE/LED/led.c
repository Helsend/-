#include "led.h"


//初始化PB0,PB1为输出.并使能这两个口的时钟		    
//LED IO初始化
void LED_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOE_CLK_ENABLE();											     //开启GPIOE时钟
		__HAL_RCC_GPIOA_CLK_ENABLE();	
	
    GPIO_Initure.Pin   = GPIO_PIN_6|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10;//PE8，9，10
    GPIO_Initure.Mode  = GPIO_MODE_OUTPUT_PP;  			       //推挽输出
    GPIO_Initure.Pull  = GPIO_PULLUP;         				     //上拉
    GPIO_Initure.Speed = GPIO_SPEED_FREQ_VERY_HIGH; 	     //高速
    HAL_GPIO_Init(GPIOE,&GPIO_Initure);     					     //初始化
	
		GPIO_Initure.Pin   = GPIO_PIN_8;
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);
	
	
	
    HAL_GPIO_WritePin(GPIOE,GPIO_PIN_8, GPIO_PIN_SET);     //PB0置8
		HAL_GPIO_WritePin(GPIOE,GPIO_PIN_9, GPIO_PIN_SET);	   //PB1置9 
		HAL_GPIO_WritePin(GPIOE,GPIO_PIN_10,GPIO_PIN_SET);	   //PB1置10 
		HAL_GPIO_WritePin(GPIOE,GPIO_PIN_6, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8, GPIO_PIN_SET);
}

