#include "IIC2_CW2015.h"
#include "delay.h"
#include "usbd_cdc_interface.h"


#define	READ_CW2015				      0xC5
#define	WRITE_CW2015			      0xC4

#define REG_VERSION             0x00
#define REG_VCELL               0x02
#define REG_SOC                 0x04
#define REG_RRT_ALERT           0x06
#define REG_CONFIG              0x08
#define REG_MODE                0x0A
#define REG_BATINFO             0x10

#define MODE_SLEEP_MASK         (0x3<<6)
#define MODE_SLEEP              (0x3<<6)
#define MODE_NORMAL             (0x0<<6)
#define MODE_QUICK_START        (0x3<<4)
#define MODE_RESTART            (0xf<<0)

#define CONFIG_UPDATE_FLG       (0x1<<1)

#define ATHD                    (0x0<<3)        //ATHD = 0%

#define SIZE_BATINFO                    64

#define BATTERY_UP_MAX_CHANGE           720                  //the max time allow battery change quantity default 720
#define BATTERY_DOWN_MIN_CHANGE         60                   //the min time allow battery change quantity when run
#define BATTERY_DOWN_MIN_CHANGE_SLEEP   1800                 //the min time allow battery change quantity when run 30min

/*��ؽ�ģ��Ϣ���ͻ��õ��Լ����ƥ��Ľ�ģ��Ϣ�����滻*/
static unsigned char cw_bat_config_info[SIZE_BATINFO] = {
0x15  ,0x4C  ,0x5D  ,0x5D  ,0x5A  ,0x59  ,0x55  ,
0x51  ,0x4E  ,0x48  ,0x46  ,0x41  ,0x3C  ,0x39  ,
0x33  ,0x2D  ,0x25  ,0x1E  ,0x19  ,0x19  ,0x1A  ,
0x2C  ,0x44  ,0x4A  ,0x43  ,0x40  ,0x0C  ,0xCD  ,
0x22  ,0x43  ,0x56  ,0x82  ,0x78  ,0x6F  ,0x62  ,
0x60  ,0x42  ,0x19  ,0x37  ,0x31  ,0x00  ,0x1D  ,
0x59  ,0x85  ,0x8F  ,0x91  ,0x91  ,0x18  ,0x58  ,
0x82  ,0x94  ,0xA5  ,0xFF  ,0xAF  ,0xE8  ,0xCB  ,
0x2F  ,0x7D  ,0x72  ,0xA5  ,0xB5  ,0xC1  ,0x46  ,
0xAE
};

uint8_t  CHARGE                    = 1; //�Ƿ�ӳ������־λ��1Ϊ�ӳ������0Ϊ�γ������
uint8_t  no_charger_full_jump      = 0;
uint32_t allow_no_charger_full     = 0;
uint32_t allow_charger_always_zero = 0;
uint8_t  if_quickstart             = 0;
uint8_t  reset_loop                = 0;

volatile CW2015_BATTERY CW2015_Data;             //����CW2015��ȡ������    
I2C_HandleTypeDef              hi2c2;



