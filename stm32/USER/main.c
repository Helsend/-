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
extern vu8 bDeviceState;			//USB���� ���
uint8_t BT_COMMAND[]={'A','T','+','N','A','M','E','?',0x0d,0x0a};

#define ADC_DMA_BUF_SIZE        5             /* ADC DMA�ɼ� BUF��С, Ӧ����ADCͨ������������ */
uint16_t g_adc_dma_buf[ADC_DMA_BUF_SIZE];      /* ADC DMA BUF */
extern uint8_t g_adc_dma_sta;                  /* DMA����״̬��־, 0,δ���; 1, ����� */





int main(void)
{
	u16 times=0;    
	u8 usbstatus=0;	
	uint16_t i;
  uint16_t adcx;
  uint32_t sum;
	float temp;

	Cache_Enable();               //��L1-Cache
	MPU_Memory_Protection();      //������ش洢����
	HAL_Init();				        		//��ʼ��HAL��
	
	Stm32_Clock_Init(160,5,2,2);	//����ʱ��,400Mhz 
	delay_init(480);							//��ʱ��ʼ��
	uart1_init(115200);						//���ڳ�ʼ��
	uart2_init(115200);						//���ڳ�ʼ��
	LED_Init();										//��ʼ��LED
	
	adc_dma_init((uint32_t)&ADC1->DR, (uint32_t)&g_adc_dma_buf);    /* ��ʼ��ADC */
	
	adc_dma_enable(50);       /* ����ADC DMA�ɼ� */
	
	btim_timx_int_init(1000 - 1, 500 - 1);    /* 5ms ��������������ʱ������ */
	
	scan_init();
	
	USBD_Init                 (&USBD_Device,&VCP_Desc,0);//���⴮�ڲ��֣���������λ��ֱ�Ӳ���
	USBD_RegisterClass        (&USBD_Device,USBD_CDC_CLASS);
	USBD_CDC_RegisterInterface(&USBD_Device,&USBD_CDC_fops);
	USBD_Start                (&USBD_Device);
	HAL_PWREx_EnableUSBVoltageDetector();
    
 	while(1)
	{
		
//		�ò���ת������ʱ���У�btim.c��		
//		if (g_adc_dma_sta == 1
//        {
//            /* ��D Cache */
//            SCB_InvalidateDCache();

//            /* ����DMA �ɼ�����ADC���ݵ�ƽ��ֵ */
//            sum = 0;

//            for (i = 0; i < ADC_DMA_BUF_SIZE; i++)              /* �ۼ� */
//            {
//                sum += g_adc_dma_buf[i];
//            }

//            adcx = sum / ADC_DMA_BUF_SIZE;                      /* ȡƽ��ֵ */

//            /* ��ʾ��� */

//            temp = (float)adcx * (3.3 / 65536);                 /* ��ȡ�����Ĵ�С����ʵ�ʵ�ѹֵ������3.1111 */
//					usb_printf("%f\r\n", temp);
//			
//            adcx = temp;                                        /* ��ֵ�������ָ�adcx��������ΪadcxΪu16���� */

//            temp -= adcx;                                       /* ���Ѿ���ʾ����������ȥ��������С�����֣�����3.1111-3=0.1111 */
//            temp *= 1000;                                       /* С�����ֳ���1000�����磺0.1111��ת��Ϊ111.1���൱�ڱ�����λС���� */

//            g_adc_dma_sta = 0;                                  /* ���DMA�ɼ����״̬��־ */
//            adc_dma_enable(ADC_DMA_BUF_SIZE);                   /* ������һ��ADC DMA�ɼ� */
//        }
				
				
				
		if(usbstatus!=bDeviceState)//USB����״̬�����˸ı�.
		{
			usbstatus=bDeviceState;//��¼�µ�״̬
			if(usbstatus==1) LED1(0);//DS1��	
			else             LED1(1);//DS1��	
		}
		if(USB_USART_RX_STA&0x8000)
		{					   
			u16 len=USB_USART_RX_STA&0x3FFF;//�õ��˴ν��յ������ݳ���	
			USB_USART_RX_STA=0;		
			
			//STM32ͨ��UART2��WIFIģ�鷢��ATָ��,ATָ�������/r/n��β
			USB_USART_RX_BUF[len  ] = 0x0D;//���'/r'
			USB_USART_RX_BUF[len+1] = 0x0A;//���'/n'
			HAL_UART_Transmit(&UART2_Handler,(uint8_t*)USB_USART_RX_BUF,len+2,1000);			//���ͽ��յ�������
			//while(__HAL_UART_GET_FLAG(&UART2_Handler, UART_FLAG_TC) != SET);					//�ȴ����ͽ���
			HAL_UART_Transmit(&UART1_Handler, (uint8_t *)BT_COMMAND, sizeof(BT_COMMAND), 1000);	//���͹̶���������
      //while(__HAL_UART_GET_FLAG(&UART1_Handler, UART_FLAG_TC) != SET);					//�ȴ����ͽ���
		}
		else
		{
			times++;
		  //if(times%30 ==0)LED0_Toggle;//��˸LED,��ʾϵͳ��������.
//			if(times%50 ==0)LED2_Toggle;//��˸LED,��ʾϵͳ��������.
			//if(times%500==0)usb_printf("������ATָ��(��AT+GMR),�Իس����м�����\r\n");
			
			//if(times%200==0) IIC2_CW2015_Init();                 //��ʼ��IIC2��IO��	
			delay_ms(10);    
		}
		
		
		
		//��WIFIģ����STM32���͵���Ϣ��ӡ����
		if(USART2_RX_STA & 0x8000)
		{	
			u16 len_WIFI = USART2_RX_STA & 0x3FFF;//�õ��˴ν��յ������ݳ���
			USART2_RX_STA = 0;
			
			//usb_printf("����WIFIģ�������:\n");
			VCP_DataTx(USART2_RX_BUF,len_WIFI);
			//usb_printf("\n");
		}
		//������ģ����STM32���͵���Ϣ��ӡ����
		if (USART1_RX_STA & 0x8000)
        {
			u16 len_BT = USART1_RX_STA & 0x3FFF;//�õ��˴ν��յ������ݳ���
			USART1_RX_STA = 0;
			
            //usb_printf("��������ģ�������:\n");
            VCP_DataTx(USART1_RX_BUF,len_BT);
            //usb_printf("\n");
        }
	}   	
}



