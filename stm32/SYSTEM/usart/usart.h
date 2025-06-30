#ifndef _USART_H
#define _USART_H
#include "sys.h"
#include "stdio.h"	
#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_cdc.h" 
#include "usbd_cdc_interface.h"

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32H7开发板
//串口1初始化		   
//正点原子@ALIENTEK
//技术论坛:www.openedv.csom
//修改日期:2017/6/8
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 正点原子 2009-2019
//All rights reserved
//********************************************************************************
//V1.0修改说明 
////////////////////////////////////////////////////////////////////////////////// 	
#define EN_USART_RX 			1		//使能（1）/禁止（0）串口1接收



#define USART1_REC_LEN  			1000		//定义最大接收字节数 1000
	  	
extern u8  USART1_RX_BUF[USART1_REC_LEN];		//接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART1_RX_STA;					//接收状态标记	
extern UART_HandleTypeDef UART1_Handler;	//UART句柄

#define uart1_RxBufSize   1						//缓存大小
extern u8 uart1_RxBuf[uart1_RxBufSize];					//HAL库USART接收Buffer

//如果想串口中断接收，请不要注释以下宏定义
void uart1_init(u32 bound);



#define USART2_REC_LEN  			1000	//定义最大接收字节数 1000

extern u8  USART2_RX_BUF[USART2_REC_LEN];	//接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART2_RX_STA;					//接收状态标记	
extern UART_HandleTypeDef UART2_Handler;	//UART句柄

#define uart2_RxBufSize   1					//缓存大小
extern u8 uart2_RxBuf[uart2_RxBufSize];		//HAL库使用的串口接收缓冲

void uart2_init(u32 bound);




#endif
