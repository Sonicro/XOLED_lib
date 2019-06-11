#include "xoled_core.h"
#include "xoled_font.h"  



#include "stdlib.h"
#include "stdarg.h"
#include "stdio.h"
#include "string.h"


/*

			Read  Me


Time 2019-1-1 20��30
Author�� He Sonicro

SSD1306  OLED�⣬



�����汾 V1.0.1

�û� ��Ҫ�޸�
xOLED_Interface.c  �� xOLED_Interface.h �Ա����ڲ�ͬƽ̨��ֲ

�û�Ӧ�ó�������� xOLED_Init(); ����ʼ������Ӳ����OLEDģ��
�û����������	���� xOLED_Refresh_Gram ��ע������128*64�����ص㣩	����
				���� xOLED_Refresh_Gram_Part��ע�����¾ֲ�������x��Ϊ1-128��  y��ֻ����Page ��1-8����
���������Դ���µ�OLED

xOLED_demo.c  չʾ�����ʹ�� ����

�޸���һЩ������ֵ�Bug

�޸� OLED�������� ������xOLED_Refresh_Gram()��xOLED_Refresh_GramPart()�����У�
  д��ָ�����DC��ƽʱ���ȴ�SPI��������ٽ���DC��ƽ���ģ�����Ч��ֹ����

��������������޸�ʱ�� 2019-1-30 18��34

��ǰ�汾 V1.0.3

1.���Ӷ�SH1106��֧��
2.�궨��OLED��x��С��bit����Y�Ĵ�СPage

 */	

//OLED���Դ�
//��Ÿ�ʽ����.
/*

Page ����

	LSB D0
	  ��
	MSB D7
	
	
*/

//[0]0 1 2 3 ... xOLED_XPosIdMax	
//[1]0 1 2 3 ... xOLED_XPosIdMax	
//[2]0 1 2 3 ... xOLED_XPosIdMax	
//[3]0 1 2 3 ... xOLED_XPosIdMax	
//[4]0 1 2 3 ... xOLED_XPosIdMax	
//[5]0 1 2 3 ... xOLED_XPosIdMax	
//[6]0 1 2 3 ... xOLED_XPosIdMax	
//[7]0 1 2 3 ... xOLED_XPosIdMax 	


	    

volatile TU16 ZoomDisX = 0, ZoomDisY = 0;
TU16 GlobleX = 0, GlobleY = 0;

volatile TU8 xOLED_GDRAM[GDRAM_XSize*(GDRAM_YSize/8+1)] = {0};//�����Դ�
volatile Matrix_t Matrix_OLED_GRAM={GDRAM_XSize,GDRAM_YSize,xOLED_GDRAM};//������������

volatile TU8 GRAMUpdate = 1;//����״̬
volatile TU8 GRAMBusy = 0;//æ��־
/**
  * @brief 
  * @param[in]  
  * @param[in]
  * @retval void
	* @ChangeData 2018-12-30-19:25
	* @History 	
  */
void xOLED_DrawPoint(TU16 x, TU16 y, TU16 t){

		Matrix_DrawPiont(x,y,(Matrix_t*)(&Matrix_OLED_GRAM),t);
}

/**
  * @brief 
  * @param[in]  
  * @param[in]
  * @retval void
	* @ChangeData 2018-12-30-19:25
	* @History 	
  */
