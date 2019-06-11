#ifndef __XOLED_3D_H__
#define __XOLED_3D_H__


#include "stdlib.h"
#include "xoled_type.h"
//////////////////////////////////////////////////////////////////////////////////	 
//代码转自MacroXu <kk20y@yahoo.com.cn>,AVR S65 3D Project
//把原来的绝大部分浮点运算改为整形运算,并将原来的sin,cos函数换为查表法,以提高速度
//优化后,速度提升约12倍	
//ALIENTEK战舰STM32开发板
//3D 代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/10/3
//版本：V1.0		       	

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
  LCD平面 横向 X
  LCD平面 纵向 Y
  LCD平面 法向 Z



*/

#define FLAT_XY		0
#define FLAT_YX		1

#define FLAT_XZ		2
#define FLAT_ZX		3

#define FLAT_YZ		4
#define FLAT_ZY		5

extern const TU8 asc2_1206[95][12];
extern const TU8 asc2_1608[95][16];

//用户和显示屏的视角关系定义	
//这里单位为0.1°  
#define     USRX    0
#define     USRY    0  
#define     USRZ    388   // OFFSETZ*0.707*10,1:1比例显示

//extern TU16 	USRX;
//extern TU16 	USRY;
//extern TU16 	USRZ;
		 
///////////////////////////////////////////////////////////////////////////////////////////////
//描述一个2D像素点  
typedef struct _TYPE_2D_PIXEL{
    TU16    x;
    TU16    y;
		TU16    color;
}type_2d_pixel;
//描述一个3D像素点 
typedef struct _TYPE_3D_PIXEL{
    TS16    x;
    TS16    y;
    TS16    z;
		TU16    color;
}type_3d_pixel;

//描述旋转角度 
//单位0.1°
typedef struct _TYPE_ROTATION_ANGLE{
    TS16   x;
    TS16   y;
	TS16   z; 
}type_rot_ang;

//描述移动位置
typedef struct _TYPE_TRANSLATION_DIST{
    TS16    x;
	TS16    y;
	TS16    z;
}type_tran_dis;

//定义一个3D图形管理器
typedef struct 
{
	type_3d_pixel *p3dbuf;		//3d像素点buf
	type_2d_pixel *p2dbuf; 	  //2d像素点buf
	type_rot_ang  ang;			//角度值
	type_tran_dis dis;	 		//位移值
	TU16 pixsize;						//当前3d点数
	TU16 maxpixsize;				//最大3d像素值
	TS16 offx;					//x方向偏移（相对于LCD平面 横向起始坐标）
	TS16 offy;					//y方向偏移（相对于LCD平面 纵向起始坐标）
	TS16 offz;					//z方向偏移（相对于LCD平面 法向起始坐标）
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
_t3d_obj* t3d_creat(TU16 offsetx,TU16 offsety,TU16 offsetz,TU16 size);//创建3D图形管理器 
void t3d_delete(_t3d_obj* t3d_del);//删除一个3D管理器
void t3d_pixel_transform(_t3d_obj* t3dx,TU16 pixindex);
void t3d_show_char(_t3d_obj *t3dx,TS16 x,TS16 y,TS16 z,TU8 num,TU8 size,TU16 color);
void t3d_show_str(_t3d_obj *t3dx,TS16 x,TS16 y,TS16 z,const TU8 *p,TU8 size,TU16 *ctbl,TU8 mode);
void t2d_draw_point(TU16 x,TU16 y,TU16 color);
void t3d_draw_point(_t3d_obj *t3dx,TU16 pixindex,TS16 x,TS16 y,TS16 z,TU16 color);
 
void t3d_show_obj(TU16 x,TU16 y,TU16 width,TU16 height,_t3d_obj *t3dx,TU16 bkcolor);
void t3d_clear_obj(TU16 x,TU16 y,TU16 width,TU16 height,_t3d_obj *t3dx,TU16 bkcolor);



//画立方体的边框
//t3dx:3D体
//color:线条颜色
void t3dplay_draw_cube_rim(_t3d_obj* t3dx,TU16 color);
//画一个3d立方体
//t3dx:3D体
//color:线条颜色.
//bkcolor:背景颜色.
void t3dplay_draw_cube(_t3d_obj* t3dx,TU16 color,TU16 bkcolor);	 










extern type_2d_pixel    Arry_2d_pixel[];
extern type_2d_matrix   Test_matrix;



unsigned int DrawPic( type_2d_matrix *  matrix, TU8 *Data,TU16 x, TU16 y,TU16 color );
void DrawMatrix( type_2d_matrix *  matrix , _t3d_obj* t3dx, TU8 Flat,int X,int Y,int Z);

   



#endif



























