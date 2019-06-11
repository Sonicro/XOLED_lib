#include "xoled_demo_ddc.h"
#include "xoled_basedraw.h"


#include "string.h"
#include "stdio.h"

const unsigned char LOGO_Right_16_8[] = {
	0x00,0x3C,0x3C,0x3C,0x3C,0x3C,0x3C,0xFF,
	0xFF,0x7E,0x7E,0x3C,0x3C,0x18,0x18,0x00/*"未命名文件",0*/};

const unsigned char LOGO_Left_16_8[] = {
	
	0x00,0x18,0x18,0x3C,0x3C,0x7E,0x7E,0xFF,
	0xFF,0x3C,0x3C,0x3C,0x3C,0x3C,0x3C,0x00/*"未命名文件",0*/
};
const unsigned char LOGO_Light0_8_8[] = {

0x00,0x00,0x00,0xFF,0x81,0x81,0x42,0x3C/*"未命名文件",0*/

};
const unsigned char LOGO_Light1_8_8[] = {

0xAA,0xAA,0x00,0xFF,0x81,0x81,0x42,0x3C/*"未命名文件",0*/
};
const unsigned char LOGO_jiantou_6_5[] = {

0x20,0x20,0x20,0xF8,0x70,0x20/*"未命名文件",0*/
};


const unsigned char LOGO_jiantou_10_7[] = {

0x38,0x38,0x38,0x38,0xFE,0x7C,0x7C,0x38,0x38,0x10/*"未命名文件",0*/
	
};
const unsigned char Sign_sheshidu_16_16[] = { //℃(0)

0x30,0x48,0x48,0x30,0x03,0x0E,0x10,0x20,0x20,0x20,0x20,0x20,0x20,0x10,0x1E,0x00,
0x00,0x00,0x00,0x00,0xF0,0x3C,0x06,0x02,0x01,0x01,0x01,0x01,0x02,0x02,0x04,0x00,/*"℃",0*/
};/*"℃",0*/
const unsigned char Sign_sheshidu_20_20[] = {

0x00,0x38,0x44,0x44,0x38,0x01,0x07,0x0C,0x18,0x30,0x20,0x20,0x20,0x20,0x20,0x10,
0x10,0x0C,0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0xF8,0xFF,0x03,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,
0xC0,0x40,0x60,0x20,0x20,0x20,0x40,0x40,0x80,0x00,0x00,0x00,/*"℃",0*/

};

const unsigned char Sign_sheshidu_26_26[] = {

0x00,0x04,0x0F,0x11,0x11,0x19,0x0E,0x00,0x00,0x03,0x07,0x06,0x0C,0x08,0x08,0x18,
0x18,0x08,0x08,0x08,0x04,0x06,0x03,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x3F,0xFF,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xF8,0x3C,0x0E,0x03,
0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x02,0x06,0x0C,0x10,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x80,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*"℃",0*/
};
const unsigned char Sign_sheshidu_30_30[] = {
 //℃(0)
0x00,0x00,0x0F,0x19,0x10,0x10,0x19,0x0F,0x00,0x00,0x00,0x03,0x07,0x06,0x0C,0x08,
0x08,0x08,0x08,0x08,0x08,0x08,0x04,0x04,0x02,0x01,0x07,0x00,0x00,0x00,0x00,0x00,
0x00,0x80,0x80,0x80,0x80,0x00,0x0F,0x7F,0xFF,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xE0,0xFC,0xFF,0x07,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x01,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xE0,0x60,0x30,0x30,0x30,0x30,0x30,0x20,0x20,
0x60,0x40,0x80,0x80,0x00,0x00,0x00,0x00,/*"℃",0*/
};

const unsigned char Sign_Dot_06_16[] = {

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0C,0x0C,0x00,0x00,0x00,/*".",0*/

};
const unsigned char Sign_Dot_08_20[] = {

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x00,0x00,0x00,0x00,0x00,/*".",0*/

};
const unsigned char Sign_Dot_10_26[] = {

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1C,0x1C,0x1C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*".",0*/

};
const unsigned char Sign_Dot_12_30[] = {

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xC0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,/*".",0*/

};

