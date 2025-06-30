#ifndef __DM_H
#define __DM_H

#include "sys.h"

/******************************************************************************************/
/* 行引脚 定义 */
#define	REFIN1_PORT              GPIOA
#define REFIN1_PIN							 GPIO_PIN_6
#define REFIN1_ENABLE()          do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)

#define	REFIN2_PORT              GPIOA
#define REFIN2_PIN							 GPIO_PIN_7
#define REFIN2_ENABLE()          do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)

#define	HANG1_1_PORT             GPIOE
#define HANG1_1_PIN							 GPIO_PIN_4
#define HANG1_1_ENABLE()          do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)

#define	HANG1_2_PORT             GPIOE
#define HANG1_2_PIN							 GPIO_PIN_5
#define HANG1_2_ENABLE()          do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)

#define	HANG1_3_PORT             GPIOE
#define HANG1_3_PIN							 GPIO_PIN_2
#define HANG1_3_ENABLE()          do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)

#define	HANG1_4_PORT             GPIOE
#define HANG1_4_PIN							 GPIO_PIN_3
#define HANG1_4_ENABLE()          do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)

#define	HANG2_1_PORT             GPIOE
#define HANG2_1_PIN							 GPIO_PIN_0
#define HANG2_1_ENABLE()          do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)

#define	HANG2_2_PORT             GPIOE
#define HANG2_2_PIN							 GPIO_PIN_1
#define HANG2_2_ENABLE()          do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)

#define	HANG2_3_PORT             GPIOB
#define HANG2_3_PIN							 GPIO_PIN_8
#define HANG2_3_ENABLE()          do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)

#define	HANG2_4_PORT             GPIOB
#define HANG2_4_PIN							 GPIO_PIN_9
#define HANG2_4_ENABLE()          do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)

#define	LIE1_1_PORT              GPIOB
#define LIE1_1_PIN							 GPIO_PIN_7
#define LIE1_1_ENABLE()          do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)

#define	LIE1_2_PORT              GPIOB
#define LIE1_2_PIN							 GPIO_PIN_6
#define LIE1_2_ENABLE()          do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)

#define	LIE1_3_PORT              GPIOB
#define LIE1_3_PIN							 GPIO_PIN_5
#define LIE1_3_ENABLE()          do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)

#define	LIE1_4_PORT              GPIOB
#define LIE1_4_PIN							 GPIO_PIN_4
#define LIE1_4_ENABLE()          do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)

#define	LIE1_5_PORT              GPIOB
#define LIE1_5_PIN							 GPIO_PIN_3
#define LIE1_5_ENABLE()          do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)

#define	LIE1_6_PORT              GPIOD
#define LIE1_6_PIN							 GPIO_PIN_7
#define LIE1_6_ENABLE()          do{ __HAL_RCC_GPIOD_CLK_ENABLE(); }while(0)

#define	LIE1_7_PORT              GPIOD
#define LIE1_7_PIN							 GPIO_PIN_6
#define LIE1_7_ENABLE()          do{ __HAL_RCC_GPIOD_CLK_ENABLE(); }while(0)

#define	LIE1_8_PORT              GPIOD
#define LIE1_8_PIN							 GPIO_PIN_5
#define LIE1_8_ENABLE()          do{ __HAL_RCC_GPIOD_CLK_ENABLE(); }while(0)

#define	LIE1_9_PORT              GPIOD
#define LIE1_9_PIN							 GPIO_PIN_4
#define LIE1_9_ENABLE()          do{ __HAL_RCC_GPIOD_CLK_ENABLE(); }while(0)

#define	LIE1_10_PORT              GPIOD
#define LIE1_10_PIN							 GPIO_PIN_3
#define LIE1_10_ENABLE()          do{ __HAL_RCC_GPIOD_CLK_ENABLE(); }while(0)

#define	LIE1_11_PORT              GPIOD
#define LIE1_11_PIN							 GPIO_PIN_2
#define LIE1_11_ENABLE()          do{ __HAL_RCC_GPIOD_CLK_ENABLE(); }while(0)

#define	LIE1_12_PORT              GPIOD
#define LIE1_12_PIN							 GPIO_PIN_1
#define LIE1_12_ENABLE()          do{ __HAL_RCC_GPIOD_CLK_ENABLE(); }while(0)