/*IIC2��ʼ�� �����Ƴ�ʼ������ ÿ�ο�����Ҫִ��
return 
1 : i2c��д�� return 
2 : оƬ����sleepģʽ return 
3 : д���profile��Ϣ������������еĲ�һ�� return 
4 : оƬ������30s�ڶ�����ֵһֱ�쳣*/
uint8_t IIC2_CW2015_Init(void)
{
	uint32_t i;
	uint8_t ret;
	uint8_t reg_val;
	
	GPIO_InitTypeDef GPIO_Initure;
	
	/*****************************GPIO��ʼ��*********************************/
	__HAL_RCC_GPIOB_CLK_ENABLE();                              //ʹ��GPIOFʱ��
	__HAL_RCC_I2C2_CLK_ENABLE();
	
	/**I2C2 GPIO Configuration    
	PB10     ------> I2C2_SCL
	PB11     ------> I2C2_SDA 
	*/
	GPIO_Initure.Pin       = GPIO_PIN_10|GPIO_PIN_11;
	GPIO_Initure.Mode      = GPIO_MODE_AF_OD;
	GPIO_Initure.Pull      = GPIO_PULLUP;
	GPIO_Initure.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_Initure.Alternate = GPIO_AF4_I2C2;
	HAL_GPIO_Init(GPIOB, &GPIO_Initure);

	/*****************************IIC��ʼ��*********************************/
	hi2c2.Instance              = I2C2;
  hi2c2.Init.Timing           = 0x6000030D;
  hi2c2.Init.OwnAddress1      = 238;
  hi2c2.Init.AddressingMode   = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode  = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2      = 0;
  hi2c2.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c2.Init.GeneralCallMode  = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode    = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

	/**Configure Analogue filter 
	*/
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c2, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

	/**Configure Digital filter 
	*/
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c2, 0) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }	
	
	/****************************CW2015��ʼ��********************************/	
	
	/* wake up cw2015/13 from sleep mode */
	reg_val = MODE_NORMAL;
	ret = cw_write(REG_MODE, &reg_val);
	if(ret)
	{
		usb_printf("CW2015 ��д����!!!\r\n");
		return 1;
	}

	delay_us(100); //delay 100us
	
	/* check ATHD if not right */
	ret = cw_read(REG_CONFIG, &reg_val);
	if(ret)
	{
		usb_printf("CW2015 ��д����!!!\r\n");
		return 1;
	}
	if((reg_val & 0xf8) != ATHD)
	{
		//"the new ATHD need set"
		reg_val &= 0x07;    /* clear ATHD */
		reg_val |= ATHD;    /* set ATHD */
		ret = cw_write(REG_CONFIG, &reg_val);
		if(ret)
		{
			usb_printf("CW2015 ��д����!!!\r\n");
			return 1;
		}
	}	
	
	/* check config_update_flag if not right */
	ret = cw_read(REG_CONFIG, &reg_val);
	if(ret)
	{
		usb_printf("CW2015 ��д����!!!\r\n");
		return 1;
	}
	if(!(reg_val & CONFIG_UPDATE_FLG))
	{
		//"update flag for new battery info need set"
		ret = cw_update_config_info();
		if(ret)
		{
			usb_printf("CW2015 ��д����!!!\r\n");
			return 1;
		}
	}
	else
	{
		for(i = 0; i < SIZE_BATINFO; i++)
		{ 
			ret = cw_read(REG_BATINFO +i, &reg_val);
			if(ret)
			{
				usb_printf("CW2015 ��д����!!!\r\n");
				return 1;
			}
			if(cw_bat_config_info[i] != reg_val)
			{
				break;
			}
		}
		if(i != SIZE_BATINFO)
		{
			//"update flag for new battery info need set"
			ret = cw_update_config_info();
			if(ret)
			{
				usb_printf("CW2015 ��д����!!!\r\n");
				return 1;
			}
		}
	}
	
	/* check SOC if not eqaul 255 */
	for (i = 0; i < 30; i++) 
	{
		ret = cw_read(REG_SOC, &reg_val);
		if (ret)
		{
			usb_printf("CW2015 ��д����!!!\r\n");
			return 1;
		}
		else if (reg_val <= 100) 
			break;
		delay_ms(100);//delay 100ms
  }
	
	if (i >=30)
	{
			reg_val = MODE_SLEEP;
			ret = cw_write(REG_MODE, &reg_val);
			// "cw2015/cw2013 input unvalid power error_2\n";
		  usb_printf("оƬ������3s�ڶ�����ֵһֱ�쳣!!!\r\n");
			return 4;
	} 
	
	usb_printf("CW2015 Init OK!!!\r\n");
	return 0;	
}



//------------------------IIC��д����--------------------------------
uint8_t cw_read(uint8_t point_reg,uint8_t *pdata)
{
	uint8_t ret;
	uint8_t reg_val;
	reg_val = point_reg;
	ret = HAL_I2C_Master_Transmit(&hi2c2, WRITE_CW2015, &reg_val, 1, 0xFF);
  ret = HAL_I2C_Master_Receive(&hi2c2, READ_CW2015, pdata, 1, 0xFF);	
	return ret;
}