const unsigned char Chinese_16_16[][32] = {

{0x08,0x30,0x24,0x24,0x25,0x26,0xA4,0x64,0x24,0x24,0x25,0x24,0x24,0x28,0x30,0x00,0x02,0x02,0x12,0x92,0x92,0x92,0x92,0xFE,0x92,0x92,0x92,0xD2,0x12,0x02,0x02,0x00},/*"室",0*/
{0x08,0x06,0x40,0x31,0x00,0x00,0x7F,0x49,0x49,0x49,0x49,0x49,0x7F,0x00,0x00,0x00,0x20,0x20,0x7E,0x80,0x02,0x7E,0x42,0x42,0x7E,0x42,0x7E,0x42,0x42,0x7E,0x02,0x00},/*"温",1*/
{0x01,0x01,0x21,0x21,0x21,0x7F,0x41,0xC1,0x41,0x01,0xFF,0x01,0x01,0x01,0x01,0x00,0x00,0x01,0x02,0x04,0x18,0xE0,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00},/*"升",0*/

};

/*




*/
BatteryDiskPointer_t CreateBatteryDisk0(	int CX,int CY,//起始位置
										 int	    Hight,//半径
										 int		CrudeSize,//粗刻度长
										 int		ThinSize,//细刻度长度
										 char		CrudeNum,//粗刻度区间个数（注意可度数=区间个数+1）
										 char		ThinNum,//粗刻度区间个数（注意可度数=区间个数+1）
										 char       SX,//指针图片起始到CX距离
										 char       SY////指针图片起始到CY距离
										){
	BatteryDiskPointer_t BatteryDiskPointer = {0};
	//Position_t ret1[6],ret2[6],Center,tpoint = {0};
	float fCrudeInterval,fThinInterval,fk;
	unsigned char tStr[5] = {0};
	TU16 CrudeInterval,ThinInterval,k;
	int i=0,j;
	fk = 100/CrudeNum;
	k = (TU16)(fk);
	
	
	fCrudeInterval = (float)Hight/CrudeNum;
	fThinInterval  = (float)Hight/CrudeNum/ThinNum;
	
	CrudeInterval = (TU16)(fCrudeInterval+0.5);
	ThinInterval  = (TU16)(fThinInterval+0.5);
	

	
	for( i=0;i<CrudeNum+1;i++){
		xOLED_DrawLine(CX,CY+i*CrudeInterval,CX+CrudeSize,CY+i*CrudeInterval,1);
//		xOLED_DrawLine(CX,CY+i*CrudeInterval+1,CX+CrudeSize,CY+i*CrudeInterval+1,1);

		memset((char*)tStr,0,sizeof(tStr));
		if( i == 0){
			
			sprintf((char*)tStr,"%d",99);
		}
		else if( i == CrudeNum ){
			sprintf((char*)tStr,"%d",0);
		}
		else{
			sprintf((char*)tStr,"%d",100-k*i);
		}
		xOLED_ShowString(CX+CrudeSize+1,CY+i*CrudeInterval-3,Font_ASCII_0806,1,tStr);

		for( j=1;((j<ThinNum)&&(i<CrudeNum));j++){
//			xOLED_DrawLine(CX+CrudeSize-ThinSize,CY+i*CrudeInterval+j*ThinInterval,CX+CrudeSize,CY+i*CrudeInterval+j*ThinInterval,1);
		
			xOLED_DrawLine(CX,CY+i*CrudeInterval+j*ThinInterval,CX+CrudeSize-ThinSize,CY+i*CrudeInterval+j*ThinInterval,1);
//			xOLED_DrawLine(CX+CrudeInterval-ThinInterval,CY+i*CrudeInterval+j*ThinInterval+1,CX+CrudeSize,CY+i*CrudeInterval+j*ThinInterval+1,1);
		}
		
	}

	
	xOLED_DrawLine(CX+2,CY,CX+2,CY+Hight,1);
	
	BatteryDiskPointer.LastPresent = 0;
	BatteryDiskPointer.Hight = Hight;
	BatteryDiskPointer.StaPointO.x = CX-7;//6
	BatteryDiskPointer.StaPointO.y = CY-2+Hight;//5
	BatteryDiskPointer.PicSize.x = 6;
	BatteryDiskPointer.PicSize.y = 5;
	BatteryDiskPointer.Data = (unsigned char*)LOGO_jiantou_6_5;
	
	BatteryDiskPointer.MovPointO.x = BatteryDiskPointer.StaPointO.x;
	BatteryDiskPointer.MovPointO.y = BatteryDiskPointer.StaPointO.y;
	
	
	xOLED_FillRectangle(	BatteryDiskPointer.MovPointO.x, BatteryDiskPointer.MovPointO.y, 
										BatteryDiskPointer.PicSize.x, 
										BatteryDiskPointer.PicSize.x, BatteryDiskPointer.PicSize.y, 
										BatteryDiskPointer.Data, 1, 1);
	return BatteryDiskPointer;
}
										



