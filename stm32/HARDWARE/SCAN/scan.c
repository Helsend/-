#include "scan.h"
#include "led.h"

void scan_init(void)
{
	GPIO_InitTypeDef gpio_init_struct;
	__HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();
	
	gpio_init_struct.Pin = HANG1_1_PIN;
	gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;            /* 推挽输出 */
  gpio_init_struct.Pull = GPIO_PULLUP;                    /* 上拉 */
  gpio_init_struct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;        /* 高速 */
  HAL_GPIO_Init(HANG1_1_PORT, &gpio_init_struct);					/* 初始化行选1_1引脚 */
	
	gpio_init_struct.Pin = HANG1_2_PIN;                   /* 行选1_2引脚 */
  HAL_GPIO_Init(HANG1_2_PORT, &gpio_init_struct);       /* 初始化行选1_2引脚 */
	
	gpio_init_struct.Pin = HANG1_3_PIN;                   /* 行选1_3引脚 */
  HAL_GPIO_Init(HANG1_3_PORT, &gpio_init_struct);       /* 初始化行选1_3引脚 */
	
	gpio_init_struct.Pin = HANG1_4_PIN;                   /* 行选1_4引脚 */
  HAL_GPIO_Init(HANG1_4_PORT, &gpio_init_struct);       /* 初始化行选1_4引脚 */
	
	gpio_init_struct.Pin = HANG2_1_PIN;                   /* 行选2_1引脚 */
  HAL_GPIO_Init(HANG2_1_PORT, &gpio_init_struct);       /* 初始化行选2_1引脚 */
	
	gpio_init_struct.Pin = HANG2_2_PIN;                   /* 行选2_2引脚 */
  HAL_GPIO_Init(HANG2_2_PORT, &gpio_init_struct);       /* 初始化行选2_2引脚 */
	
	gpio_init_struct.Pin = HANG2_3_PIN;                   /* 行选2_3引脚 */
  HAL_GPIO_Init(HANG2_3_PORT, &gpio_init_struct);       /* 初始化行选2_3引脚 */
	
	gpio_init_struct.Pin = HANG2_4_PIN;                   /* 行选2_4引脚 */
  HAL_GPIO_Init(HANG2_4_PORT, &gpio_init_struct);       /* 初始化行选2_4引脚 */
	
	gpio_init_struct.Pin = LIE2_1_PIN;                   /* 列选2_1引脚 */
  HAL_GPIO_Init(LIE2_1_PORT, &gpio_init_struct);       /* 初始化列选2_1引脚 */
	
	gpio_init_struct.Pin = LIE2_2_PIN;                   
  HAL_GPIO_Init(LIE2_2_PORT, &gpio_init_struct);
	
	gpio_init_struct.Pin = LIE2_3_PIN;                   
  HAL_GPIO_Init(LIE2_3_PORT, &gpio_init_struct);
	
	gpio_init_struct.Pin = LIE2_4_PIN;                   
  HAL_GPIO_Init(LIE2_4_PORT, &gpio_init_struct);
	
	gpio_init_struct.Pin = LIE2_5_PIN;                   
  HAL_GPIO_Init(LIE2_5_PORT, &gpio_init_struct);
	
	gpio_init_struct.Pin = LIE2_6_PIN;                   
  HAL_GPIO_Init(LIE2_6_PORT, &gpio_init_struct);
	
	gpio_init_struct.Pin = LIE2_7_PIN;                   
  HAL_GPIO_Init(LIE2_7_PORT, &gpio_init_struct);
	
	gpio_init_struct.Pin = LIE2_8_PIN;                   
  HAL_GPIO_Init(LIE2_8_PORT, &gpio_init_struct);
	
	gpio_init_struct.Pin = LIE2_9_PIN;                   
  HAL_GPIO_Init(LIE2_9_PORT, &gpio_init_struct);
	
	gpio_init_struct.Pin = LIE2_10_PIN;                   
  HAL_GPIO_Init(LIE2_10_PORT, &gpio_init_struct);
	
	gpio_init_struct.Pin = LIE2_11_PIN;                   
  HAL_GPIO_Init(LIE2_11_PORT, &gpio_init_struct);
	
	gpio_init_struct.Pin = LIE2_12_PIN;                   
  HAL_GPIO_Init(LIE2_12_PORT, &gpio_init_struct);
	
	gpio_init_struct.Pin = LIE2_13_PIN;                   
  HAL_GPIO_Init(LIE2_13_PORT, &gpio_init_struct);
	
	gpio_init_struct.Pin = LIE2_14_PIN;                   
  HAL_GPIO_Init(LIE2_14_PORT, &gpio_init_struct);
	
	gpio_init_struct.Pin = LIE2_15_PIN;                   
  HAL_GPIO_Init(LIE2_15_PORT, &gpio_init_struct);
	
	gpio_init_struct.Pin = LIE2_16_PIN;                   
  HAL_GPIO_Init(LIE2_16_PORT, &gpio_init_struct);
	
	
	
	gpio_init_struct.Pin = LIE1_1_PIN;                   /* 列选1_1引脚 */
  HAL_GPIO_Init(LIE1_1_PORT, &gpio_init_struct);       /* 初始化列选1_1引脚 */
	
	gpio_init_struct.Pin = LIE1_2_PIN;                   
  HAL_GPIO_Init(LIE1_2_PORT, &gpio_init_struct);
	
	gpio_init_struct.Pin = LIE1_3_PIN;                   
  HAL_GPIO_Init(LIE1_3_PORT, &gpio_init_struct);
	
	gpio_init_struct.Pin = LIE1_4_PIN;                   
  HAL_GPIO_Init(LIE1_4_PORT, &gpio_init_struct);
	
	gpio_init_struct.Pin = LIE1_5_PIN;                   
  HAL_GPIO_Init(LIE1_5_PORT, &gpio_init_struct);
	
	gpio_init_struct.Pin = LIE1_6_PIN;                   
  HAL_GPIO_Init(LIE1_6_PORT, &gpio_init_struct);
	
	gpio_init_struct.Pin = LIE1_7_PIN;                   
  HAL_GPIO_Init(LIE1_7_PORT, &gpio_init_struct);
	
	gpio_init_struct.Pin = LIE1_8_PIN;                   
  HAL_GPIO_Init(LIE1_8_PORT, &gpio_init_struct);
	
	gpio_init_struct.Pin = LIE1_9_PIN;                   
  HAL_GPIO_Init(LIE1_9_PORT, &gpio_init_struct);
	
	gpio_init_struct.Pin = LIE1_10_PIN;                   
  HAL_GPIO_Init(LIE1_10_PORT, &gpio_init_struct);
	
	gpio_init_struct.Pin = LIE1_11_PIN;                   
  HAL_GPIO_Init(LIE1_11_PORT, &gpio_init_struct);
	
	gpio_init_struct.Pin = LIE1_12_PIN;                   
  HAL_GPIO_Init(LIE1_12_PORT, &gpio_init_struct);
	
	gpio_init_struct.Pin = LIE1_13_PIN;                   
  HAL_GPIO_Init(LIE1_13_PORT, &gpio_init_struct);
	
	gpio_init_struct.Pin = LIE1_14_PIN;                   
  HAL_GPIO_Init(LIE1_14_PORT, &gpio_init_struct);
	
	gpio_init_struct.Pin = LIE1_15_PIN;                   
  HAL_GPIO_Init(LIE1_15_PORT, &gpio_init_struct);
	
	gpio_init_struct.Pin = LIE1_16_PIN;                   
  HAL_GPIO_Init(LIE1_16_PORT, &gpio_init_struct);
	
	gpio_init_struct.Pin = REFIN1_PIN;                   
  HAL_GPIO_Init(REFIN1_PORT, &gpio_init_struct);  

  gpio_init_struct.Pin = REFIN2_PIN;                   
  HAL_GPIO_Init(REFIN2_PORT, &gpio_init_struct); 
	
	
	HANG1_1(0);HANG1_2(0);HANG1_3(0);HANG1_4(0);REFIN1(1);
	HANG2_1(0);HANG2_2(0);HANG2_3(0);HANG2_4(0);REFIN2(1);
	LIE1_1(0);LIE1_2(0);LIE1_3(0);LIE1_4(0);LIE1_5(0);LIE1_6(0);LIE1_7(0);LIE1_8(0);
	LIE1_9(0);LIE1_10(0);LIE1_11(0);LIE1_12(0);LIE1_13(0);LIE1_14(0);LIE1_15(0);LIE1_16(0);
	LIE2_1(0);LIE2_2(0);LIE2_3(0);LIE2_4(0);LIE2_5(0);LIE2_6(0);LIE2_7(0);LIE2_8(0);
	LIE2_9(0);LIE2_10(0);LIE2_11(0);LIE2_12(0);LIE2_13(0);LIE2_14(0);LIE2_15(0);LIE2_16(0);
	
}

