#ifndef __DDC_H__
#define __DDC_H__

#include "xoled_basedraw.h"



typedef struct {
	float LastPresent;
	float TotalAngle;
	Position_t	MovPointO;
	Position_t	MovPointI;
	Position_t	CenPoint;
	Position_t	StaPointO;
	Position_t	StaPointI;
	
}SpeedDiskPointer_t;

typedef struct {
	float LastPresent;
	int   Hight;
	unsigned char* Data;
	Position_t  PicSize;
	Position_t	MovPointO;
	Position_t	StaPointO;
	
}BatteryDiskPointer_t;
//void CreateSpeedDisk(void);

BatteryDiskPointer_t CreateBatteryDisk0(	int CX,int CY,//起始位置
										 int	    Hight,//半径
										 int		CrudeSize,//粗刻度长
										 int		ThinSize,//细刻度长度
										 char		CrudeNum,//粗刻度区间个数（注意可度数=区间个数+1）
										 char		ThinNum,//粗刻度区间个数（注意可度数=区间个数+1）
										 char       GapOut,//指针外沿到粗刻度间隙
										 char       GapIn//指针内沿到粗刻度间隙
										);
SpeedDiskPointer_t CreateSpeedDisk(	int CX,int CY,//中心
									 int	    Radius,//半径
									 float		FullAngle,//扇形角度
									 int		CrudeSize,//粗刻度长
									 int		ThinSize,//细刻度长度
									 char		CrudeNum,//粗刻度区间个数（注意可度数=区间个数+1）
									 char		ThinNum,//粗刻度区间个数（注意可度数=区间个数+1）
									 char       GapOut,//指针外沿到粗刻度间隙
									 char       GapIn//指针内沿到粗刻度间隙
										);

void MovSpeedDiskPointer( SpeedDiskPointer_t *pSpeedDiskPointer, float Persent );

void MovBatteryDiskPointer( BatteryDiskPointer_t *pBatteryDiskPointer, float Persent );

















#endif