void xOLED_ShowChar(TU16 x,TU16 y,TU8 chr,FontType_t Font,TU8 mode){
		TU8 temp,t,t1,t2;
		//TU16 x0=x,y0=y;
		TU16 SizeX,SizeY;
		const TU8* tPointer = 0;	

		if( Font == Font_ASCII_0806 ){
			
				chr=chr-' ';//�õ�ƫ�ƺ��ֵ	
				SizeX = 6;
				SizeY = 8;
				tPointer = (const TU8*)(&oled_asc2_0806);
		}
		else if( Font == Font_ASCII_1206 ){
			
				chr=chr-' ';//�õ�ƫ�ƺ��ֵ	
				SizeX = 6;
				SizeY = 12;
				tPointer = (const TU8*)(&oled_asc2_1206);
		}
		else if( Font == Font_ASCII_1608 ){
			
				chr=chr-' ';//�õ�ƫ�ƺ��ֵ	
				SizeX = 8;
				SizeY = 16;
				tPointer = (const TU8*)(&oled_asc2_1608);
		}
		else if( Font == Font_ASCII_2412 ){
			
				chr=chr-' ';//�õ�ƫ�ƺ��ֵ	
				SizeX = 12;
				SizeY = 24;
				tPointer = (const TU8*)(&oled_asc2_2412);
		}
		else if( Font == Font_ASCII_3216 ){
			
				chr=chr-' ';//�õ�ƫ�ƺ��ֵ	
				SizeX = 16;
				SizeY = 32;
				tPointer = (const TU8*)(&oled_asc2_3216);
			
		}
		else if( Font == Font_DFW_1612 ){
				if( (chr >='0') && (chr <='9'))
						chr = chr-'0'+1;
				else
						chr = 0;
				SizeX = 12;
				SizeY = 16;
				tPointer = (const TU8*)(&oled_DFW_1612);
		}
		else if( Font == Font_DFW_2016 ){
				if( (chr >='0') && (chr <='9'))
						chr = chr-'0'+1;
				else
						chr = 0;
				SizeX = 16;
				SizeY = 20;
				tPointer = (const TU8*)(&oled_DFW_2016);
		}
		else if( Font == Font_DFW_2620 ){
				if( (chr >='0') && (chr <='9'))
						chr = chr-'0'+1;
				else
						chr = 0;
				
				SizeX = 20;
				SizeY = 26;
				tPointer = (const TU8*)(&oled_DFW_2620);
		}
		else if( Font == Font_DFW_3024 ){
				if( (chr >='0') && (chr <='9'))
						chr = chr-'0'+1;
				else
					 chr = 0;
				
				SizeX = 24;
				SizeY = 30;
				tPointer = (const TU8*)(&oled_DFW_3024);
		}
		else{
				return;
		}
		tPointer += SizeX*chr*((SizeY+7)/8);
	//	y0=y,x0
		for(t=0;t<SizeY/8;t++){//8��   
				for(t1=0;t1<SizeX;t1++){
						temp = *tPointer;
						tPointer++;
						for(t2=0;t2<8;t2++){
								if(temp&0x80)Matrix_DrawPiont(x+t1,y+t2,(Matrix_t*)&Matrix_OLED_GRAM,mode);
								else Matrix_DrawPiont(x+t1,y+t2,(Matrix_t*)&Matrix_OLED_GRAM,!mode);
								
								temp<<=1;
						}  	 
				} 
				y+=8;
		}   
		if( SizeY % 8 ){
				for(t1=0;t1<SizeX;t1++)
				{
						temp = *tPointer;
						tPointer++;
						for(t2=0;t2<SizeY%8;t2++)
						{
							if(temp&0x80)Matrix_DrawPiont(x+t1,y+t2,(Matrix_t*)&Matrix_OLED_GRAM,mode);
							else Matrix_DrawPiont(x+t1,y+t2,(Matrix_t*)&Matrix_OLED_GRAM,!mode);
							
							temp<<=1;
						}  	 
				} 
		}
}
/**
  * @brief 
  * @param[in]  
  * @param[in]
  * @retval void
	* @ChangeData 2018-12-30-19:25
	* @History 	
  */
void xOLED_ShowString(TU16 x,TU16 y,FontType_t Font,TU8 mode,TU8 *p){

		TU16 _MAX_CHAR_POSX = 0;
		
		TU16 SizeX = 0,SizeY = 0;
		if( Font == Font_ASCII_0806 ){
				SizeX = 6;
				SizeY = 8;
		}
		else if( Font == Font_ASCII_1206 ){
				SizeX = 6;
				SizeY = 12;
		}
		else if( Font == Font_ASCII_1608 ){
				SizeX = 8;
				SizeY = 16;
		}
		else if( Font == Font_ASCII_2412 ){
				SizeX = 12;
				SizeY = 24;
		}
		else if( Font == Font_ASCII_3216 ){
				SizeX = 16;
				SizeY = 32;	
		}
		else if( Font == Font_DFW_1612 ){
				SizeX = 12;
				SizeY = 16;
		}
		else if( Font == Font_DFW_2016 ){
				SizeX = 16;
				SizeY = 20;
		}
		else if( Font == Font_DFW_2620 ){
				SizeX = 20;
				SizeY = 26;
		}
		else if( Font == Font_DFW_3024 ){
				SizeX = 24;
				SizeY = 20;
		}
		else{
				return;
		}
		_MAX_CHAR_POSX = GDRAM_XSize-SizeX; 
		
		while(*p!='\0'){
		       
				if(x>_MAX_CHAR_POSX){x=0;y+=SizeY;}
				if(y>_MAX_CHAR_POSX){y=x=0;}//OLED_Clear();
				
				if( *p == '\n'){
						x=0;
						y+=SizeY;
				}
				else if(*p == '\t'){
						xOLED_ShowChar(x,y,' ',Font,mode);	 
						x +=SizeX; 
						xOLED_ShowChar(x,y,' ',Font,mode);	 
						x +=SizeX;
						xOLED_ShowChar(x,y,' ',Font,mode);	 
						x +=SizeX;
						xOLED_ShowChar(x,y,' ',Font,mode);	 
						x +=SizeX;
				}
				else if((*p != '\r')||(*p != '\n')){
						xOLED_ShowChar(x,y,*p,Font,mode);	 
						x+=SizeX;
				} 
				p++;
		}  
}   

/**
  * @brief 
  * @param[in]  
  * @param[in]
  * @retval void
	* @ChangeData 2018-12-30-19:25
	* @History 	
  */
TU8 _ttStr[128] = {0};
void xOLED_printf(TU16 x, TU16 y,FontType_t Font,TU8 mode, T8* Data, ...){
		
		va_list ap;
		va_start(ap,Data);
		vsprintf((char*)_ttStr,Data,ap);
		va_end( ap );
		//	Size = strlen( (const TS8 *)tStr );
		GRAMBusy = 1;//GRAM����æ

		xOLED_ShowString(x,y,Font,mode,_ttStr);
		GRAMBusy = 0;
}



/**
  * @brief 
  * @param[in]  Offset_X GDRAM��OLED��ʾ��Ļ��X��ƫ��
  * @param[in]	Offset_Y GDRAM��OLED��ʾ��Ļ��Y��ƫ��
  * @retval void
	* @ChangeData 2018-12-31
	* @History 	
  */
