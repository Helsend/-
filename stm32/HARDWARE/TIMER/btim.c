

#include "led.h"
#include "btim.h"
#include "scan.h"
#include "adc.h"
#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_cdc.h" 
#include "usbd_cdc_interface.h"

extern PCD_HandleTypeDef hpcd;
extern vu8 bDeviceState;			//USB���� ���

int x[4]={1,2,3,4},i,j;
int adc_cnt=1;
float adc[256];
TIM_HandleTypeDef g_timx_handle;                                /* ��ʱ��������� */

#define ADC_DMA_BUF_SIZE        20             /* ADC DMA�ɼ� BUF��С, Ӧ����ADCͨ������������ */
extern uint16_t g_adc_dma_buf[ADC_DMA_BUF_SIZE];      /* ADC DMA BUF */
extern uint8_t g_adc_dma_sta;                  /* DMA����״̬��־, 0,δ���; 1, ����� */

//uint16_t i;
uint16_t adcx;
uint32_t sum;
uint16_t num=1,num1=1;
float temp,adctemp,pre,adc_temp1=1,adc_temp2=1;

/**
 * @brief       ������ʱ��TIMX��ʱ�жϳ�ʼ������
 * @note
 *              ������ʱ����ʱ������APB1,��PPRE1 �� 2��Ƶ��ʱ��
 *              ������ʱ����ʱ��ΪAPB1ʱ�ӵ�2��, ��APB1Ϊ100M, ���Զ�ʱ��ʱ�� = 200Mhz
 *              ��ʱ�����ʱ����㷽��: Tout = ((arr + 1) * (psc + 1)) / Ft us.
 *              Ft=��ʱ������Ƶ��,��λ:Mhz
 *
 * @param       arr : �Զ���װֵ��
 * @param       psc : ʱ��Ԥ��Ƶ��
 * @retval      ��
 */
void btim_timx_int_init(uint16_t arr, uint16_t psc)
{
    g_timx_handle.Instance = BTIM_TIMX_INT;                      /* ��ʱ��x */
    g_timx_handle.Init.Prescaler = psc;                          /* ��Ƶϵ�� */
    g_timx_handle.Init.CounterMode = TIM_COUNTERMODE_UP;         /* ��������ģʽ */
    g_timx_handle.Init.Period = arr;                             /* �Զ�װ��ֵ */
    HAL_TIM_Base_Init(&g_timx_handle);
    
    HAL_TIM_Base_Start_IT(&g_timx_handle);                       /* ʹ�ܶ�ʱ��x�Ͷ�ʱ�������ж� */
}

/**
 * @brief       ��ʱ���ײ�����������ʱ�ӣ������ж����ȼ�
                �˺����ᱻHAL_TIM_Base_Init()��������
 * @param       htim  : ��ʱ�����
 * @retval      ��
 */
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == BTIM_TIMX_INT)
    {
        BTIM_TIMX_INT_CLK_ENABLE();                             /* ʹ��TIMxʱ�� */
        HAL_NVIC_SetPriority(BTIM_TIMX_INT_IRQn, 1, 3);         /* ��ռ1�������ȼ�3 */
        HAL_NVIC_EnableIRQ(BTIM_TIMX_INT_IRQn);                 /* ����ITMx�ж� */
    }
}

/**
 * @brief       ������ʱ��TIMX�жϷ�����
 * @param       ��
 * @retval      ��
 */
void BTIM_TIMX_INT_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&g_timx_handle);                         /* ��ʱ���ص����� */
}

/**
 * @brief       �ص���������ʱ���жϷ���������
 * @param       htim  : ��ʱ�����
 * @retval      ��
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == BTIM_TIMX_INT)
    {
			LED2_Toggle;
			HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_6);
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_8);
				
				if (g_adc_dma_sta == 1)
        {
            /* ��D Cache */
            SCB_InvalidateDCache();

            /* ����DMA �ɼ�����ADC���ݵ�ƽ��ֵ */
            sum = 0;

            for (i = 0; i < ADC_DMA_BUF_SIZE; i++)              /* �ۼ� */
            {
                sum += g_adc_dma_buf[i];
            }

            adcx = sum / ADC_DMA_BUF_SIZE;                      /* ȡƽ��ֵ */

            /* ��ʾ��� */

            temp = (float)adcx * (3.3 / 65536);                 /* ��ȡ�����Ĵ�С����ʵ�ʵ�ѹֵ������3.1111 */

						
						if(adc_cnt == 1)
						{
							adc_temp1 = temp;
						}
						if(adc_cnt == 0)
						{
							adc_temp2 = temp;
							adctemp = adc_temp1/adc_temp2;
							pre = (1/adctemp)*16.286 ;
							adc[num]=pre;
						  usb_printf("%f ", pre*50);
						}
				
						
//						adctemp = adc_temp1/adc_temp2;
//						adc[num]=adctemp;
//						usb_printf("%f\r\n", adctemp);
			
//            adcx = temp;                                        /* ��ֵ�������ָ�adcx��������ΪadcxΪu16���� */