void scan1(void)
{
		HANG2_1(0);HANG2_2(0);HANG2_3(0);HANG2_4(0);

}

void scan2(void)
{
		HANG2_1(1);HANG2_2(0);HANG2_3(0);HANG2_4(0);

}

void scan3(void)
{
		HANG2_1(0);HANG2_2(1);HANG2_3(0);HANG2_4(0);

}


void scan4(void)
{
		HANG2_1(1);HANG2_2(1);HANG2_3(0);HANG2_4(0);

}

void scan5(void)
{
		HANG2_1(0);HANG2_2(0);HANG2_3(1);HANG2_4(0);

}

void scan6(void)
{
		HANG2_1(1);HANG2_2(0);HANG2_3(1);HANG2_4(0);

}

void scan7(void)
{
		HANG2_1(0);HANG2_2(1);HANG2_3(1);HANG2_4(0);

}

void scan8(void)
{
		HANG2_1(1);HANG2_2(1);HANG2_3(1);HANG2_4(0);

}

void scan9(void)
{
		HANG2_1(0);HANG2_2(0);HANG2_3(0);HANG2_4(1);

}

void scan10(void)
{
		HANG2_1(1);HANG2_2(0);HANG2_3(0);HANG2_4(1);

}

void scan11(void)
{
		HANG2_1(0);HANG2_2(1);HANG2_3(0);HANG2_4(1);

}

void scan12(void)
{
		HANG2_1(1);HANG2_2(1);HANG2_3(0);HANG2_4(1);

}

void scan13(void)
{
		HANG2_1(0);HANG2_2(0);HANG2_3(1);HANG2_4(1);

}

void scan14(void)
{
		HANG2_1(1);HANG2_2(0);HANG2_3(1);HANG2_4(1);

}

void scan15(void)
{
		HANG2_1(0);HANG2_2(1);HANG2_3(1);HANG2_4(1);

}

void scan16(void)
{
		HANG2_1(1);HANG2_2(1);HANG2_3(1);HANG2_4(1);

}
