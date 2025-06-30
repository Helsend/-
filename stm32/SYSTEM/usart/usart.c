#include "usart.h"
////////////////////////////////////////////////////////////////////////////////// 	 
//如果使用os,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//os 使用	  
#endif
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32H7开发板
//串口1初始化		   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2017/6/8
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved
//********************************************************************************
//V1.0修改说明 
////////////////////////////////////////////////////////////////////////////////// 	  
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
//#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)	
#if 1
//#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{ 	
	while((USART1->ISR&0X40)==0);//循环发送,直到发送完毕   
	USART1->TDR=(u8)ch;      
	return ch;
}
#endif 





#if EN_USART_RX   //如果使能了接收

//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	
u8 USART1_RX_BUF[USART1_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART1_RX_STA=0;       //接收状态标记	

u8 uart1_RxBuf[uart1_RxBufSize];//HAL库使用的串口接收缓冲
UART_HandleTypeDef UART1_Handler; //UART句柄



//串口2中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	
u8 USART2_RX_BUF[USART2_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART2_RX_STA=0;       //接收状态标记	

u8 uart2_RxBuf[uart2_RxBufSize];//HAL库使用的串口接收缓冲
UART_HandleTypeDef UART2_Handler; //UART句柄





//初始化IO 串口1 
//bound:波特率
void uart1_init(u32 bound)
{	
	//GPIO端口设置
	GPIO_InitTypeDef GPIO_Initure;
	
	__HAL_RCC_GPIOA_CLK_ENABLE();							//使能GPIOA时钟
	__HAL_RCC_USART1_CLK_ENABLE();							//使能USART1时钟
	
	GPIO_Initure.Pin       = GPIO_PIN_9 | GPIO_PIN_10;		//PA9、PA10
	GPIO_Initure.Mode      = GPIO_MODE_AF_PP;				//复用推挽输出
	GPIO_Initure.Pull      = GPIO_PULLUP;					//上拉
	GPIO_Initure.Speed     = GPIO_SPEED_FREQ_HIGH;			//高速
	GPIO_Initure.Alternate = GPIO_AF7_USART1;				//复用为USART1
	HAL_GPIO_Init(GPIOA,&GPIO_Initure);						//初始化PA9、PA10
	
	//UART 初始化设置
	UART1_Handler.Instance        = USART1;					//USART1
	UART1_Handler.Init.BaudRate   = bound;					//波特率
	UART1_Handler.Init.WordLength = UART_WORDLENGTH_8B;		//字长为8位数据格式
	UART1_Handler.Init.StopBits   = UART_STOPBITS_1;		//一个停止位
	UART1_Handler.Init.Parity     = UART_PARITY_NONE;		//无奇偶校验位
	UART1_Handler.Init.HwFlowCtl  = UART_HWCONTROL_NONE;	//无硬件流控
	UART1_Handler.Init.Mode       = UART_MODE_TX_RX;		//收发模式
	HAL_UART_Init(&UART1_Handler);							//HAL_UART_Init()会使能UART1
	
	HAL_NVIC_EnableIRQ(USART1_IRQn);						//使能USART1中断通道
	HAL_NVIC_SetPriority(USART1_IRQn,3,3);					//抢占优先级3，子优先级3
	
	HAL_UART_Receive_IT(&UART1_Handler, (u8 *)uart1_RxBuf, uart1_RxBufSize);//该函数会开启接收中断：标志位UART_IT_RXNE，并且设置接收缓冲以及接收缓冲接收最大数据量
  
}



//初始化IO 串口2
//bound:波特率
void uart2_init(u32 bound)
{	
	//GPIO端口设置
	GPIO_InitTypeDef GPIO_Initure;

	__HAL_RCC_GPIOA_CLK_ENABLE();							//使能GPIOA时钟
	__HAL_RCC_USART2_CLK_ENABLE();							//使能USART2时钟

	GPIO_Initure.Pin       = GPIO_PIN_2 | GPIO_PIN_3;		//PA2、PA3
	GPIO_Initure.Mode      = GPIO_MODE_AF_PP;				//复用推挽输出
	GPIO_Initure.Pull      = GPIO_PULLUP;					//上拉
	GPIO_Initure.Speed     = GPIO_SPEED_FREQ_HIGH;			//高速
	GPIO_Initure.Alternate = GPIO_AF7_USART2;				//复用为USART2
	HAL_GPIO_Init(GPIOA,&GPIO_Initure);						//初始化PA2、PA3

	//UART 初始化设置
	UART2_Handler.Instance        = USART2;					//USART2
	UART2_Handler.Init.BaudRate   = bound;					//波特率
	UART2_Handler.Init.WordLength = UART_WORDLENGTH_8B;		//字长为8位数据格式
	UART2_Handler.Init.StopBits   = UART_STOPBITS_1;		//一个停止位
	UART2_Handler.Init.Parity     = UART_PARITY_NONE;		//无奇偶校验位
	UART2_Handler.Init.HwFlowCtl  = UART_HWCONTROL_NONE;	//无硬件流控
	UART2_Handler.Init.Mode       = UART_MODE_TX_RX;		//收发模式
	HAL_UART_Init(&UART2_Handler);							//HAL_UART_Init()会使能UART2

	HAL_NVIC_EnableIRQ(USART2_IRQn);						//使能USART2中断通道
	HAL_NVIC_SetPriority(USART2_IRQn,3,3);					//抢占优先级3，子优先级4
	
	HAL_UART_Receive_IT(&UART2_Handler, (u8 *)uart2_RxBuf, uart2_RxBufSize);//该函数会开启接收中断：标志位UART_IT_RXNE，并且设置接收缓冲以及接收缓冲接收最大数据量
}



//UART底层初始化，时钟使能，引脚配置，中断配置
//此函数会被HAL_UART_Init()调用
//huart:串口句柄
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
	
}



void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance==USART1)//如果是串口1
	{
		USART1_RX_BUF[USART1_RX_STA&0X3FFF]=uart1_RxBuf[0] ;
		USART1_RX_STA++;
		
		u16 len=USART1_RX_STA&0x3FFF;//得到此次接收到的数据长度
		if(len>(USART1_REC_LEN-1)) USART1_RX_STA=0;//接收数据错误,重新开始接收	 
		
		
		if(USART1_RX_STA&0x4000)//接收到了0x0d
		{
			if(uart1_RxBuf[0]==0x0a) USART1_RX_STA|=0x8000;//接收完成了 	
		}
		else //还没收到0X0D
		{	
			if(uart1_RxBuf[0]==0x0d) USART1_RX_STA|=0x4000;	 
		}
	}
	else if(huart->Instance==USART2)//如果是串口2
	{
		USART2_RX_BUF[USART2_RX_STA&0X3FFF]=uart2_RxBuf[0] ;
		USART2_RX_STA++;
		
		u16 len=USART2_RX_STA&0x3FFF;//得到此次接收到的数据长度
		if(len>(USART2_REC_LEN-1)) USART2_RX_STA=0;//接收数据错误,重新开始接收	 
		
		
		if(USART2_RX_STA&0x4000)//接收到了0x0d
		{
			if(uart2_RxBuf[0]==0x0a) USART2_RX_STA|=0x8000;//接收完成了 	
		}
		else //还没收到0X0D
		{	
			if(uart2_RxBuf[0]==0x0d) USART2_RX_STA|=0x4000;	 
		}
	}
}