void xOLED_Refresh_Gram( TU16 Offset_X, TU16 Offset_Y ){
	
		TU8 i = 0, n = 0;
		TU16 tv1,tv2;
		TU16 PageInt = 0;
		TU16 PageRem = 0;
		TU16 NPageRem = 0;
		volatile TU8  PageChar = 0;
		
		PageInt = Offset_Y/8;
		PageRem = Offset_Y%8;
		NPageRem = 8-PageRem;
#ifdef SH1106
    if( !GRAMBusy ){
        
				for(i=0;i<xOLED_YPageSize;i++,PageInt++){  
						tv1 = (0+Offset_X)+PageInt*GDRAM_XSize;
						tv2 = tv1+GDRAM_XSize;
//						tv2 = (0+Offset_X)+(PageInt+1)*GDRAM_XSize;
						xOLED_WR_Byte (0xb0+i,OLED_CMD);    //����ҳ��ַ��0~7��
            xOLED_WR_Byte (0x10,OLED_CMD);      //������ʾλ�á��иߵ�ַ 
            xOLED_WR_Byte (0x00+2,OLED_CMD);      //������ʾλ�á��е͵�ַ
          
            xOLED_Itf_WaitTransFinish();//�ȴ���һ�δ���������������׳�������
            xOLED_Itf_DC_Set();  
						for(n=0;n<xOLED_XPosSize;n++,tv1++,tv2++){	
								if( !PageRem ){
										PageChar = *(xOLED_GDRAM+tv1);
								}
								else{									
										PageChar = __CombineChar__(*(xOLED_GDRAM+tv1),*(xOLED_GDRAM+tv2),PageRem,NPageRem);	
								}																	
								xOLED_Itf_WriteBytes((TU8*)&PageChar,1);
						}
				}
				xOLED_Itf_DC_Clr(); 
		}
#else
		if( !GRAMBusy ){
				//Setup column start and end address
				xOLED_WR_Byte (0x21,OLED_CMD);    	//
				xOLED_WR_Byte (0x00,OLED_CMD);      //
				xOLED_WR_Byte (xOLED_XPosIdMax, OLED_CMD);      // 
				//Setup page start and end address
				xOLED_WR_Byte (0x22,OLED_CMD);    	//
				xOLED_WR_Byte (0x00,OLED_CMD);      //
				xOLED_WR_Byte (0x07,OLED_CMD);      // 
      
				xOLED_Itf_WaitTransFinish();//�ȴ���һ�δ���������������׳�������
				xOLED_Itf_DC_Set();
				for(i=0;i<xOLED_YPageSize;i++,PageInt++){  
						tv1 = (0+Offset_X)+PageInt*GDRAM_XSize;
						tv2 = tv1+GDRAM_XSize;
//						tv2 = (0+Offset_X)+(PageInt+1)*GDRAM_XSize;
						
						for(n=0;n<xOLED_XPosSize;n++,tv1++,tv2++){	
								if( !PageRem ){
										PageChar = *(xOLED_GDRAM+tv1);
								}
								else{									
										PageChar = __CombineChar__(*(xOLED_GDRAM+tv1),*(xOLED_GDRAM+tv2),PageRem,NPageRem);	
								}																	
								xOLED_Itf_WriteBytes((TU8*)&PageChar,1);
						}
				}
				xOLED_Itf_DC_Clr(); 
		}
#endif
}
/**
  * @brief 
  * @param[in]  Offset_X GDRAM��OLED��ʾ��Ļ��X��ƫ��
  * @param[in]	Offset_Y GDRAM��OLED��ʾ��Ļ��Y��ƫ��
  * @param[in]	Obs_X 		OLED��ʾ��Ļ ������ʼxλ��  	0-xOLED_XPosIdMax
  * @param[in]	Obs_Page 	OLED��ʾ��Ļ ������ʼPageλ�� 0-xOLED_XPageIdMax
  * @param[in]	XSize 		OLED��ʾ��Ļ ����X��� 				1-xOLED_XPosSize
  * @param[in]	PageSize 	OLED��ʾ��Ļ ����PAGE��С 		1-xOLED_XPageSize
  * @retval void
	* @ChangeData 2018-12-31
	* @History 	
  */