uint8_t cw_read_MultiData(uint8_t point_reg,uint8_t *pdata, uint16_t Size)
{
	uint8_t ret;
	uint8_t reg_val;
	reg_val = point_reg;
	//��ȡ��ʽ1
	//ret = HAL_I2C_Master_Transmit(&hi2c2, WRITE_CW2015, &reg_val, 1, 0xFF);
	//ret = HAL_I2C_Master_Receive(&hi2c2, READ_CW2015, pdata, Size, 0xFF);	
	//��ȡ��ʽ2
	ret = HAL_I2C_Mem_Read(&hi2c2, WRITE_CW2015, reg_val, I2C_MEMADD_SIZE_8BIT, pdata, Size, 0xFF);	
	return ret;
}

uint8_t cw_write(uint8_t point_reg,uint8_t *pdata)
{
	uint8_t ret;
  ret = HAL_I2C_Mem_Write(&hi2c2, WRITE_CW2015, point_reg, I2C_MEMADD_SIZE_8BIT, pdata, 1, 0xFF);
	
	return ret;
}

uint8_t cw2015_por(void)
{
	uint8_t ret = 0;
	unsigned char reset_val = 0;
	reset_val = MODE_SLEEP;             
	ret = cw_write(REG_MODE, &reset_val);
	if (ret)
	{
		usb_printf("CW2015 ��д����!!!\r\n");
		return 1;
	}
	delay_us(100); //delay 100us
	
	reset_val = MODE_NORMAL;
	ret = cw_write(REG_MODE, &reset_val);
	if (ret)
	{
		usb_printf("CW2015 ��д����!!!\r\n");
		return 1;
	}
	delay_us(100); //delay 100us
	
	ret = IIC2_CW2015_Init();
	if (ret) 
	{
		usb_printf("CW2015 ��д����!!!\r\n");
		return 1;
	}
	return 0;
}

/*��������������Ǹ���ic�ڵĵ��profile��Ϣ��һ��ֻ����ic VDD��������ϵ�ʱ��ִ�� 
return 1 : i2c��д�� return 2 : оƬ����sleepģʽ
return 3 : д���profile��Ϣ������������еĲ�һ��*/
uint8_t cw_update_config_info(void)
{
	uint8_t ret = 0;
	uint32_t i;
	uint8_t reset_val;
	uint8_t reg_val;
	/* make sure no in sleep mode */
	ret = cw_read(REG_MODE, &reg_val);
	if(ret)
	{
		usb_printf("CW2015 ��д����!!!\r\n");
		return 1;
	}
	if((reg_val & MODE_SLEEP_MASK) == MODE_SLEEP)
	{
		usb_printf("CW2015 ����sleepģʽ!!!\r\n");
		return 2;
	}
	/* update new battery info */
	for(i = 0; i < SIZE_BATINFO; i++)
	{
		reg_val = cw_bat_config_info[i];
		ret = cw_write(REG_BATINFO+i, &reg_val);
		if(ret)
		{
			usb_printf("CW2015 ��д����!!!\r\n");
		  return 1;
		}
	}

	/* readback & check */
	for(i = 0; i < SIZE_BATINFO; i++)
	{
		ret = cw_read(REG_BATINFO+i, &reg_val);
		if(ret)
		{
			usb_printf("CW2015 ��д����!!!\r\n");
			return 1;
		}
		if(reg_val != cw_bat_config_info[i])
		{
			usb_printf("д���profile��Ϣ������������еĲ�һ��!!!\r\n");
	  	return 3;
		}
	}
	/* set cw2015/cw2013 to use new battery info */
	ret = cw_read(REG_CONFIG, &reg_val);
	if(ret)
	{
		usb_printf("CW2015 ��д����!!!\r\n");
		return 1;
	}
	reg_val |= CONFIG_UPDATE_FLG;   /* set UPDATE_FLAG */
	reg_val &= 0x07;                /* clear ATHD */
	reg_val |= ATHD;                /* set ATHD */
	ret = cw_write(REG_CONFIG, &reg_val);
	if(ret)
	{
		usb_printf("CW2015 ��д����!!!\r\n");
		return 1;
	}
	/* reset */
	reset_val = MODE_NORMAL;
	reg_val   = MODE_RESTART;
	ret = cw_write(REG_MODE, &reg_val);
	if(ret)
	{
		usb_printf("CW2015 ��д����!!!\r\n");
		return 1;
	}
	delay_us(100);     //delay 100us   
	ret = cw_write(REG_MODE, &reset_val);
	if(ret)
	{
		usb_printf("CW2015 ��д����!!!\r\n");
		return 1;
	}   
	return 0;
}