#define	LIE1_13_PORT              GPIOD
#define LIE1_13_PIN							 GPIO_PIN_0
#define LIE1_13_ENABLE()          do{ __HAL_RCC_GPIOD_CLK_ENABLE(); }while(0)

#define	LIE1_14_PORT              GPIOC
#define LIE1_14_PIN							 GPIO_PIN_12
#define LIE1_14_ENABLE()          do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)

#define	LIE1_15_PORT              GPIOC
#define LIE1_15_PIN							 GPIO_PIN_11
#define LIE1_15_ENABLE()          do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)

#define	LIE1_16_PORT              GPIOC
#define LIE1_16_PIN							 GPIO_PIN_10
#define LIE1_16_ENABLE()          do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)





#define	LIE2_1_PORT              GPIOC
#define LIE2_1_PIN							 GPIO_PIN_9
#define LIE2_1_ENABLE()          do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)

#define	LIE2_2_PORT              GPIOB
#define LIE2_2_PIN							 GPIO_PIN_12
#define LIE2_2_ENABLE()          do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)

#define	LIE2_3_PORT              GPIOC
#define LIE2_3_PIN							 GPIO_PIN_8
#define LIE2_3_ENABLE()          do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)

#define	LIE2_4_PORT              GPIOB
#define LIE2_4_PIN							 GPIO_PIN_13
#define LIE2_4_ENABLE()          do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)

#define	LIE2_5_PORT              GPIOD
#define LIE2_5_PIN							 GPIO_PIN_7
#define LIE2_5_ENABLE()          do{ __HAL_RCC_GPIOD_CLK_ENABLE(); }while(0)

#define	LIE2_6_PORT              GPIOB
#define LIE2_6_PIN							 GPIO_PIN_14
#define LIE2_6_ENABLE()          do{ __HAL_RCC_GPIOD_CLK_ENABLE(); }while(0)

#define	LIE2_7_PORT              GPIOD
#define LIE2_7_PIN							 GPIO_PIN_6
#define LIE2_7_ENABLE()          do{ __HAL_RCC_GPIOD_CLK_ENABLE(); }while(0)

#define	LIE2_8_PORT              GPIOB
#define LIE2_8_PIN							 GPIO_PIN_15
#define LIE2_8_ENABLE()          do{ __HAL_RCC_GPIOD_CLK_ENABLE(); }while(0)

#define	LIE2_9_PORT              GPIOD
#define LIE2_9_PIN							 GPIO_PIN_15
#define LIE2_9_ENABLE()          do{ __HAL_RCC_GPIOD_CLK_ENABLE(); }while(0)

#define	LIE2_10_PORT              GPIOD
#define LIE2_10_PIN							 GPIO_PIN_8
#define LIE2_10_ENABLE()          do{ __HAL_RCC_GPIOD_CLK_ENABLE(); }while(0)

#define	LIE2_11_PORT              GPIOD
#define LIE2_11_PIN							 GPIO_PIN_14
#define LIE2_11_ENABLE()          do{ __HAL_RCC_GPIOD_CLK_ENABLE(); }while(0)

#define	LIE2_12_PORT              GPIOD
#define LIE2_12_PIN							 GPIO_PIN_9
#define LIE2_12_ENABLE()          do{ __HAL_RCC_GPIOD_CLK_ENABLE(); }while(0)

#define	LIE2_13_PORT              GPIOD
#define LIE2_13_PIN							 GPIO_PIN_13
#define LIE2_13_ENABLE()          do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)

#define	LIE2_14_PORT              GPIOD
#define LIE2_14_PIN							 GPIO_PIN_10
#define LIE2_14_ENABLE()          do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)

#define	LIE2_15_PORT              GPIOD
#define LIE2_15_PIN							 GPIO_PIN_12
#define LIE2_15_ENABLE()          do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)

#define	LIE2_16_PORT              GPIOD
#define LIE2_16_PIN							 GPIO_PIN_11
#define LIE2_16_ENABLE()          do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)

/* 行列选择端口定义 */
#define REFIN1(x)   do{ x ? \
                      HAL_GPIO_WritePin(REFIN1_PORT, REFIN1_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(REFIN1_PORT, REFIN1_PIN, GPIO_PIN_RESET); \
                  }while(0) 

#define REFIN2(x)   do{ x ? \
                      HAL_GPIO_WritePin(REFIN2_PORT, REFIN2_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(REFIN2_PORT, REFIN2_PIN, GPIO_PIN_RESET); \
                  }while(0)
									