void xOLED_Refresh_Gram_Part( TU16 Offset_X, TU16 Offset_Y, TU16 Obs_X, TU8 Obs_Page, TU16 XSize, TU8 PageSize ){
	
		TU8 i = 0, n = 0;
		TU16 tv1,tv2;
		TU16 PageInt = 0;
		TU16 PageRem = 0;
		TU16 NPageRem = 0;
		volatile TU8  PageChar = 0;
		
		PageInt = Offset_Y/8;
		PageRem = Offset_Y%8;
		NPageRem = 8-PageRem;
  
#ifdef SH1106
    if( !GRAMBusy ){
				if( (Obs_X+XSize)>xOLED_XPosIdMax ){
						XSize = xOLED_XPosIdMax-Obs_X;
				}
				
				for(i=Obs_Page;i<Obs_Page+PageSize;i++,PageInt++){  
						tv1 = (Obs_X+Offset_X)+(PageInt+Obs_Page)*GDRAM_XSize;
						tv2 = tv1+GDRAM_XSize;
//						tv2 = (0+Offset_X)+(PageInt+1)*GDRAM_XSize;
            xOLED_WR_Byte(0xb0+PageInt,OLED_CMD);//����ҳ��ַ��0~7��
            xOLED_WR_Byte((((Obs_X+2)&0xf0)>>4)|0x10,OLED_CMD);
            xOLED_WR_Byte(((Obs_X+2)&0x0f),OLED_CMD); 
            xOLED_Itf_WaitTransFinish();//�ȴ���һ�δ���������������׳�������
            xOLED_Itf_DC_Set();

						for(n=0;n<XSize;n++,tv1++,tv2++){	
								if( !PageRem ){
										PageChar = *(xOLED_GDRAM+tv1);
								}
								else{									
										PageChar = __CombineChar__(*(xOLED_GDRAM+tv1),*(xOLED_GDRAM+tv2),PageRem,NPageRem);	
								}																	
								xOLED_Itf_WriteBytes((TU8*)&PageChar,1);
						}
				}
		}	
#else   
		if( !GRAMBusy ){
				if( (Obs_X+XSize)>xOLED_XPosIdMax ){
						XSize = xOLED_XPosIdMax-Obs_X;
				}
				//Setup column start and end address
				xOLED_WR_Byte (0x21,OLED_CMD);    	//
				xOLED_WR_Byte (Obs_X,OLED_CMD);      //
				xOLED_WR_Byte (Obs_X+XSize-1,OLED_CMD);      // 
				//Setup page start and end address
				xOLED_WR_Byte (0x22,OLED_CMD);    	//
				xOLED_WR_Byte (Obs_Page,OLED_CMD);      //
				xOLED_WR_Byte (Obs_Page+PageSize-1,OLED_CMD);      // 
				xOLED_Itf_WaitTransFinish();//�ȴ���һ�δ���������������׳�������
				xOLED_Itf_DC_Set();
				for(i=Obs_Page;i<Obs_Page+PageSize;i++,PageInt++){  
						tv1 = (Obs_X+Offset_X)+(PageInt+Obs_Page)*GDRAM_XSize;
						tv2 = tv1+GDRAM_XSize;
//						tv2 = (0+Offset_X)+(PageInt+1)*GDRAM_XSize;
						
						for(n=0;n<XSize;n++,tv1++,tv2++){	
								if( !PageRem ){
										PageChar = *(xOLED_GDRAM+tv1);
								}
								else{									
										PageChar = __CombineChar__(*(xOLED_GDRAM+tv1),*(xOLED_GDRAM+tv2),PageRem,NPageRem);	
								}																	
								xOLED_Itf_WriteBytes((TU8*)&PageChar,1);
						}
				}
		}
#endif
}
/**
  * @brief 
  * @param[in]  
  * @param[in]
  * @retval void
	* @ChangeData 2018-12-30-19:25
	* @History 	
  */
void xOLED_Clear( TU8 vValue ){
	
		GRAMBusy = 1;
		if( vValue ){
				memset((char*)xOLED_GDRAM,0xff,GDRAM_XSize*(GDRAM_YSize/8+1));
		}
		else{
				memset((char*)xOLED_GDRAM,0,GDRAM_XSize*(GDRAM_YSize/8+1));
		}		
		GRAMBusy = 0;
}

/**
  * @brief 
  * @param[in]  
  * @param[in]
  * @retval void
	* @ChangeData 2018-12-30-19:25
	* @History 	
  */
void xOLED_WR_Byte(TU8 dat,TU8 cmd){			

	if( cmd ){// 1 Data
		xOLED_Itf_DC_Set();
	}
	else {// 0 CMD
		xOLED_Itf_DC_Clr();	
	}
	xOLED_Itf_WriteBytes(&dat,1);  	  
} 

	  	  
//����OLED��ʾ    
void OLED_Display_On( void ){

		xOLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC����
		xOLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
		xOLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}
//�ر�OLED��ʾ     
void OLED_Display_Off( void ){

		xOLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC����
		xOLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
		xOLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}


