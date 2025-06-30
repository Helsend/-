#ifndef _IIC2_CW2015_H
#define _IIC2_CW2015_H
#include "sys.h"

typedef struct {
	uint8_t  usb_online;
	uint8_t  alt;
	uint8_t  capacity;
	float    voltage;
}CW2015_BATTERY;

extern volatile CW2015_BATTERY CW2015_Data;

//IIC2���в�������
uint8_t IIC2_CW2015_Init(void);             //��ʼ��IIC2��IO��				 
void    IIC2_CW2015_Read(void);             //��ȡCW2015������������

//------------------------IIC��д����--------------------------------
uint8_t cw_read(uint8_t point_reg,uint8_t *pdata);
uint8_t cw_read_MultiData(uint8_t point_reg,uint8_t *pdata, uint16_t Size);
uint8_t cw_write(uint8_t point_reg,uint8_t *pdata);
uint8_t cw_update_config_info(void);
uint8_t cw2015_por(void);
int32_t cw2015_get_soc(void);
float   cw2015_get_vcell(void);

#endif

