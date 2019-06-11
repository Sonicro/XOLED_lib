#ifndef __XOLED_BASEDRAW_H__
#define __XOLED_BASEDRAW_H__

#include "xoled_core.h"
#include "xoled_type.h"


typedef enum
{	
	Quadrant_Empty = 0,
	Quadrant_Full  = 1,
	Quadrant_Start = 2,
	Quadrant_End = 3,
	Quadrant_StartEnd = 4,
}t_Quadrant_Porp;

	
typedef struct {
	TS32 x;
	TS32 y;
}Position_t;


//void Bresenhamline ( TS32 x0,TS32 y0,TS32 x1, TS32 y1,TS32 color );
void xOLED_DrawLine( TS32 x1, TS32 y1, TS32 x2, TS32 y2, TU32 color );
void xOLED_DrawCircle( TS32 xc, TS32 yc, TS32 r, TS32 Edge, TS32 color );
void xOLED_DrawArc( TS32 xc, TS32 yc, TS32 r, TS32 Edge, TS32 color , float StartAngle, float Angle );
void xOLED_FillRectangle(TU32 x, TU32 y, TU32 width, TU32 xSize, TU32 ySize, const unsigned char* pData ,TU16 Color, unsigned char Mode );


Position_t xOLED_PointAnticlockwise(Position_t RoutPoint, Position_t StaticPoint, double Angle);

#endif
