#include "usart.h"
////////////////////////////////////////////////////////////////////////////////// 	 
//���ʹ��os,����������ͷ�ļ�����.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//os ʹ��	  
#endif
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32H7������
//����1��ʼ��		   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2017/6/8
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved
//********************************************************************************
//V1.0�޸�˵�� 
////////////////////////////////////////////////////////////////////////////////// 	  
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
//#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)	
#if 1
//#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{ 	
	while((USART1->ISR&0X40)==0);//ѭ������,ֱ���������   
	USART1->TDR=(u8)ch;      
	return ch;
}
#endif 





#if EN_USART_RX   //���ʹ���˽���

//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
u8 USART1_RX_BUF[USART1_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART1_RX_STA=0;       //����״̬���	

u8 uart1_RxBuf[uart1_RxBufSize];//HAL��ʹ�õĴ��ڽ��ջ���
UART_HandleTypeDef UART1_Handler; //UART���



//����2�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
u8 USART2_RX_BUF[USART2_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART2_RX_STA=0;       //����״̬���	

u8 uart2_RxBuf[uart2_RxBufSize];//HAL��ʹ�õĴ��ڽ��ջ���
UART_HandleTypeDef UART2_Handler; //UART���





//��ʼ��IO ����1 
//bound:������
void uart1_init(u32 bound)
{	
	//GPIO�˿�����
	GPIO_InitTypeDef GPIO_Initure;
	
	__HAL_RCC_GPIOA_CLK_ENABLE();							//ʹ��GPIOAʱ��
	__HAL_RCC_USART1_CLK_ENABLE();							//ʹ��USART1ʱ��
	
	GPIO_Initure.Pin       = GPIO_PIN_9 | GPIO_PIN_10;		//PA9��PA10
	GPIO_Initure.Mode      = GPIO_MODE_AF_PP;				//�����������
	GPIO_Initure.Pull      = GPIO_PULLUP;					//����
	GPIO_Initure.Speed     = GPIO_SPEED_FREQ_HIGH;			//����
	GPIO_Initure.Alternate = GPIO_AF7_USART1;				//����ΪUSART1
	HAL_GPIO_Init(GPIOA,&GPIO_Initure);						//��ʼ��PA9��PA10
	
	//UART ��ʼ������
	UART1_Handler.Instance        = USART1;					//USART1
	UART1_Handler.Init.BaudRate   = bound;					//������
	UART1_Handler.Init.WordLength = UART_WORDLENGTH_8B;		//�ֳ�Ϊ8λ���ݸ�ʽ
	UART1_Handler.Init.StopBits   = UART_STOPBITS_1;		//һ��ֹͣλ
	UART1_Handler.Init.Parity     = UART_PARITY_NONE;		//����żУ��λ
	UART1_Handler.Init.HwFlowCtl  = UART_HWCONTROL_NONE;	//��Ӳ������
	UART1_Handler.Init.Mode       = UART_MODE_TX_RX;		//�շ�ģʽ
	HAL_UART_Init(&UART1_Handler);							//HAL_UART_Init()��ʹ��UART1
	
	HAL_NVIC_EnableIRQ(USART1_IRQn);						//ʹ��USART1�ж�ͨ��
	HAL_NVIC_SetPriority(USART1_IRQn,3,3);					//��ռ���ȼ�3�������ȼ�3
	
	HAL_UART_Receive_IT(&UART1_Handler, (u8 *)uart1_RxBuf, uart1_RxBufSize);//�ú����Ὺ�������жϣ���־λUART_IT_RXNE���������ý��ջ����Լ����ջ���������������
  
}



//��ʼ��IO ����2
//bound:������
void uart2_init(u32 bound)
{	
	//GPIO�˿�����
	GPIO_InitTypeDef GPIO_Initure;

	__HAL_RCC_GPIOA_CLK_ENABLE();							//ʹ��GPIOAʱ��
	__HAL_RCC_USART2_CLK_ENABLE();							//ʹ��USART2ʱ��

	GPIO_Initure.Pin       = GPIO_PIN_2 | GPIO_PIN_3;		//PA2��PA3
	GPIO_Initure.Mode      = GPIO_MODE_AF_PP;				//�����������
	GPIO_Initure.Pull      = GPIO_PULLUP;					//����
	GPIO_Initure.Speed     = GPIO_SPEED_FREQ_HIGH;			//����
	GPIO_Initure.Alternate = GPIO_AF7_USART2;				//����ΪUSART2
	HAL_GPIO_Init(GPIOA,&GPIO_Initure);						//��ʼ��PA2��PA3

	//UART ��ʼ������
	UART2_Handler.Instance        = USART2;					//USART2
	UART2_Handler.Init.BaudRate   = bound;					//������
	UART2_Handler.Init.WordLength = UART_WORDLENGTH_8B;		//�ֳ�Ϊ8λ���ݸ�ʽ
	UART2_Handler.Init.StopBits   = UART_STOPBITS_1;		//һ��ֹͣλ
	UART2_Handler.Init.Parity     = UART_PARITY_NONE;		//����żУ��λ
	UART2_Handler.Init.HwFlowCtl  = UART_HWCONTROL_NONE;	//��Ӳ������
	UART2_Handler.Init.Mode       = UART_MODE_TX_RX;		//�շ�ģʽ
	HAL_UART_Init(&UART2_Handler);							//HAL_UART_Init()��ʹ��UART2

	HAL_NVIC_EnableIRQ(USART2_IRQn);						//ʹ��USART2�ж�ͨ��
	HAL_NVIC_SetPriority(USART2_IRQn,3,3);					//��ռ���ȼ�3�������ȼ�4
	
	HAL_UART_Receive_IT(&UART2_Handler, (u8 *)uart2_RxBuf, uart2_RxBufSize);//�ú����Ὺ�������жϣ���־λUART_IT_RXNE���������ý��ջ����Լ����ջ���������������
}



//UART�ײ��ʼ����ʱ��ʹ�ܣ��������ã��ж�����
//�˺����ᱻHAL_UART_Init()����
//huart:���ھ��
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
	
}



void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance==USART1)//����Ǵ���1
	{
		USART1_RX_BUF[USART1_RX_STA&0X3FFF]=uart1_RxBuf[0] ;
		USART1_RX_STA++;
		
		u16 len=USART1_RX_STA&0x3FFF;//�õ��˴ν��յ������ݳ���
		if(len>(USART1_REC_LEN-1)) USART1_RX_STA=0;//�������ݴ���,���¿�ʼ����	 
		
		
		if(USART1_RX_STA&0x4000)//���յ���0x0d
		{
			if(uart1_RxBuf[0]==0x0a) USART1_RX_STA|=0x8000;//��������� 	
		}
		else //��û�յ�0X0D
		{	
			if(uart1_RxBuf[0]==0x0d) USART1_RX_STA|=0x4000;	 
		}
	}
	else if(huart->Instance==USART2)//����Ǵ���2
	{
		USART2_RX_BUF[USART2_RX_STA&0X3FFF]=uart2_RxBuf[0] ;
		USART2_RX_STA++;
		
		u16 len=USART2_RX_STA&0x3FFF;//�õ��˴ν��յ������ݳ���
		if(len>(USART2_REC_LEN-1)) USART2_RX_STA=0;//�������ݴ���,���¿�ʼ����	 
		
		
		if(USART2_RX_STA&0x4000)//���յ���0x0d
		{
			if(uart2_RxBuf[0]==0x0a) USART2_RX_STA|=0x8000;//��������� 	
		}
		else //��û�յ�0X0D
		{	
			if(uart2_RxBuf[0]==0x0d) USART2_RX_STA|=0x4000;	 
		}
	}
}