SpeedDiskPointer_t CreateSpeedDisk(	int CX,int CY,//中心
									 int	    Radius,//半径
									 float		FullAngle,//扇形角度
									 int		CrudeSize,//粗刻度长
									 int		ThinSize,//细刻度长度
									 char		CrudeNum,//粗刻度区间个数（注意可度数=区间个数+1）
									 char		ThinNum,//粗刻度区间个数（注意可度数=区间个数+1）
									 char       GapOut,//指针外沿到粗刻度间隙
									 char       GapIn//指针内沿到粗刻度间隙
										){
	SpeedDiskPointer_t SpeedDiskPointer = {0};
	Position_t ret1[6],ret2[6],Center,tpoint = {0};
	float CrudeAngle,ThinAngle,BegainAngle;
	int i=0;
//	Posi = {64,64};//圆心
//	Position_t Pointer[6] = {
//	{64,23},
//	{64,33},
//	{62,31},
//	{66,31},
//	},Pointer1[6];
	Center.x = CX;
	Center.y = CY;
	
	ret1[0].x = Center.x-1; ret1[0].y = Center.y-Radius+1;
	ret1[1].x = Center.x;   ret1[1].y = Center.y-Radius+1;
	ret1[2].x = Center.x+1; ret1[2].y = Center.y-Radius+1;
	ret1[3].x = Center.x-1; ret1[3].y = Center.y-Radius+CrudeSize+1;
	ret1[4].x = Center.x;   ret1[4].y = Center.y-Radius+CrudeSize+1;
	ret1[5].x = Center.x+1; ret1[5].y = Center.y-Radius+CrudeSize+1;
	
	/*画粗刻度线*/
{	

	CrudeAngle = FullAngle/CrudeNum;
	ThinAngle = CrudeAngle/ThinNum;
	BegainAngle = 90.0 + FullAngle/2;
{	//获得指针
	SpeedDiskPointer.CenPoint.x = CX;
	SpeedDiskPointer.CenPoint.y = CY;
	SpeedDiskPointer.TotalAngle = FullAngle;
	
	tpoint.x = CX;
	tpoint.y = CY-Radius+CrudeSize+GapOut;//留下5空隙
	SpeedDiskPointer.StaPointO = xOLED_PointAnticlockwise(tpoint,Center,90.0-BegainAngle);
	if( GapIn ){
		tpoint.y = CY-GapIn;
		SpeedDiskPointer.StaPointI = xOLED_PointAnticlockwise(tpoint,Center,90.0-BegainAngle);

	}
	else{
		SpeedDiskPointer.StaPointI.x = CX;
		SpeedDiskPointer.StaPointI.y = CY;	
	}

	
	SpeedDiskPointer.MovPointO.x = SpeedDiskPointer.StaPointO.x;
	SpeedDiskPointer.MovPointO.y = SpeedDiskPointer.StaPointO.y;
	
	SpeedDiskPointer.MovPointI.x = SpeedDiskPointer.StaPointI.x;
	SpeedDiskPointer.MovPointI.y = SpeedDiskPointer.StaPointI.y;
	

}	
	for( i=0;i<CrudeNum+1;i++ ){
		if( BegainAngle-90.0 ){
			ret2[0] = xOLED_PointAnticlockwise(ret1[0],Center,BegainAngle-90.0);//坐标逆时针旋转
			ret2[1] = xOLED_PointAnticlockwise(ret1[1],Center,BegainAngle-90.0);//坐标逆时针旋转
			ret2[2] = xOLED_PointAnticlockwise(ret1[2],Center,BegainAngle-90.0);//坐标逆时针旋转
			ret2[3] = xOLED_PointAnticlockwise(ret1[3],Center,BegainAngle-90.0);//坐标逆时针旋转
			ret2[4] = xOLED_PointAnticlockwise(ret1[4],Center,BegainAngle-90.0);//坐标逆时针旋转
			ret2[5] = xOLED_PointAnticlockwise(ret1[5],Center,BegainAngle-90.0);//坐标逆时针旋转
			xOLED_DrawLine(ret2[0].x,ret2[0].y, ret2[3].x,ret2[3].y,1);
			xOLED_DrawLine(ret2[1].x,ret2[1].y, ret2[4].x,ret2[4].y,1);
			xOLED_DrawLine(ret2[2].x,ret2[2].y, ret2[5].x,ret2[5].y,1);
			xOLED_DrawLine(ret2[0].x,ret2[0].y, ret2[5].x,ret2[5].y,1);
			xOLED_DrawLine(ret2[2].x,ret2[2].y, ret2[3].x,ret2[3].y,1);
		}
		else{
			xOLED_DrawLine(ret1[0].x,ret1[0].y, ret1[3].x,ret1[3].y,1);
			xOLED_DrawLine(ret1[1].x,ret1[1].y, ret1[4].x,ret1[4].y,1);
			xOLED_DrawLine(ret1[2].x,ret1[2].y, ret1[5].x,ret1[5].y,1);
			
		}

		BegainAngle -= CrudeAngle;
//		delay_ms(300);
			
	}
}	

#if(1)
/*画细刻度线*/
{	
	
	ret1[4].y = Center.y-Radius+ThinSize+1;//更改长度
	
	BegainAngle = 90.0 + FullAngle/2;
	for( i=0;i<CrudeNum*ThinNum+1;i++ ){
			ret2[1] = xOLED_PointAnticlockwise(ret1[1],Center,BegainAngle-90.0);//坐标逆时针旋转
			ret2[4] = xOLED_PointAnticlockwise(ret1[4],Center,BegainAngle-90.0);//坐标逆时针旋转
			xOLED_DrawLine(ret2[1].x,ret2[1].y, ret2[4].x,ret2[4].y,1);
			BegainAngle -= ThinAngle;
//			delay_ms(300);
			
	}
	
}
#endif
/*画圆弧*/
{
	if( (FullAngle/2)<=90 ){
		xOLED_DrawArc(Center.x,Center.y,Radius,2,1,90.0-FullAngle/2,FullAngle);		
//		DrawArc(Center.x,Center.y,Radius-CrudeSize-2,0,1,90.0-FullAngle/2,FullAngle);
	}
	else{
		xOLED_DrawArc(Center.x,Center.y,Radius,2,1,360-(FullAngle/2-90.0),FullAngle);
//		DrawArc(Center.x,Center.y,Radius-CrudeSize-2,0,1,360-(FullAngle/2-90.0),FullAngle);
		
		
		
	}
	
	xOLED_DrawLine( SpeedDiskPointer.MovPointI.x,SpeedDiskPointer.MovPointI.y,
			  SpeedDiskPointer.MovPointO.x,SpeedDiskPointer.MovPointO.y,1);
	

}

	return SpeedDiskPointer;
}