int32_t cw2015_get_soc(void)
{
	uint8_t ret = 0;
	uint8_t reg_val;
	int32_t cw_capacity;
	int32_t allow_capacity;
	
	ret = cw_read(REG_SOC, &reg_val);
	if(ret)
	{
		usb_printf("CW2015 ��д����!!!\r\n");
		return -1;
	}
	
	cw_capacity = reg_val;
	/*����ic�������⣬��ȡ�������ں���ֵ��Χ�ڣ�����ic*/
	if ((cw_capacity < 0) || (cw_capacity > 100)) 
	{
		//"get cw_capacity error; cw_capacity = %d\n"
    reset_loop++;
		if (reset_loop >5) 
		{ 
			ret = cw2015_por(); //por ic
			if(ret)
			{
				usb_printf("CW2015 ��д����!!!\r\n");
				return -1;
			}
			reset_loop =0;               
		}                   
    return CW2015_Data.capacity;
  }
	else 
	{
		reset_loop =0;
  }

	/*����ǳ��״̬������Ӧ�����������ӵģ���������ʱ������ζ�ȡ�ĵ������ϴ�С����ʾ�ϴε�����*/
	/*ʲô����»�������������أ���Ϊ��˾��������С��λ�����籾�ε���0x04�Ĵ���������ֵ��9.01��*/
	/*��Ϊ����ֻ��03�Ĵ��������Ը��ͻ���ʾ��ֵ��9�����´ζ�ȡ�ĵ�����8.99*/
	/*��ô�´���ʾ���ͻ��ĵ�����8���ӿͻ���ʾ��������̫�ÿ����������������*/
	/*�ŵ�ʱ����ͬ���Ĵ���*/
	if(((CW2015_Data.usb_online == 1) && (cw_capacity == (CW2015_Data.capacity - 1)))
	 ||((CW2015_Data.usb_online == 0) && (cw_capacity == (CW2015_Data.capacity + 1))))
	{
		// modify battery level swing
		if(!((cw_capacity == 0 && CW2015_Data.capacity <= 2)||(cw_capacity == 100 && CW2015_Data.capacity == 99)))
		{			
			cw_capacity = CW2015_Data.capacity;
		}
	}
	
	
	/*����ǿͻ����������⣬�ͻ�ʹ�õ�charger ic�����ic�����Ȳ��Ǻܸߣ�
	��Щicֻ�ܰѵ�س�絽4.1V�������ȡ�������ʱ�����ѹ�����4.2V��
	��ô����Զ��ʾ����100%*/
	/*�����������������ַ�����1������д�Ĵ���������ʾ���ͻ�һ���ٵ�ֵ��һ������ӵ�100��
	2���������޸�profile��������ʾ100%ʱ�ĵ�ѹ�㣨��������������ǻ���Щcharger icֻ���õ�س䵽4.0�����������ˣ���
	��ǰ��oppo��һ��charger��������������
	*/
	if((CW2015_Data.usb_online == 1) && (cw_capacity >= 80) && (cw_capacity <= CW2015_Data.capacity) )
	{     
		// avoid not charge full
		allow_no_charger_full++;
		if(allow_no_charger_full >= BATTERY_UP_MAX_CHANGE)
		{
			allow_capacity = CW2015_Data.capacity + 1; 
			cw_capacity = (allow_capacity <= 100) ? allow_capacity : 100;
			no_charger_full_jump =1;
			allow_no_charger_full =0;
		}
		else if(cw_capacity <= CW2015_Data.capacity)
		{
			cw_capacity = CW2015_Data.capacity; 
		}
	}
	/*��εĴ����ǵ�������ͨ���ϵ�����������ȥ�ļٵ�ֵ����ôҪ�üٵķ�����������������100ֱ���������ʵֵ�����*/
  else if((CW2015_Data.usb_online == 0) && (cw_capacity <= CW2015_Data.capacity ) && (cw_capacity >= 90) && (no_charger_full_jump == 1))
	{
		// avoid battery level jump to CW_BAT
		if(CW2015_Data.usb_online == 0) 
		   allow_no_charger_full++;
		if(allow_no_charger_full >= BATTERY_DOWN_MIN_CHANGE)
		{
			allow_capacity = CW2015_Data.capacity - 1;
			allow_no_charger_full =0; 
			if (cw_capacity >= allow_capacity)
			{
				no_charger_full_jump =0;
			}
			else
			{
				cw_capacity = (allow_capacity > 0) ? allow_capacity : 0;
			}
		}
		else if(cw_capacity <= CW2015_Data.capacity)
		{
			cw_capacity = CW2015_Data.capacity;
		}
	}
	else
	{
		allow_no_charger_full =0;
	}

	/*ic�����ˣ����˺ܾ�һֱ����0%��һ�������ð��Сʱ����ô������ic*/
	if((CW2015_Data.usb_online > 0) && (cw_capacity == 0))
	{		  
		allow_charger_always_zero++;
		if((allow_charger_always_zero >= BATTERY_DOWN_MIN_CHANGE_SLEEP) && (if_quickstart == 0))
		{
      ret = cw2015_por(); //por ic
			if(ret)
			{
				usb_printf("CW2015 ��д����!!!\r\n");
				return -1;
			}
			if_quickstart = 1;
			allow_charger_always_zero =0;
		}
	}
	else if((if_quickstart == 1)&&(CW2015_Data.usb_online == 0))
	{
		if_quickstart = 0;
	}	
	
	return cw_capacity;
}

