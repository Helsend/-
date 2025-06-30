#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "led.h"
#include "mpu.h" 
#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_cdc.h" 
#include "usbd_cdc_interface.h"
#include "IIC2_CW2015.h"
#include "adc.h"
#include "scan.h"
#include "btim.h"


USBD_HandleTypeDef USBD_Device;
extern PCD_HandleTypeDef hpcd;
extern vu8 bDeviceState;			//USB连接 情况
uint8_t BT_COMMAND[]={'A','T','+','N','A','M','E','?',0x0d,0x0a};

#define ADC_DMA_BUF_SIZE        5             /* ADC DMA采集 BUF大小, 应等于ADC通道数的整数倍 */
uint16_t g_adc_dma_buf[ADC_DMA_BUF_SIZE];      /* ADC DMA BUF */
extern uint8_t g_adc_dma_sta;                  /* DMA传输状态标志, 0,未完成; 1, 已完成 */





int main(void)
{
	u16 times=0;    
	u8 usbstatus=0;	
	uint16_t i;
  uint16_t adcx;
  uint32_t sum;
	float temp;

	Cache_Enable();               //打开L1-Cache
	MPU_Memory_Protection();      //保护相关存储区域
	HAL_Init();				        		//初始化HAL库
	
	Stm32_Clock_Init(160,5,2,2);	//设置时钟,400Mhz 
	delay_init(480);							//延时初始化
	uart1_init(115200);						//串口初始化
	uart2_init(115200);						//串口初始化
	LED_Init();										//初始化LED
	
	adc_dma_init((uint32_t)&ADC1->DR, (uint32_t)&g_adc_dma_buf);    /* 初始化ADC */
	
	adc_dma_enable(50);       /* 启动ADC DMA采集 */
	
	btim_timx_int_init(1000 - 1, 500 - 1);    /* 5ms 详情计数规则见定时器部分 */
	
	scan_init();
	
	USBD_Init                 (&USBD_Device,&VCP_Desc,0);//虚拟串口部分，用以与上位机直接测试
	USBD_RegisterClass        (&USBD_Device,USBD_CDC_CLASS);
	USBD_CDC_RegisterInterface(&USBD_Device,&USBD_CDC_fops);
	USBD_Start                (&USBD_Device);
	HAL_PWREx_EnableUSBVoltageDetector();
    
 	while(1)
	{
		
//		该部分转移至定时器中（btim.c）		
//		if (g_adc_dma_sta == 1
//        {
//            /* 清D Cache */
//            SCB_InvalidateDCache();

//            /* 计算DMA 采集到的ADC数据的平均值 */
//            sum = 0;

//            for (i = 0; i < ADC_DMA_BUF_SIZE; i++)              /* 累加 */
//            {
//                sum += g_adc_dma_buf[i];
//            }

//            adcx = sum / ADC_DMA_BUF_SIZE;                      /* 取平均值 */

//            /* 显示结果 */

//            temp = (float)adcx * (3.3 / 65536);                 /* 获取计算后的带小数的实际电压值，比如3.1111 */
//					usb_printf("%f\r\n", temp);
//			
//            adcx = temp;                                        /* 赋值整数部分给adcx变量，因为adcx为u16整形 */

//            temp -= adcx;                                       /* 把已经显示的整数部分去掉，留下小数部分，比如3.1111-3=0.1111 */
//            temp *= 1000;                                       /* 小数部分乘以1000，例如：0.1111就转换为111.1，相当于保留三位小数。 */

//            g_adc_dma_sta = 0;                                  /* 清除DMA采集完成状态标志 */
//            adc_dma_enable(ADC_DMA_BUF_SIZE);                   /* 启动下一次ADC DMA采集 */
//        }
				
				
				
		if(usbstatus!=bDeviceState)//USB连接状态发生了改变.
		{
			usbstatus=bDeviceState;//记录新的状态
			if(usbstatus==1) LED1(0);//DS1亮	
			else             LED1(1);//DS1灭	
		}
		if(USB_USART_RX_STA&0x8000)
		{					   
			u16 len=USB_USART_RX_STA&0x3FFF;//得到此次接收到的数据长度	
			USB_USART_RX_STA=0;		
			
			//STM32通过UART2向WIFI模块发送AT指令,AT指令必须以/r/n结尾
			USB_USART_RX_BUF[len  ] = 0x0D;//添加'/r'
			USB_USART_RX_BUF[len+1] = 0x0A;//添加'/n'
			HAL_UART_Transmit(&UART2_Handler,(uint8_t*)USB_USART_RX_BUF,len+2,1000);			//发送接收到的数据
			//while(__HAL_UART_GET_FLAG(&UART2_Handler, UART_FLAG_TC) != SET);					//等待发送结束
			HAL_UART_Transmit(&UART1_Handler, (uint8_t *)BT_COMMAND, sizeof(BT_COMMAND), 1000);	//发送固定测试数据
      //while(__HAL_UART_GET_FLAG(&UART1_Handler, UART_FLAG_TC) != SET);					//等待发送结束
		}
		else
		{
			times++;
		  //if(times%30 ==0)LED0_Toggle;//闪烁LED,提示系统正在运行.
//			if(times%50 ==0)LED2_Toggle;//闪烁LED,提示系统正在运行.
			//if(times%500==0)usb_printf("请输入AT指令(如AT+GMR),以回车换行键结束\r\n");
			
			//if(times%200==0) IIC2_CW2015_Init();                 //初始化IIC2的IO口	
			delay_ms(10);    
		}
		
		
		
		//将WIFI模块向STM32发送的信息打印出来
		if(USART2_RX_STA & 0x8000)
		{	
			u16 len_WIFI = USART2_RX_STA & 0x3FFF;//得到此次接收到的数据长度
			USART2_RX_STA = 0;
			
			//usb_printf("来自WIFI模块的数据:\n");
			VCP_DataTx(USART2_RX_BUF,len_WIFI);
			//usb_printf("\n");
		}
		//将蓝牙模块向STM32发送的信息打印出来
		if (USART1_RX_STA & 0x8000)
        {
			u16 len_BT = USART1_RX_STA & 0x3FFF;//得到此次接收到的数据长度
			USART1_RX_STA = 0;
			
            //usb_printf("来自蓝牙模块的数据:\n");
            VCP_DataTx(USART1_RX_BUF,len_BT);
            //usb_printf("\n");
        }
	}   	
}



