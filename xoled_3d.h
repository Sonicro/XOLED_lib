#ifndef __XOLED_3D_H__
#define __XOLED_3D_H__


#include "stdlib.h"
#include "xoled_type.h"
//////////////////////////////////////////////////////////////////////////////////	 
//����ת��MacroXu <kk20y@yahoo.com.cn>,AVR S65 3D Project
//��ԭ���ľ��󲿷ָ��������Ϊ��������,����ԭ����sin,cos������Ϊ���,������ٶ�
//�Ż���,�ٶ�����Լ12��	
//ALIENTEKս��STM32������
//3D ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/10/3
//�汾��V1.0		       	

//#ifndef TU8
//	#define TU8 TU8
//#endif

//#ifndef TU16
//	#define TU16 unsigned TS16 int
//#endif

//#ifndef TU32
//	#define TU32 unsigned int
//#endif

//#ifndef TS16
//	#define TS16 TS16 int
//#endif

////////////////////////////////////////////////////////////////////////////////// 	   

/*
  LCDƽ�� ���� X
  LCDƽ�� ���� Y
  LCDƽ�� ���� Z



*/

#define FLAT_XY		0
#define FLAT_YX		1

#define FLAT_XZ		2
#define FLAT_ZX		3

#define FLAT_YZ		4
#define FLAT_ZY		5

extern const TU8 asc2_1206[95][12];
extern const TU8 asc2_1608[95][16];

//�û�����ʾ�����ӽǹ�ϵ����	
//���ﵥλΪ0.1��  
#define     USRX    0
#define     USRY    0  
#define     USRZ    388   // OFFSETZ*0.707*10,1:1������ʾ

//extern TU16 	USRX;
//extern TU16 	USRY;
//extern TU16 	USRZ;
		 
///////////////////////////////////////////////////////////////////////////////////////////////
//����һ��2D���ص�  
typedef struct _TYPE_2D_PIXEL{
    TU16    x;
    TU16    y;
		TU16    color;
}type_2d_pixel;
//����һ��3D���ص� 
typedef struct _TYPE_3D_PIXEL{
    TS16    x;
    TS16    y;
    TS16    z;
		TU16    color;
}type_3d_pixel;

//������ת�Ƕ� 
//��λ0.1��
typedef struct _TYPE_ROTATION_ANGLE{
    TS16   x;
    TS16   y;
	TS16   z; 
}type_rot_ang;

//�����ƶ�λ��
typedef struct _TYPE_TRANSLATION_DIST{
    TS16    x;
	TS16    y;
	TS16    z;
}type_tran_dis;

//����һ��3Dͼ�ι�����
typedef struct 
{
	type_3d_pixel *p3dbuf;		//3d���ص�buf
	type_2d_pixel *p2dbuf; 	  //2d���ص�buf
	type_rot_ang  ang;			//�Ƕ�ֵ
	type_tran_dis dis;	 		//λ��ֵ
	TU16 pixsize;						//��ǰ3d����
	TU16 maxpixsize;				//���3d����ֵ
	TS16 offx;					//x����ƫ�ƣ������LCDƽ�� ������ʼ���꣩
	TS16 offy;					//y����ƫ�ƣ������LCDƽ�� ������ʼ���꣩
	TS16 offz;					//z����ƫ�ƣ������LCDƽ�� ������ʼ���꣩
}_t3d_obj;

typedef struct _TYPE_2D_MATRIX{
    TU16    			  xoffsize;
    TU16    			  yoffsize;
	TU16				  		validindex;
	type_2d_pixel*    p2d_pixel;
}type_2d_matrix;






 TS16 my_sin(TS16 arg);
 TS16 my_cos(TS16 arg);  
T8 xt3d_creat(TU16 offsetx,TU16 offsety,TU16 offsetz,TU16 size,_t3d_obj* t3d_crt,void* p2dbuf,void* p3dbuf);
_t3d_obj* t3d_creat(TU16 offsetx,TU16 offsety,TU16 offsetz,TU16 size);//����3Dͼ�ι����� 
void t3d_delete(_t3d_obj* t3d_del);//ɾ��һ��3D������
void t3d_pixel_transform(_t3d_obj* t3dx,TU16 pixindex);
void t3d_show_char(_t3d_obj *t3dx,TS16 x,TS16 y,TS16 z,TU8 num,TU8 size,TU16 color);
void t3d_show_str(_t3d_obj *t3dx,TS16 x,TS16 y,TS16 z,const TU8 *p,TU8 size,TU16 *ctbl,TU8 mode);
void t2d_draw_point(TU16 x,TU16 y,TU16 color);
void t3d_draw_point(_t3d_obj *t3dx,TU16 pixindex,TS16 x,TS16 y,TS16 z,TU16 color);
 
void t3d_show_obj(TU16 x,TU16 y,TU16 width,TU16 height,_t3d_obj *t3dx,TU16 bkcolor);
void t3d_clear_obj(TU16 x,TU16 y,TU16 width,TU16 height,_t3d_obj *t3dx,TU16 bkcolor);



//��������ı߿�
//t3dx:3D��
//color:������ɫ
void t3dplay_draw_cube_rim(_t3d_obj* t3dx,TU16 color);
//��һ��3d������
//t3dx:3D��
//color:������ɫ.
//bkcolor:������ɫ.
void t3dplay_draw_cube(_t3d_obj* t3dx,TU16 color,TU16 bkcolor);	 










extern type_2d_pixel    Arry_2d_pixel[];
extern type_2d_matrix   Test_matrix;



unsigned int DrawPic( type_2d_matrix *  matrix, TU8 *Data,TU16 x, TU16 y,TU16 color );
void DrawMatrix( type_2d_matrix *  matrix , _t3d_obj* t3dx, TU8 Flat,int X,int Y,int Z);

   



#endif



























