#ifndef __XOLED_CORE_H__
#define __XOLED_CORE_H__


//#include "wiringPi.h"
//#include "wiringPiSPI.h"
#include "xoled_matrix.h"
#include "xoled_type.h"
#include "xoled_interface.h"

//#define OLED_PORT  GPIOB
//#define SCL_PORT   GPIO_Pin_6
//#define SDA_PORT   GPIO_Pin_7
//#define RST_PORT   GPIO_Pin_8
//#define D_C_PORT   GPIO_Pin_9

#define SH1106


#define Line_12_0  0
#define Line_12_1  13
#define Line_12_2  26
#define Line_12_3  39
#define Line_12_4  52



#define Line_16_1  0
#define Line_16_2  16
#define Line_16_3  32
#define Line_16_4  48




#define OLED_CMD   0	//写命令
#define OLED_DATA  1	//写数据

#define FONT_GBK      0
#define FONT_Unicode  1



/*__CombineChar__
ICL: 	Input Char Low
ICH: 	Input Char High
RemL: Low bit Num
RemH:	High bit Num
ICL : 
			L0
			L1 
			L2
			L3							RemL = 3
			L4							RemH = 8-3 = 5
			L5											
			L6												L5			
			L7							    			L6
ICH					->>>>>>>> 	  			L7
			H0 												H0
			H1                        H1
			H2                        H2
			H3                        H3
			H4                        H4
			H5
			H6
			H7


ICB : B7 B6 B5 B4 B3 B2 B1 B0
Low	:3
High = 8-3
__CombineChar__ = B2 B1 B0 A7 A6 A5 A4 A3
*/
#define __CombineChar__(ICL,ICH,RemH,RemL)	((ICL>>RemL)|(ICH<<RemH))	

typedef enum {
	Font_ASCII_0806 = 1,
	Font_ASCII_1206 ,
	Font_ASCII_1608 ,
	Font_ASCII_2412 ,
	Font_ASCII_3216 ,
	
	Font_DFW_1612,
	Font_DFW_2016,
	Font_DFW_2620,
	Font_DFW_3024,
	
}FontType_t;
typedef struct {
	TU16 XStart;
	TU16 YStart;
	TU16 XEnd;
	TU16 YEnd;
	TU32 Status;
}RefreshInfo_t;


extern volatile TU8  xOLED_GDRAM[GDRAM_XSize*(GDRAM_YSize/8+1)];


	
	
extern volatile Matrix_t Matrix_OLED_GRAM;
	
	
	
extern volatile TU8 GRAMUpdate;	
extern volatile TU8 GRAMBusy;

extern volatile TU16 ZoomDisX, ZoomDisY;


//OLED控制用函数
void xOLED_WR_Byte(TU8 dat,TU8 cmd);	    
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Refresh_Gram(void);	

void xOLED_Refresh_Gram( TU16 Offset_X, TU16 Offset_Y );	
void xOLED_Refresh_Gram_Part( TU16 Offset_X, TU16 Offset_Y, TU16 Obs_X, TU8 Obs_Page, TU16 XSize, TU8 PageSize );
void xOLED_Clear( TU8 vValue );
void xOLED_DrawPoint(TU16 x,TU16 y,TU16 t);
void xOLED_ShowChar(TU16 x,TU16 y,TU8 chr,FontType_t Font,TU8 mode);	
void xOLED_ShowString(TU16 x,TU16 y,FontType_t Font,TU8 mode,TU8 *p);
void xOLED_printf(TU16 x, TU16 y,FontType_t Font,TU8 mode, T8* Data, ...);

void xOLED_Init(void);
void xOLED_RefreshInit( void );




void OLED_Display_Chinese_12_12(TU8 x,TU8 y,TU8 ch[],TU8 mode);
void OLED_Display_Chinese_16_16(TU8 x,TU8 y,TU8 ch[],TU8 mode);
void OLED_Display_Chinese_32_32(TU8 x,TU8 y,TU8 ch[],TU8 mode);
void DisplayChineseEnglish(TU8 x,TU8 y,TU8 * ch_en,TU8 size,TU8 mode);
void DisplayChineseEnglish_No_Change_Line(TU8 x,TU8 y,TU8 * ch_en,TU8 size,TU8 mode);
void Read_font_form_flash(TU8 font[],TU8 data_read[] , TU8 size ,TU8 FONT_NAME);
void OLED_Display_Chinese(TU8 x,TU8 y,TU8 ch[],TU8 size ,TU8 mode);
void OLED_ShowChar_Flash(TU8 x,TU8 y,TU8 chr,TU8 size,TU8 mode);
void store_ASCII(TU8 size);
void Display_chinese_unicode(TU8 x,TU8 y,TU8 * ch_en,TU8 size,TU8 mode,TU8 length);
void Display_chinese_unicode_No_Change_Line(TU8 x,TU8 y,TU8 * ch_en,TU8 size,TU8 mode,TU8 length);

#endif