#define HANG1_1(x)   do{ x ? \
                      HAL_GPIO_WritePin(HANG1_1_PORT, HANG1_1_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(HANG1_1_PORT, HANG1_1_PIN, GPIO_PIN_RESET); \
                  }while(0) 

#define HANG1_2(x)   do{ x ? \
                      HAL_GPIO_WritePin(HANG1_2_PORT, HANG1_2_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(HANG1_2_PORT, HANG1_2_PIN, GPIO_PIN_RESET); \
                  }while(0) 

#define HANG1_3(x)   do{ x ? \
                      HAL_GPIO_WritePin(HANG1_3_PORT, HANG1_3_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(HANG1_3_PORT, HANG1_3_PIN, GPIO_PIN_RESET); \
                  }while(0) 

#define HANG1_4(x)   do{ x ? \
                      HAL_GPIO_WritePin(HANG1_4_PORT, HANG1_4_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(HANG1_4_PORT, HANG1_4_PIN, GPIO_PIN_RESET); \
                  }while(0) 

#define HANG2_1(x)   do{ x ? \
                      HAL_GPIO_WritePin(HANG2_1_PORT, HANG2_1_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(HANG2_1_PORT, HANG2_1_PIN, GPIO_PIN_RESET); \
                  }while(0) 

#define HANG2_2(x)   do{ x ? \
                      HAL_GPIO_WritePin(HANG2_2_PORT, HANG2_2_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(HANG2_2_PORT, HANG2_2_PIN, GPIO_PIN_RESET); \
                  }while(0) 

#define HANG2_3(x)   do{ x ? \
                      HAL_GPIO_WritePin(HANG2_3_PORT, HANG2_3_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(HANG2_3_PORT, HANG2_3_PIN, GPIO_PIN_RESET); \
                  }while(0) 

#define HANG2_4(x)   do{ x ? \
                      HAL_GPIO_WritePin(HANG2_4_PORT, HANG2_4_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(HANG2_4_PORT, HANG2_4_PIN, GPIO_PIN_RESET); \
                  }while(0) 
																		

#define LIE2_1(x)   do{ x ? \
                      HAL_GPIO_WritePin(LIE2_1_PORT, LIE2_1_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(LIE2_1_PORT, LIE2_1_PIN, GPIO_PIN_RESET); \
                  }while(0) 
#define LIE2_2(x)   do{ x ? \
                      HAL_GPIO_WritePin(LIE2_2_PORT, LIE2_2_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(LIE2_2_PORT, LIE2_2_PIN, GPIO_PIN_RESET); \
                  }while(0)
#define LIE2_3(x)   do{ x ? \
                      HAL_GPIO_WritePin(LIE2_3_PORT, LIE2_3_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(LIE2_3_PORT, LIE2_3_PIN, GPIO_PIN_RESET); \
                  }while(0)
#define LIE2_4(x)   do{ x ? \
                      HAL_GPIO_WritePin(LIE2_4_PORT, LIE2_4_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(LIE2_4_PORT, LIE2_4_PIN, GPIO_PIN_RESET); \
                  }while(0)
#define LIE2_5(x)   do{ x ? \
                      HAL_GPIO_WritePin(LIE2_5_PORT, LIE2_5_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(LIE2_5_PORT, LIE2_5_PIN, GPIO_PIN_RESET); \
                  }while(0)
#define LIE2_6(x)   do{ x ? \
                      HAL_GPIO_WritePin(LIE2_6_PORT, LIE2_6_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(LIE2_6_PORT, LIE2_6_PIN, GPIO_PIN_RESET); \
                  }while(0)
#define LIE2_7(x)   do{ x ? \
                      HAL_GPIO_WritePin(LIE2_7_PORT, LIE2_7_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(LIE2_7_PORT, LIE2_7_PIN, GPIO_PIN_RESET); \
                  }while(0)
#define LIE2_8(x)   do{ x ? \
                      HAL_GPIO_WritePin(LIE2_8_PORT, LIE2_8_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(LIE2_8_PORT, LIE2_8_PIN, GPIO_PIN_RESET); \
                  }while(0)
#define LIE2_9(x)   do{ x ? \
                      HAL_GPIO_WritePin(LIE2_9_PORT, LIE2_9_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(LIE2_9_PORT, LIE2_9_PIN, GPIO_PIN_RESET); \
                  }while(0)