void MovSpeedDiskPointer( SpeedDiskPointer_t *pSpeedDiskPointer, float Persent ){
	float tAngle = 0.0;
	if( pSpeedDiskPointer && pSpeedDiskPointer->TotalAngle ){
		
		if( pSpeedDiskPointer->LastPresent != Persent ){
			if( Persent >= 100 )
				Persent = 100;
			if( Persent <=  0 )
				Persent = 0;
			tAngle = Persent*pSpeedDiskPointer->TotalAngle/100;
			

			xOLED_DrawLine(pSpeedDiskPointer->MovPointI.x,pSpeedDiskPointer->MovPointI.y,
					 pSpeedDiskPointer->MovPointO.x,pSpeedDiskPointer->MovPointO.y,0);
	
			if( tAngle ){
				
				pSpeedDiskPointer->MovPointO = xOLED_PointAnticlockwise(pSpeedDiskPointer->StaPointO,pSpeedDiskPointer->CenPoint,tAngle);
				if( ( pSpeedDiskPointer->StaPointI.x == pSpeedDiskPointer->CenPoint.x) &&
				    ( pSpeedDiskPointer->StaPointI.y == pSpeedDiskPointer->CenPoint.y) ){
						
				}
				else{
					pSpeedDiskPointer->MovPointI = xOLED_PointAnticlockwise(pSpeedDiskPointer->StaPointI,pSpeedDiskPointer->CenPoint,tAngle);
					
				}
				
			}
			else{
				pSpeedDiskPointer->MovPointO.x = pSpeedDiskPointer->StaPointO.x;
				pSpeedDiskPointer->MovPointO.y = pSpeedDiskPointer->StaPointO.y;
				
				pSpeedDiskPointer->MovPointI.x = pSpeedDiskPointer->StaPointI.x;
				pSpeedDiskPointer->MovPointI.y = pSpeedDiskPointer->StaPointI.y;

			}

				xOLED_DrawLine( pSpeedDiskPointer->MovPointI.x,pSpeedDiskPointer->MovPointI.y,
						  pSpeedDiskPointer->MovPointO.x,pSpeedDiskPointer->MovPointO.y,1);


			pSpeedDiskPointer->LastPresent = Persent;
		}

	}
}




