#include "led.h"


//��ʼ��PB0,PB1Ϊ���.��ʹ���������ڵ�ʱ��		    
//LED IO��ʼ��
void LED_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOE_CLK_ENABLE();											     //����GPIOEʱ��
		__HAL_RCC_GPIOA_CLK_ENABLE();	
	
    GPIO_Initure.Pin   = GPIO_PIN_6|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10;//PE8��9��10
    GPIO_Initure.Mode  = GPIO_MODE_OUTPUT_PP;  			       //�������
    GPIO_Initure.Pull  = GPIO_PULLUP;         				     //����
    GPIO_Initure.Speed = GPIO_SPEED_FREQ_VERY_HIGH; 	     //����
    HAL_GPIO_Init(GPIOE,&GPIO_Initure);     					     //��ʼ��
	
		GPIO_Initure.Pin   = GPIO_PIN_8;
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);
	
	
	
    HAL_GPIO_WritePin(GPIOE,GPIO_PIN_8, GPIO_PIN_SET);     //PB0��8
		HAL_GPIO_WritePin(GPIOE,GPIO_PIN_9, GPIO_PIN_SET);	   //PB1��9 
		HAL_GPIO_WritePin(GPIOE,GPIO_PIN_10,GPIO_PIN_SET);	   //PB1��10 
		HAL_GPIO_WritePin(GPIOE,GPIO_PIN_6, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8, GPIO_PIN_SET);
}

