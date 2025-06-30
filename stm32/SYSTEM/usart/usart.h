#ifndef _USART_H
#define _USART_H
#include "sys.h"
#include "stdio.h"	
#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_cdc.h" 
#include "usbd_cdc_interface.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32H7������
//����1��ʼ��		   
//����ԭ��@ALIENTEK
//������̳:www.openedv.csom
//�޸�����:2017/6/8
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
//All rights reserved
//********************************************************************************
//V1.0�޸�˵�� 
////////////////////////////////////////////////////////////////////////////////// 	
#define EN_USART_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����



#define USART1_REC_LEN  			1000		//�����������ֽ��� 1000
	  	
extern u8  USART1_RX_BUF[USART1_REC_LEN];		//���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART1_RX_STA;					//����״̬���	
extern UART_HandleTypeDef UART1_Handler;	//UART���

#define uart1_RxBufSize   1						//�����С
extern u8 uart1_RxBuf[uart1_RxBufSize];					//HAL��USART����Buffer

//����봮���жϽ��գ��벻Ҫע�����º궨��
void uart1_init(u32 bound);



#define USART2_REC_LEN  			1000	//�����������ֽ��� 1000

extern u8  USART2_RX_BUF[USART2_REC_LEN];	//���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART2_RX_STA;					//����״̬���	
extern UART_HandleTypeDef UART2_Handler;	//UART���

#define uart2_RxBufSize   1					//�����С
extern u8 uart2_RxBuf[uart2_RxBufSize];		//HAL��ʹ�õĴ��ڽ��ջ���

void uart2_init(u32 bound);




#endif