#define LIE2_10(x)   do{ x ? \
                      HAL_GPIO_WritePin(LIE2_10_PORT, LIE2_10_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(LIE2_10_PORT, LIE2_10_PIN, GPIO_PIN_RESET); \
                  }while(0)
#define LIE2_11(x)   do{ x ? \
                      HAL_GPIO_WritePin(LIE2_11_PORT, LIE2_11_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(LIE2_11_PORT, LIE2_11_PIN, GPIO_PIN_RESET); \
                  }while(0)
#define LIE2_12(x)   do{ x ? \
                      HAL_GPIO_WritePin(LIE2_12_PORT, LIE2_12_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(LIE2_12_PORT, LIE2_12_PIN, GPIO_PIN_RESET); \
                  }while(0)
#define LIE2_13(x)   do{ x ? \
                      HAL_GPIO_WritePin(LIE2_13_PORT, LIE2_13_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(LIE2_13_PORT, LIE2_13_PIN, GPIO_PIN_RESET); \
                  }while(0)
#define LIE2_14(x)   do{ x ? \
                      HAL_GPIO_WritePin(LIE2_14_PORT, LIE2_14_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(LIE2_14_PORT, LIE2_14_PIN, GPIO_PIN_RESET); \
                  }while(0)
#define LIE2_15(x)   do{ x ? \
                      HAL_GPIO_WritePin(LIE2_15_PORT, LIE2_15_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(LIE2_15_PORT, LIE2_15_PIN, GPIO_PIN_RESET); \
                  }while(0)
#define LIE2_16(x)   do{ x ? \
                      HAL_GPIO_WritePin(LIE2_16_PORT, LIE2_16_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(LIE2_16_PORT, LIE2_16_PIN, GPIO_PIN_RESET); \
                  }while(0)

									
									

#define LIE1_1(x)   do{ x ? \
                      HAL_GPIO_WritePin(LIE1_1_PORT, LIE1_1_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(LIE1_1_PORT, LIE1_1_PIN, GPIO_PIN_RESET); \
                  }while(0) 

#define LIE1_2(x)   do{ x ? \
                      HAL_GPIO_WritePin(LIE1_2_PORT, LIE1_2_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(LIE1_2_PORT, LIE1_2_PIN, GPIO_PIN_RESET); \
                  }while(0)
#define LIE1_3(x)   do{ x ? \
                      HAL_GPIO_WritePin(LIE1_3_PORT, LIE1_3_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(LIE1_3_PORT, LIE1_3_PIN, GPIO_PIN_RESET); \
                  }while(0)
#define LIE1_4(x)   do{ x ? \
                      HAL_GPIO_WritePin(LIE1_4_PORT, LIE1_4_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(LIE1_4_PORT, LIE1_4_PIN, GPIO_PIN_RESET); \
                  }while(0)
#define LIE1_5(x)   do{ x ? \
                      HAL_GPIO_WritePin(LIE1_5_PORT, LIE1_5_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(LIE1_5_PORT, LIE1_5_PIN, GPIO_PIN_RESET); \
                  }while(0)
#define LIE1_6(x)   do{ x ? \
                      HAL_GPIO_WritePin(LIE1_6_PORT, LIE1_6_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(LIE1_6_PORT, LIE1_6_PIN, GPIO_PIN_RESET); \
                  }while(0)
#define LIE1_7(x)   do{ x ? \
                      HAL_GPIO_WritePin(LIE1_7_PORT, LIE1_7_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(LIE1_7_PORT, LIE1_7_PIN, GPIO_PIN_RESET); \
                  }while(0)
#define LIE1_8(x)   do{ x ? \
                      HAL_GPIO_WritePin(LIE1_8_PORT, LIE1_8_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(LIE1_8_PORT, LIE1_8_PIN, GPIO_PIN_RESET); \
                  }while(0)
#define LIE1_9(x)   do{ x ? \
                      HAL_GPIO_WritePin(LIE1_9_PORT, LIE1_9_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(LIE1_9_PORT, LIE1_9_PIN, GPIO_PIN_RESET); \
                  }while(0)
#define LIE1_10(x)   do{ x ? \
                      HAL_GPIO_WritePin(LIE1_10_PORT, LIE1_10_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(LIE1_10_PORT, LIE1_10_PIN, GPIO_PIN_RESET); \
                  }while(0)