float cw2015_get_vcell(void)
{ 
	uint8_t cw2015_buf[2] = {0};
	uint16_t tem;
	float voltage;
	cw_read(REG_VCELL, cw2015_buf);
	cw_read(REG_VCELL+1, cw2015_buf+1);
	tem = ((uint16_t)cw2015_buf[0]<<8) | cw2015_buf[1];//��ص�ѹ
	voltage = tem * 305.0 / 1000000.0;
	return voltage;
}

/**
  * @brief  ʹ��IIC1��ȡCW2015�Ĵ���������
  * @param  ��
  * @retval ��
  */
void IIC2_CW2015_Read(void)
{	
	//��ȡ��ѹ�͵����Ĵ����е�����
	uint8_t ret = 0;
	uint8_t cw2015_buf[4] = {0};
	ret = cw_read_MultiData(REG_VCELL, cw2015_buf,4);
	if(ret)
	{
		usb_printf("CW2015 ��д����!!!\r\n");
		return;
	}

	//�Ե�ѹ�͵����Ĵ����е����ݽ��д������ʵ�ʵĵ�ص�ѹ�͵�ص���	
	//1.�Ե�ѹ�Ĵ����е����ݽ��д������ʵ�ʵĵ�ص�ѹ	
	uint16_t tem;
	float    voltage;	
	tem = ((uint16_t)cw2015_buf[0]<<8) | cw2015_buf[1];//��ص�ѹ
	voltage = tem * 305.0 / 1000000.0;
		
	CW2015_Data.voltage  = voltage;//��ȡ��ǰ��ص�ѹ
	

	//2.�Ե����Ĵ����е����ݽ��д������ʵ�ʵĵ�ص���
	int32_t  cw_capacity;
	int32_t  allow_capacity;	
	cw_capacity = cw2015_buf[2];
	/*����ic�������⣬��ȡ�������ں���ֵ��Χ�ڣ�����ic*/
	if ((cw_capacity < 0) || (cw_capacity > 100)) 
	{
		//"get cw_capacity error; cw_capacity = %d\n"
    reset_loop++;
		if (reset_loop >5) 
		{ 
			ret = cw2015_por(); //por ic
			if(ret)
			{
				usb_printf("CW2015 ��д����!!!\r\n");
				return;
			}
			reset_loop =0;               
		}                   
    return;
  }
	else 
	{
		reset_loop =0;
  }

	/*����ǳ��״̬������Ӧ�����������ӵģ���������ʱ������ζ�ȡ�ĵ������ϴ�С����ʾ�ϴε�����*/
	/*ʲô����»�������������أ���Ϊ��˾��������С��λ�����籾�ε���0x04�Ĵ���������ֵ��9.01��*/
	/*��Ϊ����ֻ��03�Ĵ��������Ը��ͻ���ʾ��ֵ��9�����´ζ�ȡ�ĵ�����8.99*/
	/*��ô�´���ʾ���ͻ��ĵ�����8���ӿͻ���ʾ��������̫�ÿ����������������*/
	/*�ŵ�ʱ����ͬ���Ĵ���*/
	if(((CW2015_Data.usb_online == 1) && (cw_capacity == (CW2015_Data.capacity - 1)))
	 ||((CW2015_Data.usb_online == 0) && (cw_capacity == (CW2015_Data.capacity + 1))))
	{
		// modify battery level swing
		if(!((cw_capacity == 0 && CW2015_Data.capacity <= 2)||(cw_capacity == 100 && CW2015_Data.capacity == 99)))
		{			
			cw_capacity = CW2015_Data.capacity;
		}
	}	
	
	/*����ǿͻ����������⣬�ͻ�ʹ�õ�charger ic�����ic�����Ȳ��Ǻܸߣ�
	��Щicֻ�ܰѵ�س�絽4.1V�������ȡ�������ʱ�����ѹ�����4.2V��
	��ô����Զ��ʾ����100%*/
	/*�����������������ַ�����1������д�Ĵ���������ʾ���ͻ�һ���ٵ�ֵ��һ������ӵ�100��
	2���������޸�profile��������ʾ100%ʱ�ĵ�ѹ�㣨��������������ǻ���Щcharger icֻ���õ�س䵽4.0�����������ˣ���
	��ǰ��oppo��һ��charger��������������
	*/
	if((CW2015_Data.usb_online == 1) && (cw_capacity >= 80) && (cw_capacity <= CW2015_Data.capacity) )
	{     
		// avoid not charge full
		allow_no_charger_full++;
		if(allow_no_charger_full >= BATTERY_UP_MAX_CHANGE)
		{
			allow_capacity = CW2015_Data.capacity + 1; 
			cw_capacity = (allow_capacity <= 100) ? allow_capacity : 100;
			no_charger_full_jump =1;
			allow_no_charger_full =0;
		}
		else if(cw_capacity <= CW2015_Data.capacity)
		{
			cw_capacity = CW2015_Data.capacity; 
		}
	}
	/*��εĴ����ǵ�������ͨ���ϵ�����������ȥ�ļٵ�ֵ����ôҪ�üٵķ�����������������100ֱ���������ʵֵ�����*/
  else if((CW2015_Data.usb_online == 0) && (cw_capacity <= CW2015_Data.capacity ) && (cw_capacity >= 90) && (no_charger_full_jump == 1))
	{
		// avoid battery level jump to CW_BAT
		if(CW2015_Data.usb_online == 0) 
		   allow_no_charger_full++;
		if(allow_no_charger_full >= BATTERY_DOWN_MIN_CHANGE)
		{
			allow_capacity = CW2015_Data.capacity - 1;
			allow_no_charger_full =0; 
			if (cw_capacity >= allow_capacity)
			{
				no_charger_full_jump =0;
			}
			else
			{
				cw_capacity = (allow_capacity > 0) ? allow_capacity : 0;
			}
		}
		else if(cw_capacity <= CW2015_Data.capacity)
		{
			cw_capacity = CW2015_Data.capacity;
		}
	}
	else
	{
		allow_no_charger_full =0;
	}

	/*ic�����ˣ����˺ܾ�һֱ����0%��һ�������ð��Сʱ����ô������ic*/
	if((CW2015_Data.usb_online > 0) && (cw_capacity == 0))
	{		  
		allow_charger_always_zero++;
		if((allow_charger_always_zero >= BATTERY_DOWN_MIN_CHANGE_SLEEP) && (if_quickstart == 0))
		{
      ret = cw2015_por(); //por ic
			if(ret)
			{
				usb_printf("CW2015 ��д����!!!\r\n");
				return;
			}
			if_quickstart = 1;
			allow_charger_always_zero =0;
		}
	}
	else if((if_quickstart == 1)&&(CW2015_Data.usb_online == 0))
	{
		if_quickstart = 0;
	}	

	CW2015_Data.capacity = cw_capacity;	//��ȡ��ǰ��ص���

	usb_printf("��ص�ѹ��%fV,���������%d%%\r\n",CW2015_Data.voltage,CW2015_Data.capacity);
}



	