//            temp -= adcx;                                       /* ���Ѿ���ʾ����������ȥ��������С�����֣�����3.1111-3=0.1111 */
//            temp *= 1000;                                       /* С�����ֳ���1000�����磺0.1111��ת��Ϊ111.1���൱�ڱ�����λС���� */

//            usb_printf("\r\n");
						g_adc_dma_sta = 0;                                  /* ���DMA�ɼ����״̬��־ */
            adc_dma_enable(ADC_DMA_BUF_SIZE);                   /* ������һ��ADC DMA�ɼ� */
        }
			  
				switch(num){
					case 1:REFIN2(0);LIE2_1(1);break;case 2:REFIN2(1);LIE2_1(0);break;
					case 3:REFIN2(0);LIE2_2(1);break;case 4:REFIN2(1);LIE2_2(0);break;
					case 5:REFIN2(0);LIE2_3(1);break;case 6:REFIN2(1);LIE2_3(0);break;
					case 7:REFIN2(0);LIE2_4(1);break;case 8:REFIN2(1);LIE2_4(0);break;
					case 9:REFIN2(0);LIE2_5(1);break;case 10:REFIN2(1);LIE2_5(0);break;
					case 11:REFIN2(0);LIE2_6(1);break;case 12:REFIN2(1);LIE2_6(0);break;
					case 13:REFIN2(0);LIE2_7(1);break;case 14:REFIN2(1);LIE2_7(0);break;
					case 15:REFIN2(0);LIE2_8(1);break;case 16:REFIN2(1);LIE2_8(0);break;
					case 17:REFIN2(0);LIE2_9(1);break;case 18:REFIN2(1);LIE2_9(0);break;
					case 19:REFIN2(0);LIE2_10(1);break;case 20:REFIN2(1);LIE2_10(0);break;
					case 21:REFIN2(0);LIE2_11(1);break;case 22:REFIN2(1);LIE2_11(0);break;
					case 23:REFIN2(0);LIE2_12(1);break;case 24:REFIN2(1);LIE2_12(0);break;
					case 25:REFIN2(0);LIE2_13(1);break;case 26:REFIN2(1);LIE2_13(0);break;
					case 27:REFIN2(0);LIE2_14(1);break;case 28:REFIN2(1);LIE2_14(0);break;
					case 29:REFIN2(0);LIE2_15(1);break;case 30:REFIN2(1);LIE2_15(0);break;
					case 31:REFIN2(0);LIE2_16(1);break;
					case 0:
					switch(num1){
						case 1:scan2();break;case 2:scan3();break;case 3:scan4();break;case 4:scan5();break;
						case 5:scan6();break;case 6:scan7();break;case 7:scan8();break;case 8:scan9();break;
						case 9:scan10();break;case 10:scan11();break;case 11:scan12();break;case 12:scan13();break;
						case 13:scan14();break;case 14:scan15();break;case 15:scan16();break;case 0:usb_printf("a");scan1();break;
					}	
					REFIN2(1);LIE2_16(0);num1++;num1=num1%16;break;
		 
				}
				num++;
				num=num%32;
				
				adc_cnt++;
				adc_cnt=adc_cnt%2;

    }
}


//          δ��ɵ��Ż���(
//					case 33:REFIN2(0);LIE2_1(1);break;case 34:REFIN2(1);LIE2_1(0);break;
//					case 35:REFIN2(0);LIE2_2(1);break;case 36:REFIN2(1);LIE2_2(0);break;
//					case 37:REFIN2(0);LIE2_3(1);break;case 38:REFIN2(1);LIE2_3(0);break;
//					case 39:REFIN2(0);LIE2_4(1);break;case 40:REFIN2(1);LIE2_4(0);break;
//					case 41:REFIN2(0);LIE2_5(1);break;case 42:REFIN2(1);LIE2_5(0);break;
//					case 43:REFIN2(0);LIE2_6(1);break;case 44:REFIN2(1);LIE2_6(0);break;
//					case 45:REFIN2(0);LIE2_7(1);break;case 46:REFIN2(1);LIE2_7(0);break;
//					case 47:REFIN2(0);LIE2_8(1);break;case 48:REFIN2(1);LIE2_8(0);break;
//					case 49:REFIN2(0);LIE2_9(1);break;case 50:REFIN2(1);LIE2_9(0);break;
//					case 51:REFIN2(0);LIE2_10(1);break;case 52:REFIN2(1);LIE2_10(0);break;
//					case 53:REFIN2(0);LIE2_11(1);break;case 54:REFIN2(1);LIE2_11(0);break;
//					case 55:REFIN2(0);LIE2_12(1);break;case 56:REFIN2(1);LIE2_12(0);break;
//					case 57:REFIN2(0);LIE2_13(1);break;case 58:REFIN2(1);LIE2_13(0);break;
//					case 59:REFIN2(0);LIE2_14(1);break;case 60:REFIN2(1);LIE2_14(0);break;
//					case 61:REFIN2(0);LIE2_15(1);break;case 62:REFIN2(1);LIE2_15(0);break;
//					case 63:REFIN2(0);LIE2_16(1);break;
//					case 0:REFIN2(1);LIE2_16(0);HANG1_1(0);HANG1_2(0);HANG1_3(0);HANG1_4(0);break;
//					HANG1_2(0);HANG1_3(1);HANG1_4(0);REFIN2(1);break;
//					case 33:REFIN2(0);LIE2_1(1);break;case 34:REFIN2(1);LIE2_1(0);break;
//	
//						sum = 0;
//						
//						for( i=0;i<15;i++){
//							
//							switch(i){
//							case 1:scan2();break;case 2:scan3();break;case 3:scan4();break;case 4:scan5();break;
//							case 5:scan6();break;case 6:scan7();break;case 7:scan8();break;case 8:scan9();break;
//							case 9:scan10();break;case 10:scan11();break;case 11:scan12();break;case 12:scan13();break;
//							case 13:scan14();break;case 14:scan15();break;case 15:scan16();break;case 0:scan1();break;
//							}
//							
//							for( j=0;j<15;j++){
//								
//								/* ����DMA �ɼ�����ADC���ݵ�ƽ��ֵ */
//								