#define LIE1_11(x)   do{ x ? \
                      HAL_GPIO_WritePin(LIE1_11_PORT, LIE1_11_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(LIE1_11_PORT, LIE1_11_PIN, GPIO_PIN_RESET); \
                  }while(0)
#define LIE1_12(x)   do{ x ? \
                      HAL_GPIO_WritePin(LIE1_12_PORT, LIE1_12_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(LIE1_12_PORT, LIE1_12_PIN, GPIO_PIN_RESET); \
                  }while(0)
#define LIE1_13(x)   do{ x ? \
                      HAL_GPIO_WritePin(LIE1_13_PORT, LIE1_13_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(LIE1_13_PORT, LIE1_13_PIN, GPIO_PIN_RESET); \
                  }while(0)
#define LIE1_14(x)   do{ x ? \
                      HAL_GPIO_WritePin(LIE1_14_PORT, LIE1_14_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(LIE1_14_PORT, LIE1_14_PIN, GPIO_PIN_RESET); \
                  }while(0)
#define LIE1_15(x)   do{ x ? \
                      HAL_GPIO_WritePin(LIE1_15_PORT, LIE1_15_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(LIE1_15_PORT, LIE1_15_PIN, GPIO_PIN_RESET); \
                  }while(0)
#define LIE1_16(x)   do{ x ? \
                      HAL_GPIO_WritePin(LIE1_16_PORT, LIE1_16_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(LIE1_16_PORT, LIE1_16_PIN, GPIO_PIN_RESET); \
                  }while(0)


/* 取反定义 */
#define REFIN1_TOGGLE()    do{ HAL_GPIO_TogglePin(REFIN1_PORT, REFIN1_PIN); }while(0)   
#define REFIN2_TOGGLE()    do{ HAL_GPIO_TogglePin(REFIN2_PORT, REFIN2_PIN); }while(0)
#define HANG1_1_TOGGLE()    do{ HAL_GPIO_TogglePin(HANG1_1_PORT, HANG1_1_PIN); }while(0)   /* HANG1_1 = !HANG1_1 */
#define HANG1_2_TOGGLE()    do{ HAL_GPIO_TogglePin(HANG1_2_PORT, HANG1_2_PIN); }while(0)   /* HANG1_2 = !HANG1_2 */									
#define HANG1_3_TOGGLE()    do{ HAL_GPIO_TogglePin(HANG1_3_PORT, HANG1_3_PIN); }while(0)   /* HANG1_3 = !HANG1_3 */
#define HANG1_4_TOGGLE()    do{ HAL_GPIO_TogglePin(HANG1_4_PORT, HANG1_4_PIN); }while(0)   /* HANG1_4 = !HANG1_4 */
#define HANG2_1_TOGGLE()    do{ HAL_GPIO_TogglePin(HANG2_1_PORT, HANG2_1_PIN); }while(0)   /* HANG2_1 = !HANG2_1 */
#define HANG2_2_TOGGLE()    do{ HAL_GPIO_TogglePin(HANG2_2_PORT, HANG2_2_PIN); }while(0)   /* HANG2_2 = !HANG2_2 */
#define HANG2_3_TOGGLE()    do{ HAL_GPIO_TogglePin(HANG2_3_PORT, HANG2_3_PIN); }while(0)   /* HANG2_3 = !HANG2_3 */
#define HANG2_4_TOGGLE()    do{ HAL_GPIO_TogglePin(HANG2_4_PORT, HANG2_4_PIN); }while(0)   /* HANG2_4 = !HANG2_4 */
#define LIE1_1_TOGGLE()    do{ HAL_GPIO_TogglePin(LIE1_1_PORT, LIE1_1_PIN); }while(0)   
#define LIE2_1_TOGGLE()    do{ HAL_GPIO_TogglePin(LIE2_1_PORT, LIE2_1_PIN); }while(0) 


/******************************************************************************************/
void scan_init(void);                    /* 行列选初始化 */
void scan1(void);
void scan2(void);
void scan3(void);
void scan4(void);
void scan5(void);
void scan6(void);
void scan7(void);
void scan8(void);
void scan9(void);
void scan10(void);
void scan11(void);
void scan12(void);
void scan13(void);
void scan14(void);
void scan15(void);
void scan16(void);


#endif

