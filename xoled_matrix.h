#ifndef __MATRIX_H__
#define __MATRIX_H__

//typedef unsigned int   Ma_unsigned int;
//typedef unsigned short Ma_unsigned short int;
//typedef TU8  Ma_unsigned char;

#include "xoled_type.h"

typedef unsigned int   TU32;
typedef unsigned short TU16;
typedef TU8  TU8;

typedef struct {
	TU16 x0;
	TU16 y0;
	TU16 XSize;
	TU16 YSize;
	TU8  *Buffer;
}Rect_t;



typedef struct {
	TU16 XSize;/*Bit*/
	TU16 YSize;/*Bit*/
	volatile TU8 *GRAM;
}Matrix_t;




//typedef struct _Ma_t{
//	
//	TU32	Status;			/*状态*/
//	Rect_t  		Rectangle;
//	Rect_t  		ValidRect;		/*有效区域*/	
//	
//}Ma_Info_t;

/*窗口定义
	二值   0  1
	▽	▽	
	0D0	1D0...
	0D1	1D1...
	0D2	1D2...
	0D3	1D3...
	0D4	1D4...
	0D5	1D5...
	0D6	1D6...
	0D7	1D7...
	△	△
*/


void Matrix_DrawPiont( TU16 x, TU16 y, Matrix_t *pMatrix, TU8 Value );
TU8 Matrix_ReadPiont( TU16 x, TU16 y, Matrix_t *pMatrix );

void Matrix_ScrollX_1( Matrix_t *pMatrix , TU8 Dir );
void Matrix_ScrollY_1( Matrix_t *pMatrix , TU8 Dir );
void Matrix_Copy( Matrix_t 		*MatrixDes, 
									Matrix_t 		*MatrixSrc ,
									TU16 	Dx0, 
									TU16 	Dy0, 
									TU16 	Sx0, 
									TU16 	Sy0, 
									TU16 	xSize, 
									TU16 	ySize );

#endif