//����1�жϷ������
void USART1_IRQHandler(void)                	
{
	u32 timeout=0;
	u32 maxDelay=0x1FFFF;

	HAL_UART_IRQHandler(&UART1_Handler);	//����HAL���жϴ����ú���
	
	timeout=0;
	while (HAL_UART_GetState(&UART1_Handler)!=HAL_UART_STATE_READY)//�ȴ�����
	{
		timeout++;////��ʱ����
		if(timeout>maxDelay) break;
	}

	timeout=0;
	while(HAL_UART_Receive_IT(&UART1_Handler,(u8 *)uart1_RxBuf, uart1_RxBufSize)!=HAL_OK)//һ�δ������֮�����¿����жϲ�����RxXferCountΪ1
	{
		timeout++; //��ʱ����
		if(timeout>maxDelay) break;	
	}
}

//����2�жϷ������
void USART2_IRQHandler(void)                	
{ 
	u32 timeout=0;
	u32 maxDelay=0x1FFFF;

	HAL_UART_IRQHandler(&UART2_Handler);	//����HAL���жϴ����ú���
	
	timeout=0;
	while (HAL_UART_GetState(&UART2_Handler)!=HAL_UART_STATE_READY)//�ȴ�����
	{
		timeout++;////��ʱ����
		if(timeout>maxDelay) break;		
	}

	timeout=0;
	while(HAL_UART_Receive_IT(&UART2_Handler,(u8 *)uart2_RxBuf, uart2_RxBufSize)!=HAL_OK)//һ�δ������֮�����¿����жϲ�����RxXferCountΪ1
	{
		timeout++; //��ʱ����
		if(timeout>maxDelay) break;	
	}
}
#endif	