//m^n����
TU32 oled_pow(TU8 m,TU8 n)
{
	TU32 result=1;	 
	while(n--)result*=m;    
	return result;
}				  
//��ʼ��SSD1306					    
void xOLED_Init(void)
{ 	

	xOLED_Itf_HadwareInit();
	
	OLED0_ON();
	OLED1_ON();
  
	xOLED_Itf_DC_Set(); 
	xOLED_Itf_RST_Clr();
	xOLED_Delay_ms(100);
	xOLED_Itf_RST_Set(); 
	
	
	
 /*
	The display clock (DCLK) for the Display Timing Generator is derived from CLK. The division factor ��D��
	can be programmed from 1 to 16 by command D5h
	DCLK = FOSC / D
	The frame frequency of display is determined by the following formula.
	
	FRM = Fosc/(D*K*(No. of Mux))
	
 D stands for clock divide ratio. It is set by command D5h A[3:0]. The divide ratio has the range from 1 to
	16.
  K is the number of display clocks per row. The value is derived by
	K = Phase 1 period + Phase 2 period + BANK0 pulse width
		= 2 + 2 + 50 = 54 at power on reset
	(Please refer to Section 8.6 ��Segment Drivers / Common Drivers�� for the details of the ��Phase��)
  Number of multiplex ratio is set by command A8h. The power on reset value is 63 (i.e. 64MUX).
  FOSC is the oscillator frequency. It can be changed by command D5h A[7:4]. The higher the register
			setting results in higher frequency.
 */
 #ifdef SH1106

	xOLED_WR_Byte(0xAE,OLED_CMD);//--turn off oled panel
	xOLED_WR_Byte(0x00,OLED_CMD);//---set low column address
	xOLED_WR_Byte(0x10,OLED_CMD);//---set high column address
	xOLED_WR_Byte(0x40,OLED_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	xOLED_WR_Byte(0x81,OLED_CMD);//--set contrast control register
	xOLED_WR_Byte(0xCF,OLED_CMD); // Set SEG Output Current Brightness
	xOLED_WR_Byte(0xA1,OLED_CMD);//--Set SEG/Column Mapping     0xa0���ҷ��� 0xa1����
	xOLED_WR_Byte(0xC8,OLED_CMD);//Set COM/Row Scan Direction   0xc0���·��� 0xc8����
	xOLED_WR_Byte(0xA6,OLED_CMD);//--set normal display
	xOLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	xOLED_WR_Byte(0x3f,OLED_CMD);//--1/64 duty
	xOLED_WR_Byte(0xD3,OLED_CMD);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	xOLED_WR_Byte(0x00,OLED_CMD);//-not offset
	xOLED_WR_Byte(0xd5,OLED_CMD);//--set display clock divide ratio/oscillator frequency
	xOLED_WR_Byte(0x80,OLED_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
	xOLED_WR_Byte(0xD9,OLED_CMD);//--set pre-charge period
	xOLED_WR_Byte(0xF1,OLED_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	xOLED_WR_Byte(0xDA,OLED_CMD);//--set com pins hardware configuration
	xOLED_WR_Byte(0x12,OLED_CMD);
	xOLED_WR_Byte(0xDB,OLED_CMD);//--set vcomh
	xOLED_WR_Byte(0x40,OLED_CMD);//Set VCOM Deselect Level
	xOLED_WR_Byte(0x20,OLED_CMD);//-Set Page Addressing Mode (0x00/0x01/0x02)
	xOLED_WR_Byte(0x02,OLED_CMD);//
	xOLED_WR_Byte(0x8D,OLED_CMD);//--set Charge Pump enable/disable
	xOLED_WR_Byte(0x14,OLED_CMD);//--set(0x10) disable
	xOLED_WR_Byte(0xA4,OLED_CMD);// Disable Entire Display On (0xa4/0xa5)
	xOLED_WR_Byte(0xA6,OLED_CMD);// Disable Inverse Display On (0xa6/a7) 
	xOLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel

  xOLED_WR_Byte(0xAF,OLED_CMD); /*display ON*/ 
#else  
	xOLED_WR_Byte(0xAE,OLED_CMD); //�ر���ʾ
	xOLED_WR_Byte(0xD5,OLED_CMD); //����ʱ�ӷ�Ƶ����,��Ƶ��
	xOLED_WR_Byte(0x80,OLED_CMD);   //[3:0],��Ƶ����;[7:4],��Ƶ��
	xOLED_WR_Byte(0xA8,OLED_CMD); //��������·��
	xOLED_WR_Byte(0X3F,OLED_CMD); //Ĭ��0X3F(1/64) 
	xOLED_WR_Byte(0xD3,OLED_CMD); //������ʾƫ��
	xOLED_WR_Byte(0X00,OLED_CMD); //Ĭ��Ϊ0
	

	xOLED_WR_Byte(0x40,OLED_CMD); //������ʾ��ʼ�� [5:0],����.
													    
	xOLED_WR_Byte(0x8D,OLED_CMD); //��ɱ�����
	xOLED_WR_Byte(0x14,OLED_CMD); //bit2������/�ر�
	xOLED_WR_Byte(0x20,OLED_CMD); //�����ڴ��ַģʽ-Horizontal addressing mode
	xOLED_WR_Byte(0x00,OLED_CMD); //[1:0],00->ˮƽ��ַģʽ;01->��ֱ��ַģʽ;10->ҳ��ַģʽ;Ĭ��10;
	xOLED_WR_Byte(0xA1,OLED_CMD); //���ض�������,bit0:0,0->0;1,0->xOLED_XPosIdMax;
	xOLED_WR_Byte(0xC8,OLED_CMD); //����COMɨ�跽��;bit3:0,��ͨģʽ;1,�ض���ģʽ COM[N-1]->COM0;N:����·��
	xOLED_WR_Byte(0xDA,OLED_CMD); //����COMӲ����������
	xOLED_WR_Byte(0x12,OLED_CMD); //[5:4]����
		 
	xOLED_WR_Byte(0x81,OLED_CMD); //�Աȶ�����
	xOLED_WR_Byte(0x3F,OLED_CMD); //1~255;Ĭ��0X7F (��������,Խ��Խ��)
	xOLED_WR_Byte(0xD9,OLED_CMD); //����Ԥ�������
	xOLED_WR_Byte(0xf1,OLED_CMD); //[3:0],PHASE 1;[7:4],PHASE 2;
	xOLED_WR_Byte(0xDB,OLED_CMD); //����VCOMH ��ѹ����
	xOLED_WR_Byte(0x30,OLED_CMD); //[6:4] 000,0.65*vcc;001,0.77*vcc;011,0.83*vcc;

	xOLED_WR_Byte(0xA4,OLED_CMD); //ȫ����ʾ����;bit0:1,����;0,�ر�;(����/����)
	xOLED_WR_Byte(0xA6,OLED_CMD); //������ʾ��ʽ;bit0:1,������ʾ;0,������ʾ	    						   
	xOLED_WR_Byte(0xAF,OLED_CMD); //������ʾ	 
#endif
	xOLED_Clear(0);
	
	OLED0_ON();
	OLED1_OFF();
	
}  

void xOLED_RefreshInit( void ){
	

 }


/*****************************
   �������ÿһ���ֽڽ���λ��ת
   ����ת���ch2�����ֵ��ch1
******************************/
void convert_spe_array(TU8 *ch1,TU8 *ch2,TS32 length)
{
	TS32 i=0;
	for(i=0;i<length;i++)
	{
		ch1[i] = ch2[i]^0xff;	
	}
}





#if(0)
/********************************
  ��ʾһ��12*12�ĺ���
  mode  0->������ʾ  
        1->������ʾ
**********************************/

void OLED_Display_Chinese_12_12(TU8 x,TU8 y,TU8 ch[],TU8 mode)
{
	TU8 temp_x,tepm_y;
	TU8 i ,j ,k ,l;
	TU8 num_index = 0;
	
	temp_x = x;
	tepm_y = y;
	for(i=0;i<num_12_12;i++)
	{
		if(GB12_12Chinese[i].Index[0] == ch[0] && 
			 GB12_12Chinese[i].Index[1] == ch[1])//ɸѡ��������
		{
			for(j=0;j<12;j++)//��ʾ��������
			{

					for(l=0;l<8;l++)//��ʾ��һ���ֽ�
					{
						if((GB12_12Chinese[i].Msk[num_index]<<l)&0x80)
						OLED_DrawPoint(temp_x,tepm_y,mode);
						else
						OLED_DrawPoint(temp_x,tepm_y,!mode);		
						temp_x++;
					}
					num_index++;//�ֽ�λ�ü�1
				  for(l=0;l<4;l++)//��ʾ�ڶ����ֽ�
					{
						if((GB12_12Chinese[i].Msk[num_index]<<l)&0x80)
						OLED_DrawPoint(temp_x,tepm_y,mode);
						else
						OLED_DrawPoint(temp_x,tepm_y,!mode);		
						temp_x++;
					}
					num_index++;//�ֽ�λ�ü�1
				temp_x=x;
				tepm_y++;	
			}
			return ;
		}
	}	
}

/********************************
  ��ʾһ��16*16�ĺ���
  mode  0->������ʾ  
        1->������ʾ
**********************************/

void OLED_Display_Chinese_16_16(TU8 x,TU8 y,TU8 ch[],TU8 mode)
{
	TU8 temp_x,tepm_y;
	TU8 i ,j ,k ,l;
	TU8 num_index = 0;
	
	temp_x = x;
	tepm_y = y;
	for(i=0;i<num_16_16;i++)
	{
		if(GB16_16_Chinese[i].Index[0] == ch[0] && 
			 GB16_16_Chinese[i].Index[1] == ch[1])//ɸѡ��������
		{
			for(j=0;j<16;j++)//��ʾ��������
			{
				for(k=0;k<2;k++)//��ʾ��һ��
				{
					for(l=0;l<8;l++)//��ʾһ���ֽ�
					{
						if((GB16_16_Chinese[i].Msk[num_index]<<l)&0x80)
						OLED_DrawPoint(temp_x,tepm_y,mode);
						else
						OLED_DrawPoint(temp_x,tepm_y,!mode);		
						temp_x++;
					}
					num_index++;//�ֽ�λ�ü�1
				}
				temp_x=x;
				tepm_y++;	
			}
			return ;
		}
	}	
}

/********************************
  ��ʾһ��32*32�ĺ���
  mode  0->������ʾ  
        1->������ʾ
**********************************/

void OLED_Display_Chinese_32_32(TU8 x,TU8 y,TU8 ch[],TU8 mode)
{
	TU8 temp_x,tepm_y;
	TU8 i ,j ,k ,l;
	TU8 num_index = 0;
	
	temp_x = x;
	tepm_y = y;
	for(i=0;i<num_32_32;i++)
	{
		if(GB32_32_Chinese[i].Index[0] == ch[0] && 
			 GB32_32_Chinese[i].Index[1] == ch[1])//ɸѡ��������
		{
			for(j=0;j<32;j++)//��ʾ��������
			{
				for(k=0;k<4;k++)//��ʾ��һ��
				{
					for(l=0;l<8;l++)//��ʾһ���ֽ�
					{
						if((GB32_32_Chinese[i].Msk[num_index]<<l)&0x80)
						OLED_DrawPoint(temp_x,tepm_y,mode);
						else
						OLED_DrawPoint(temp_x,tepm_y,!mode);		
						temp_x++;
					}
					num_index++;//�ֽ�λ�ü�1
				}
				temp_x=x;
				tepm_y++;	
			}
			return ;
		}
	}	
}

void OLED_ShowChar_3216(TU8 x,TU8 y,TU8 chr,TU8 mode)
{
	TU8 temp_x,tepm_y;
	TU8 i=0,j ,k ,l;
	TU8 num_index = chr-' ';
  TU8 temp = 0;
	temp = oled_asc2_3216[num_index][i];
	
	temp_x = x;
	tepm_y = y;
	
	
	for(i=0;i<64;i++)
	{
		for(j=0;j<2;j++)
		{
				for(l=0;l<8;l++)//��ʾһ���ֽ�
				{
						if((oled_asc2_3216[num_index][i]>>l) & 0x80)
						OLED_DrawPoint(temp_x,tepm_y,mode);
						else
						OLED_DrawPoint(temp_x,tepm_y,!mode);		
						temp_x++;
				}
				i++;	
				
		}
		temp_x=x;
		tepm_y++;	
		
	}
}







/********************************
  ��ʾ����Ӣ���ַ���
**********************************/
void DisplayChineseEnglish(TU8 x,TU8 y,TU8 * ch_en,TU8 size,TU8 mode)

{
	TU8 temp_index ,temp_x ,temp_y ;
	TU8 temp_font_dis[32] = {0};
	temp_index = 0;
	temp_x = x;
	temp_y = y;
	while(ch_en[temp_index] != '\0')
	{
	 if(ch_en[temp_index]<128)//Ϊ��ĸ����
	 {
		 
		 if(size == 12)//�����С
		 {
			 OLED_ShowChar_Flash(temp_x,temp_y,ch_en[temp_index],12,mode);
			 temp_index++;
			 temp_x+=6;
			 if(temp_x>xOLED_XPosIdMax)
			 {
				 temp_x=0;
				 temp_y+=12;
			 }
			 
		 }
		 else if(size == 16)//�����С
		 {
			 OLED_ShowChar_Flash(temp_x,temp_y,ch_en[temp_index],16,mode);
			 temp_index++;
			 temp_x+=8;
			 if(temp_x>xOLED_XPosIdMax)
			 {
				 temp_x=0;
				 temp_y+=16;
			 }
			}
		else if(size == 32)//�����С	
		{



		}			
	 }
	 else//Ϊ����
	 {
	 
				Read_font_form_flash(&ch_en[temp_index],temp_font_dis,size,FONT_GBK);
				OLED_Display_Chinese(temp_x,temp_y,temp_font_dis,size,mode);
				temp_index+=2;
				temp_x+=size;
				if(temp_x>xOLED_XPosIdMax)
				{
					temp_x=0;
					temp_y+=size;
				} 		
	 }
 }
}
/********************************
  ��ʾ����Ӣ���ַ���
**********************************/
void DisplayChineseEnglish_No_Change_Line(TU8 x,TU8 y,TU8 * ch_en,TU8 size,TU8 mode)

{
	TU8 temp_index ,temp_x ,temp_y ;
	TU8 temp_font_dis[32] = {0};
	temp_index = 0;
	temp_x = x;
	temp_y = y;
	while(ch_en[temp_index] != '\0')
	{
	 if(ch_en[temp_index]<128)//Ϊ��ĸ����
	 {
		 
		 if(size == 12)//�����С
		 {
			 OLED_ShowChar_Flash(temp_x,temp_y,ch_en[temp_index],12,mode);
			 temp_index++;
			 if(temp_x>=xOLED_XPosIdMax)
			 {
				 return;//��ֹ����
			 }
			 temp_x+=6;
			 
		 }
		 else if(size == 16)//�����С
		 {
			 OLED_ShowChar_Flash(temp_x,temp_y,ch_en[temp_index],16,mode);
			 temp_index++;
			 
			 if(temp_x>=xOLED_XPosIdMax)
			 {
				 return;//��ֹ����
			 }
			 temp_x+=8;
			}
		else if(size == 32)//�����С	
		{



		}			
	 }
	 else//Ϊ����
	 {
	 
				Read_font_form_flash(&ch_en[temp_index],temp_font_dis,size,FONT_GBK);
				OLED_Display_Chinese(temp_x,temp_y,temp_font_dis,size,mode);
				temp_index+=2;
				
				if(temp_x>=xOLED_XPosIdMax)
				{
					return;//��ֹ����
				}
				temp_x+=size;		
	 }
 }
}





void Read_font_form_flash(TU8 font[],TU8 data_read[] , TU8 size ,TU8 FONT_NAME)
{
	TU32 addr  = 0;
/*	
	#define FONT_GBK      1
#define FONT_Unicode  2
	*/
	if(FONT_NAME == FONT_GBK)
	{
				if(font[1]<0x7F)
				{
					addr = ((font[0]-0x81)*190+font[1]-0X40)*(size*2);
				}else
				{
					addr = ((font[0]-0x81)*190+font[1]-0X41)*(size*2);
				}

				if(size == 12)
				SPI_Flash_Read( data_read ,font_12_12_st_add+addr,size*2);
				else if(size == 16)
				SPI_Flash_Read( data_read ,font_16_16_st_add+addr,size*2);
	}
	else if(FONT_NAME == FONT_Unicode)
	{
		   addr = (font[0]+(font[1]-0x4E)*256)*(size*2);
		   if(size == 12)
			 SPI_Flash_Read( data_read ,unicode_12_12_st_add+addr,size*2);
			 else if(size == 16)
			 SPI_Flash_Read( data_read ,unicode_16_16_st_add+addr,size*2);
	}
}




void OLED_Display_Chinese(TU8 x,TU8 y,TU8 ch[],TU8 size ,TU8 mode)
{
	TU8 temp_x,tepm_y;
	TU8 i ,j ,k ,l;
	TU8 num_index = 0;
	
	temp_x = x;
	tepm_y = y;	
		
			for(j=0;j<size;j++)//��ʾ��������
			{

					for(l=0;l<8;l++)//��ʾ��һ���ֽ�
					{
						if((ch[num_index]<<l)&0x80)
						OLED_DrawPoint(temp_x,tepm_y,mode);
						else
						OLED_DrawPoint(temp_x,tepm_y,!mode);		
						temp_x++;
					}
					num_index++;//�ֽ�λ�ü�1
					
				  for(l=0;l<size-8;l++)//��ʾ�ڶ����ֽ�
					{
						if((ch[num_index]<<l)&0x80)
						OLED_DrawPoint(temp_x,tepm_y,mode);
						else
						OLED_DrawPoint(temp_x,tepm_y,!mode);		
						temp_x++;
					}
					num_index++;//�ֽ�λ�ü�1
				temp_x=x;
				tepm_y++;	
			}
			return ;
}


//��ָ��λ����ʾһ���ַ�,���������ַ�
//x:0~xOLED_XPosIdMax
//y:0~63
//mode:0,������ʾ;1,������ʾ				 
//size:ѡ������ 16/12 
void OLED_ShowChar_Flash(TU8 x,TU8 y,TU8 chr,TU8 size,TU8 mode)
{      			    
	TU8 temp,t,t1;
	TU8 y0=y;
	TU8 temp_font[17] = {0};
	chr=chr-' ';//�õ�ƫ�ƺ��ֵ	
  

  if(size == 12)
	{
			SPI_Flash_Read( temp_font ,char_12_12_st_add+chr*12,12);
	}
	else if(size == 16)
	{
			SPI_Flash_Read( temp_font ,char_16_16_st_add+chr*size,16);
	}
    for(t=0;t<size;t++)
    {                            
			for(t1=0;t1<8;t1++)
			{
				if(temp_font[t]&0x80)OLED_DrawPoint(x,y,mode);
				else OLED_DrawPoint(x,y,!mode);

				temp_font[t]<<=1;
				y++;
				if((y-y0)==size)
				{
					y=y0;
					x++;
					break;
				}
			}  	 
		}          
}

void store_ASCII(TU8 size)
{
	TU32 i=0 , j=0 ,k=0;

	for(i=0;i<95;i++)
	{
		for(j=0;j<size;j++)
		{
			delay_ms(10);
			if(size == 12)
			{
			SPI_Flash_Write(&oled_asc2_1206[i][j],char_12_12_st_add+k++,1);
			}
			else if(size == 16)
			{
				SPI_Flash_Write(&oled_asc2_1608[i][j],char_16_16_st_add+k++,1);
			}
		}
	}

}
void Display_chinese_unicode(TU8 x,TU8 y,TU8 * ch_en,TU8 size,TU8 mode,TU8 length)
{
	TU8 temp_index ,temp_x ,temp_y ,LENTH = 0;
	TU8 temp_font_dis[32] = {0};
	temp_index = 0;
	temp_x = x;
	temp_y = y;

	for(temp_index = 0;temp_index < length;temp_index+=2)
	{ 
       if(ch_en[temp_index+1] != 0x00)
			 {
				Read_font_form_flash(&ch_en[temp_index],temp_font_dis,size,FONT_Unicode);
				OLED_Display_Chinese(temp_x,temp_y,temp_font_dis,size,mode);
//				temp_index+=2;
				temp_x+=size;
				if(temp_x>=xOLED_XPosIdMax)
				{
					temp_x = 0;
					temp_y+=size;
				}
				
			}
			else//ΪӢ����ĸ
				{
					 OLED_ShowChar_Flash( temp_x,temp_y,ch_en[temp_index],size,mode);
					 temp_x+=size/2;
					 if(temp_x>=xOLED_XPosIdMax)
						{		
					    temp_x = 0;
					    temp_y+=size;
						}
			  }	
	 
  }
	
}
void Display_chinese_unicode_No_Change_Line(TU8 x,TU8 y,TU8 * ch_en,TU8 size,TU8 mode,TU8 length)
{
	TU8 temp_index ,temp_x ,temp_y ,LENTH = 0;
	TU8 temp_font_dis[32] = {0};
	temp_index = 0;
	temp_x = x;
	temp_y = y;

	for(temp_index = 0;temp_index < length;temp_index+=2)
	{ 
       if(ch_en[temp_index+1] != 0x00)
			 {
				Read_font_form_flash(&ch_en[temp_index],temp_font_dis,size,FONT_Unicode);
				OLED_Display_Chinese(temp_x,temp_y,temp_font_dis,size,mode);		
				if(temp_x>=xOLED_XPosIdMax)
				{
					return;//�����л���
				}
				temp_x+=size;
			 }
			else//ΪӢ����ĸ
				{
					 OLED_ShowChar_Flash( temp_x,temp_y,ch_en[temp_index],size,mode);					
          if(temp_x>=xOLED_XPosIdMax)
				  {
					 return;
				  }
					temp_x+=size/2;
			  }	
	 
  }
	
}

#endif