//								for (i = 0; i < ADC_DMA_BUF_SIZE; i++)              /* �ۼ� */
//								{
//									sum += g_adc_dma_buf[i];
//								}

//								adcx = sum / ADC_DMA_BUF_SIZE;                      /* ȡƽ��ֵ */

//								/* ��ʾ��� */

//								temp = (float)adcx * (3.3 / 65536);                 /* ��ȡ�����Ĵ�С����ʵ�ʵ�ѹֵ������3.1111 */
//								
//								adc_temp1 = temp;
////								usb_printf("%f\r\n", temp);
//								
////								g_adc_dma_sta = 0;                                  /* ���DMA�ɼ����״̬��־ */
////								adc_dma_enable(ADC_DMA_BUF_SIZE);
//								
//								switch(j){
//									case 0:REFIN2(0);LIE2_1(1);break;case 1:REFIN2(0);LIE2_2(1);break;
//									case 2:REFIN2(0);LIE2_3(1);break;case 3:REFIN2(0);LIE2_4(1);break;
//									case 4:REFIN2(0);LIE2_5(1);break;case 5:REFIN2(0);LIE2_6(1);break;
//									case 6:REFIN2(0);LIE2_7(1);break;case 7:REFIN2(0);LIE2_8(1);break;
//									case 8:REFIN2(0);LIE2_9(1);break;case 9:REFIN2(0);LIE2_10(1);break;
//									case 10:REFIN2(0);LIE2_11(1);break;case 11:REFIN2(0);LIE2_12(1);break;
//									case 12:REFIN2(0);LIE2_13(1);break;case 13:REFIN2(0);LIE2_14(1);break;
//									case 14:REFIN2(0);LIE2_15(1);break;case 15:REFIN2(0);LIE2_16(1);break;
//								
//								}
//								
//								if (g_adc_dma_sta == 1){
//									for (i = 0; i < ADC_DMA_BUF_SIZE; i++)              /* �ۼ� */
//									{
//										sum += g_adc_dma_buf[i];
//									}

//									adcx = sum / ADC_DMA_BUF_SIZE;                      /* ȡƽ��ֵ */

//									/* ��ʾ��� */

//									temp = (float)adcx * (3.3 / 65536);                 /* ��ȡ�����Ĵ�С����ʵ�ʵ�ѹֵ������3.1111 */
//									
//									adc_temp2 = temp;
//									adctemp = adc_temp1/adc_temp2;
//									usb_printf("%f\r\n", adctemp);
//	//								pre = (1/adctemp)*16.286 ;
//	//								adc[num]=pre;
//	//								usb_printf("%f ", pre);
//									switch(j){
//										case 0:REFIN2(1);LIE2_1(0);break;case 1:REFIN2(1);LIE2_2(0);break;
//										case 2:REFIN2(1);LIE2_3(0);break;case 3:REFIN2(1);LIE2_4(0);break;
//										case 4:REFIN2(1);LIE2_5(0);break;case 5:REFIN2(1);LIE2_6(0);break;
//										case 6:REFIN2(1);LIE2_7(0);break;case 7:REFIN2(1);LIE2_8(0);break;
//										case 8:REFIN2(1);LIE2_9(0);break;case 9:REFIN2(1);LIE2_10(0);break;
//										case 10:REFIN2(1);LIE2_11(0);break;case 11:REFIN2(1);LIE2_12(0);break;
//										case 12:REFIN2(1);LIE2_13(0);break;case 13:REFIN2(1);LIE2_14(0);break;
//										case 14:REFIN2(1);LIE2_15(0);break;case 15:REFIN2(1);LIE2_16(0);break;
//									
//									}
//									g_adc_dma_sta = 0;                                  /* ���DMA�ɼ����״̬��־ */
//									adc_dma_enable(ADC_DMA_BUF_SIZE);
//								}
//								
//							}
//						}