//串口1中断服务程序
void USART1_IRQHandler(void)                	
{
	u32 timeout=0;
	u32 maxDelay=0x1FFFF;

	HAL_UART_IRQHandler(&UART1_Handler);	//调用HAL库中断处理公用函数
	
	timeout=0;
	while (HAL_UART_GetState(&UART1_Handler)!=HAL_UART_STATE_READY)//等待就绪
	{
		timeout++;////超时处理
		if(timeout>maxDelay) break;
	}

	timeout=0;
	while(HAL_UART_Receive_IT(&UART1_Handler,(u8 *)uart1_RxBuf, uart1_RxBufSize)!=HAL_OK)//一次处理完成之后，重新开启中断并设置RxXferCount为1
	{
		timeout++; //超时处理
		if(timeout>maxDelay) break;	
	}
}

//串口2中断服务程序
void USART2_IRQHandler(void)                	
{ 
	u32 timeout=0;
	u32 maxDelay=0x1FFFF;

	HAL_UART_IRQHandler(&UART2_Handler);	//调用HAL库中断处理公用函数
	
	timeout=0;
	while (HAL_UART_GetState(&UART2_Handler)!=HAL_UART_STATE_READY)//等待就绪
	{
		timeout++;////超时处理
		if(timeout>maxDelay) break;		
	}

	timeout=0;
	while(HAL_UART_Receive_IT(&UART2_Handler,(u8 *)uart2_RxBuf, uart2_RxBufSize)!=HAL_OK)//一次处理完成之后，重新开启中断并设置RxXferCount为1
	{
		timeout++; //超时处理
		if(timeout>maxDelay) break;	
	}
}
#endif	
