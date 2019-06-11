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

BatteryDiskPointer_t CreateBatteryDisk0(	int CX,int CY,//��ʼλ��
										 int	    Hight,//�뾶
										 int		CrudeSize,//�̶ֿȳ�
										 int		ThinSize,//ϸ�̶ȳ���
										 char		CrudeNum,//�̶ֿ����������ע��ɶ���=�������+1��
										 char		ThinNum,//�̶ֿ����������ע��ɶ���=�������+1��
										 char       GapOut,//ָ�����ص��̶ֿȼ�϶
										 char       GapIn//ָ�����ص��̶ֿȼ�϶
										);
SpeedDiskPointer_t CreateSpeedDisk(	int CX,int CY,//����
									 int	    Radius,//�뾶
									 float		FullAngle,//���νǶ�
									 int		CrudeSize,//�̶ֿȳ�
									 int		ThinSize,//ϸ�̶ȳ���
									 char		CrudeNum,//�̶ֿ����������ע��ɶ���=�������+1��
									 char		ThinNum,//�̶ֿ����������ע��ɶ���=�������+1��
									 char       GapOut,//ָ�����ص��̶ֿȼ�϶
									 char       GapIn//ָ�����ص��̶ֿȼ�϶
										);

void MovSpeedDiskPointer( SpeedDiskPointer_t *pSpeedDiskPointer, float Persent );

void MovBatteryDiskPointer( BatteryDiskPointer_t *pBatteryDiskPointer, float Persent );

















#endif