void MovBatteryDiskPointer( BatteryDiskPointer_t *pBatteryDiskPointer, float Persent ){
	float fInterval = 0.0;
	TU16 Interval = 0;
	
	
	if( pBatteryDiskPointer && pBatteryDiskPointer->Hight ){
		
		if( pBatteryDiskPointer->LastPresent != Persent ){
			if( Persent >= 100 )
				Persent = 100;
			if( Persent <=  0 )
				Persent = 0;
			
			fInterval = Persent*(float)(pBatteryDiskPointer->Hight)/100;
			Interval = (TU16)(fInterval+0.5);
			xOLED_FillRectangle(	pBatteryDiskPointer->MovPointO.x, pBatteryDiskPointer->MovPointO.y, 
								pBatteryDiskPointer->PicSize.x, 
								pBatteryDiskPointer->PicSize.x, pBatteryDiskPointer->PicSize.y, 
								pBatteryDiskPointer->Data, 0, 0);
			

			
			xOLED_FillRectangle(	pBatteryDiskPointer->StaPointO.x, pBatteryDiskPointer->StaPointO.y-Interval, 
								pBatteryDiskPointer->PicSize.x, 
								pBatteryDiskPointer->PicSize.x, pBatteryDiskPointer->PicSize.y, 
								pBatteryDiskPointer->Data, 1, 1);

			
			pBatteryDiskPointer->MovPointO.x = pBatteryDiskPointer->StaPointO.x;
			pBatteryDiskPointer->MovPointO.y = pBatteryDiskPointer->StaPointO.y-Interval;


			pBatteryDiskPointer->LastPresent = Persent;
		}

	}
}


























