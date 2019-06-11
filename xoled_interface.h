#ifndef __XOLED_INTERFACE_H__
#define __XOLED_INTERFACE_H__


#include "xoled_type.h"


#include "STM32F0Base.h"
//#include "wiringPi.h"
//#include "wiringPiSPI.h"


/**
	OLED 平台硬件接口

*/
#define xOLED_Pin_RST GPIO_Pin_12
#define xOLED_Pin_DC  GPIO_Pin_11



/**
	RST管脚控制映射
*/
#define xOLED_Itf_RST_Clr() 	{GPIOB->BRR = xOLED_Pin_RST;} //xOLED_Pin_RST=0//digitalWrite(22,LOW)//HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_RESET)//
#define xOLED_Itf_RST_Set() 	{GPIOB->BSRR = xOLED_Pin_RST;}//xOLED_Pin_RST=1//digitalWrite(22,HIGH)//HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_SET)//

/**
	数据、命令管脚控制映射
*/
#define xOLED_Itf_DC_Clr() 	  {GPIOB->BRR = xOLED_Pin_DC;}//xOLED_Pin_DC=0//digitalWrite(21,LOW)//HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,GPIO_PIN_RESET)//
#define xOLED_Itf_DC_Set()    {GPIOB->BSRR = xOLED_Pin_DC;}//xOLED_Pin_DC=1//digitalWrite(21,HIGH)//HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,GPIO_PIN_SET)//


/*OLED Physical Size*/

#define xOLED_XPosIdMax  127
#define xOLED_YPageIdMax 7

#define xOLED_XPosSize  (xOLED_XPosIdMax+1)
#define xOLED_YPageSize (xOLED_YPageIdMax+1)

/**
GDRAM size
*/

#define GDRAM_XSize				(256)//64*8 = 
#define GDRAM_YSize		    	(96)//64*8 = 
	



#define OLED0_ON()	//digitalWrite(28,0)
#define OLED0_OFF()	//digitalWrite(28,1)
#define OLED1_ON()	//digitalWrite(29,0)
#define OLED1_OFF()	//digitalWrite(29,1)





/**
	OLED 延时函数
*/

#define xOLED_Delay_ms(n)	delay_ms(n)//delay(n)//


extern void xOLED_Itf_HadwareInit( void );
extern void xOLED_Itf_WriteBytes(TU8 *data, TU32 Num);
extern void xOLED_Itf_WaitTransFinish( void );





#endif
