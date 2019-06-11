#include "xoled_basedraw.h"
#include "math.h"

//#include "3d.h"
static void CirclePt(TS32 x0, TS32 y0, TS32 x, TS32 y, TU32 clolor){



       xOLED_DrawPoint ( x+x0, y+y0,clolor);//x,y		/* 270-315 */

       xOLED_DrawPoint ( -x+x0, y+y0,clolor);//-x,y		/* 270-225 */

       xOLED_DrawPoint ( x+x0, -y+y0,clolor);//x, -y		/* 90-45 */

       xOLED_DrawPoint ( -x+x0, -y+y0,clolor);//-x, -y	/* 90-135 */

       xOLED_DrawPoint ( y+x0, x+y0,clolor);//y, x		/* 0-315 */	

       xOLED_DrawPoint ( y+x0, -x+y0,clolor);//y, -x		/* 0-45 */	

       xOLED_DrawPoint ( -y+x0, x+y0,clolor);//-y, x		/* 180-225 */

       xOLED_DrawPoint ( -y+x0,-x+y0,clolor);//-y, -x 	 /* 180-135 */
}
/*
返回 RoutPoint 围绕 StaticPoint 逆时针旋转Angle后的坐标


*/

Position_t xOLED_PointAnticlockwise(Position_t RoutPoint, Position_t StaticPoint, double Angle){
	#if (0)
	
		Position_t Last = {0, 0};
		TS16 intang = 0;
		TS32 tempx,tempy;
		
		if( Angle < 0){
			intang = (TS16)(Angle*10-0.5);
		}
		else{
			
			intang = (TS16)(Angle*10+0.5);
		}
		tempx = ((RoutPoint.x-StaticPoint.x)* my_cos(intang) - (RoutPoint.y-StaticPoint.y)*my_sin(intang))/1024 + StaticPoint.x;
		tempy = ((RoutPoint.x-StaticPoint.x)* my_sin(intang) + (RoutPoint.y-StaticPoint.y)*my_cos(intang))/1024 + StaticPoint.y;
		Last.x = tempx;
		Last.y = tempy;
		return Last;
	#else
		Position_t Last = {0, 0};
		double tempx,tempy;
		
		
		tempx = (RoutPoint.x-StaticPoint.x)*cos(Angle*3.1416/180) - (RoutPoint.y-StaticPoint.y)*sin(Angle*3.1416/180) + StaticPoint.x;
		tempy = (RoutPoint.x-StaticPoint.x)*sin(Angle*3.1416/180) + (RoutPoint.y-StaticPoint.y)*cos(Angle*3.1416/180) + StaticPoint.y;
		if(tempx<0){
			Last.x = (TS32)(tempx-0.5);
		}
		else{
			Last.x = (TS32)(tempx+0.5);
		}
		
		if(tempy<0){
			Last.y = (TS32)(tempy-0.5);
		}
		else{
			Last.y = (TS32)(tempy+0.5);
		}
		return Last;
	#endif
}

void xOLED_DrawLine( TS32 x1, TS32 y1, TS32 x2, TS32 y2, TU32 color ) { 
	TS32 dx = x2 - x1;      
	TS32 dy = y2 - y1;       
	TS32 ux = ((dx > 0) << 1) - 1;//x的增量方向，取或-1      
	TS32 uy = ((dy > 0) << 1) - 1;//y的增量方向，取或-1      
	TS32 x = x1, y = y1, eps;//eps为累加误差 
    eps = 0;

	if( dx<0 )
		dx = -dx;
	if( dy<0 )
	   dy = -dy;  
	if( dx > dy){          
		for(  x = x1; x != x2; x += ux){          
//			SetPixel(img, x, y);  
			xOLED_DrawPoint(x,y,color);	
			eps += dy;                
			if( (eps << 1) >= dx ){      
				y += uy; 
				eps -= dx;               
			}
		}
		xOLED_DrawPoint(x,y,color);	//画完最后一个点	
	}
	else{          
		for( y = y1; y != y2; y += uy){     
//			SetPixel(img, x, y);    
			xOLED_DrawPoint(x,y,color);	
			eps += dx;                
			if( (eps << 1) >= dy ){
				x += ux; 
				eps -= dy;
			}
		}
		xOLED_DrawPoint(x,y,color);//画完最后一个点
	}
}


/*
对于圆上的点
F(x,y) = (x)平方+(y)平方-r平方
下一个zhongdian
d=F(x+1,y-0.5)=(x+1)平方+(y-0.5)平方-r平方
di=F(xi+1,yi-0.5) = (xi+1)平方+(yi-0.5)平方-r平方
当di<0
di+1 = F(xi+2,yi-0.5)=(xi+2)平方+(yi-0.5)平方-r平方=di+2xi+3
当di>0
di+1 = F(xi+2,yi-1.5)=(xi+2)平方+(yi-1.5)平方-r平方=di+2xi-2yi+5

d0 = F(1,r-0.5)=1.25-r


所有d同时乘以2

d0=3-r
当di<0
	di+1 =di+4xi+3
当di>0
	di+1 =di+4xi-4yi+10

*/

void xOLED_DrawCircle( TS32 xc, TS32 yc, TS32 r, TS32 Edge, TS32 color ){

    // (xc, yc) 为圆心，r 为半径
    // fill 为是否填充
    // c 为颜色值
    // 如果圆在图片可见区域外，直接退出

    TS32 x = 0, y, yi, d;
    TS32 yMin,dMin;

		if( Edge>r){
				return;
		}
		y = r;
		yMin = r-Edge;
    d = 3 - 2*r;//F(X+2,Y-0.5)F(1,R-0.5)=1^2+(R-0.5)^2-R^2
		dMin = 3 - 2*yMin;//F(X+2,Y-0.5)F(1,R-0.5)=1^2+(R-0.5)^2-R^2
	
		// 如果填充（画实心圆）
		while(x <= y){
				if( Edge > 1){
						if( yMin<0 ){
								yi = 0;
						}
						else{
								yi = yMin;
						}
						for (; yi <= y; yi ++){
								CirclePt(xc,yc,x,yi,color);
						}
				}
				else{
						CirclePt(xc,yc,x,y,color);
				}
			
				if(d < 0){
						d = d + 4 * x + 6;

				} 
				else{
						d = d + 4 * (x - y) + 10;
						y --;
				}
				if( Edge > 1){
						if(dMin < 0){
								dMin = dMin + 4 * x + 6;

						} 
						else{
								dMin = dMin + 4 * (x - yMin) + 10;
								yMin --;
						}
				}
				x++;
		} 
}

void xOLED_DrawArc( TS32 xc, TS32 yc, TS32 r, TS32 Edge, TS32 color , float StartAngle, float Angle ){

    // (xc, yc) 为圆心，r 为半径
    // fill 为是否填充
    // c 为颜色值
    // 如果圆在图片可见区域外，直接退出

  TS32 x = 0, y = r, yi, d;
  TS32 yMin,dMin;

	TS32 Start_x,Start_y,End_x,End_y;
	TS32 Start_Quad,End_Quad;
	TS32 i;
	t_Quadrant_Porp Quadrant_Porp[8];
	double dSx,dSy,dEx,dEy;
	
	float EndAngle;
	
	EndAngle = StartAngle+Angle;
	
	dSx = r*cos((double)StartAngle*3.1416/180);
	dSy = r*sin((double)StartAngle*3.1416/180);
	
	dEx = r*cos((double)EndAngle*3.1416/180);
	dEy = r*sin((double)EndAngle*3.1416/180);
	/**/
	if( dSx >0 ){
		Start_x = (TS32)(dSx+0.5);
	}
	else{
		Start_x = (TS32)(-(dSx-0.5));	
	}
	/**/
	if( dSy >0 ){
		Start_y = (TS32)(dSy+0.5);
	}
	else{
		Start_y = (TS32)(-(dSy-0.5));	
	}
	/**/
	if( dEx >0 ){
		End_x = (TS32)(dEx+0.5);
	}
	else{
		End_x = (TS32)(-(dEx-0.5));	
	}
	/**/
	if( dEy >0 ){
		End_y = (TS32)(dEy+0.5);
	}
	else{
		End_y = (TS32)(-(dEy-0.5));	
	}
	

	
	
	Start_Quad = (TS32)((StartAngle-1)/45); 
	if( EndAngle>360 )
		End_Quad = (TS32)((EndAngle-360-1)/45); 
	else
		End_Quad = (TS32)((EndAngle-1)/45); 
	
	
	
	if( EndAngle<= 360 ){
			if( Start_Quad != End_Quad ){
				
					for(i=0;i<Start_Quad;i++){
						Quadrant_Porp[i] = Quadrant_Empty;
					}
					
					Quadrant_Porp[Start_Quad] = Quadrant_Start;
					
					for(i=Start_Quad+1;i<End_Quad;i++){
						Quadrant_Porp[i] = Quadrant_Full;
					}
					
					Quadrant_Porp[End_Quad] = Quadrant_End;
					
					for(i=End_Quad+1;i<8;i++){
						Quadrant_Porp[i] = Quadrant_Empty;
					}
			}
			else{
				if( Angle <= 45 ){//不超过45度
						for(i=0;i<Start_Quad;i++){
								Quadrant_Porp[i] = Quadrant_Empty;
						}
						Quadrant_Porp[Start_Quad] = Quadrant_StartEnd;
						
						for(i=Start_Quad+1;i<8;i++){
								Quadrant_Porp[i] = Quadrant_Empty;
						}
				}
				else{
					for(i=0;i<Start_Quad;i++){
						Quadrant_Porp[i] = Quadrant_Full;
					}
					
					Quadrant_Porp[Start_Quad] = Quadrant_StartEnd;
					
					for(i=Start_Quad+1;i<8;i++){
						Quadrant_Porp[i] = Quadrant_Full;
					}
				}
			}
	}
	else{//超过了360度
		if( Start_Quad != End_Quad ){
			for(i=0;i<End_Quad;i++){
				Quadrant_Porp[i] = Quadrant_Full;
			}
			
			Quadrant_Porp[End_Quad] = Quadrant_End;
			
			for(i=End_Quad+1;i<Start_Quad;i++){
				Quadrant_Porp[i] = Quadrant_Empty;
			}
			
			Quadrant_Porp[Start_Quad] = Quadrant_Start;
			
			for(i=Start_Quad+1;i<8;i++){
				Quadrant_Porp[i] = Quadrant_Full;
			}
		}
		else{
			if( Angle <= 45 ){//不超过45度
				for(i=0;i<Start_Quad;i++){
					Quadrant_Porp[i] = Quadrant_Empty;
				}
				
				Quadrant_Porp[Start_Quad] = Quadrant_StartEnd;
				
				for(i=Start_Quad+1;i<8;i++){
					Quadrant_Porp[i] = Quadrant_Empty;
				}
			}
			else{
				for(i=0;i<Start_Quad;i++){
					Quadrant_Porp[i] = Quadrant_Full;
				}
				
				Quadrant_Porp[Start_Quad] = Quadrant_StartEnd;
				
				for(i=Start_Quad+1;i<8;i++){
					Quadrant_Porp[i] = Quadrant_Full;
				}
			}
		}
	}
	
	

	
	
	
	
	

			d = 3 - 2*r;//F(X+2,Y-0.5)F(1,R-0.5)=1^2+(R-0.5)^2-R^2
			yMin = r-Edge;
			dMin = d = 3 - 2*yMin;
			if( Edge>1 ){
					while (x <= y) {
							/*
							画 对称点
							*/
							/*--------------------------------------*/
							/* 270-315   累加 x轴   */
							if( Quadrant_Porp[6] == Quadrant_Full ){//直接画点
									if( yMin<0 )
											yi = 0;
									else
											yi = yMin;
									for (; yi <= y; yi ++){
											xOLED_DrawPoint ( xc+x, yc+yi, color);//x,y		/* 270-315 */
									}
							}
							else if( Quadrant_Porp[6] == Quadrant_Empty ){//不操作

								;  
							}
							else if( Quadrant_Porp[6] == Quadrant_Start ){//大于 x画点
									if( x >= Start_x ){
											if( yMin<0 )
													yi = 0;
											else
													yi = yMin;
											for (; yi <= y; yi ++){
													xOLED_DrawPoint ( xc+x, yc+yi, color);//x,y		/* 270-315 */
											}
									}
							}
							else if( Quadrant_Porp[6] == Quadrant_End ){//小于x画点
									if( x <= End_x ){
											if( yMin<0 )
													yi = 0;
											else
													yi = yMin;
											for (; yi <= y; yi ++){
													xOLED_DrawPoint ( xc+x, yc+yi, color);//x,y		/* 270-315 */
											}
									}
							}
							else if( Quadrant_Porp[6] == Quadrant_StartEnd ){//
									if( Angle <= 45){
											if( ( x >= Start_x) && ( x <= End_x)){
													if( yMin<0 )
															yi = 0;
													else
															yi = yMin;
													for (; yi <= y; yi ++){
															xOLED_DrawPoint ( xc+x, yc+yi, color);//x,y		/* 270-315 */
													}
											}
									}
									else{
											if( ( x >= Start_x) || ( x <= End_x)){
													if( yMin<0 )
															yi = 0;
													else
															yi = yMin;
													for (; yi <= y; yi ++){
															xOLED_DrawPoint ( xc+x, yc+yi, color);//x,y		/* 270-315 */
													}
											}
									}
							}
							

							/* 270-225   累加 x轴 */
							

							if( Quadrant_Porp[5] == Quadrant_Full ){//直接画点
									if( yMin<0 )
											yi = 0;
									else
											yi = yMin;
									for (; yi <= y; yi ++){
											xOLED_DrawPoint ( xc-x, yc+yi, color);//-x,y		/* 270-225 */
									}
							}
							else if( Quadrant_Porp[5] == Quadrant_Empty ){//不操作

								;  
							}
							else if( Quadrant_Porp[5] == Quadrant_Start ){//小于 x画点
									if( x <= Start_x ){
											if( yMin<0 )
													yi = 0;
											else
													yi = yMin;
											for (; yi <= y; yi ++){
													xOLED_DrawPoint ( xc-x, yc+yi, color);//-x,y		/* 270-225 */
											}
									}
							}
							else if( Quadrant_Porp[5] == Quadrant_End ){//大于x画点
									if( x >= End_x ){
											if( yMin<0 )
													yi = 0;
											else
													yi = yMin;
											for (; yi <= y; yi ++){
													xOLED_DrawPoint ( xc-x, yc+yi, color);//-x,y		/* 270-225 */
											}
									}
							}
							else if( Quadrant_Porp[5] == Quadrant_StartEnd ){//	
									if( Angle <= 45){
											if( ( x >= End_x) && ( x <= Start_x)){
													if( yMin<0 )
															yi = 0;
													else
															yi = yMin;
													for (; yi <= y; yi ++){
															xOLED_DrawPoint ( xc-x, yc+yi, color);//-x,y		/* 270-225 */
													}
											}
									}
									else{
											if( ( x >= End_x) || ( x <= Start_x)){
													if( yMin<0 )
															yi = 0;
													else
															yi = yMin;
													for (; yi <= y; yi ++){
															xOLED_DrawPoint ( xc-x, yc+yi, color);//-x,y		/* 270-225 */
													}
											}
									}
							}



							/* 90-45   累加 x轴 */
							

							if( Quadrant_Porp[1] == Quadrant_Full ){//直接画点
									if( yMin<0 )
											yi = 0;
									else
											yi = yMin;
									for (; yi <= y; yi ++){
											xOLED_DrawPoint ( xc+x, yc-yi, color);//x, -y		/* 90-45 */
									}
							}
							else if( Quadrant_Porp[1] == Quadrant_Empty ){//不操作

								;  
							}
							else if( Quadrant_Porp[1] == Quadrant_Start ){//小于 x画点
									if( x <= Start_x ){
											if( yMin<0 )
													yi = 0;
											else
													yi = yMin;
											for (; yi <= y; yi ++){
													xOLED_DrawPoint ( xc+x, yc-yi, color);//x, -y		/* 90-45 */
											}
									}

							}
							else if( Quadrant_Porp[1] == Quadrant_End ){//大于x画点
									if( x >= End_x ){
											if( yMin<0 )
													yi = 0;
											else
													yi = yMin;
											for (; yi <= y; yi ++){
													xOLED_DrawPoint ( xc+x, yc-yi, color);//x, -y		/* 90-45 */
											}
									}
							}
							else if( Quadrant_Porp[1] == Quadrant_StartEnd ){//
								
								if( Angle <= 45){
										if( ( x >= End_x) && ( x <= Start_x)){
												if( yMin<0 )
														yi = 0;
												else
														yi = yMin;
												for (; yi <= y; yi ++){
														xOLED_DrawPoint ( xc+x, yc-yi, color);//x, -y		/* 90-45 */
												}
										}
								}
								else{
										if( ( x >= End_x) || ( x <= Start_x)){
												if( yMin<0 )
														yi = 0;
												else
														yi = yMin;
												for (; yi <= y; yi ++){
														xOLED_DrawPoint ( xc+x, yc-yi, color);//x, -y		/* 90-45 */
												}
										}
								}
							}



							/* 90-135   累加 x轴 */
							
							if( Quadrant_Porp[2] == Quadrant_Full ){//直接画点
									if( yMin<0 )
											yi = 0;
									else
											yi = yMin;
									for (; yi <= y; yi ++){
											xOLED_DrawPoint ( xc-x, yc-yi, color);//-x, -y	/* 90-135 */
									}
							}
							else if( Quadrant_Porp[2] == Quadrant_Empty ){//不操作

								;  
							}
							else if( Quadrant_Porp[2] == Quadrant_Start ){//大于 x画点
									if( x >= Start_x ){
											if( yMin<0 )
													yi = 0;
											else
													yi = yMin;
											for (; yi <= y; yi ++){
													xOLED_DrawPoint ( xc-x, yc-yi, color);//-x, -y	/* 90-135 */
											}
									}
							}
							else if( Quadrant_Porp[2] == Quadrant_End ){//小于x画点
								if( x <= End_x ){
											if( yMin<0 )
													yi = 0;
											else
													yi = yMin;
											for (; yi <= y; yi ++){
													xOLED_DrawPoint ( xc-x, yc-yi, color);//-x, -y	/* 90-135 */
											}
									}

							}
							else if( Quadrant_Porp[2] == Quadrant_StartEnd ){//
								
								if( Angle <= 45){
											if( yMin<0 )
													yi = 0;
											else
													yi = yMin;
											for (; yi <= y; yi ++){
													xOLED_DrawPoint ( xc-x, yc-yi, color);//-x, -y	/* 90-135 */
											}
									}
								else{
									if( ( x >= Start_x) || ( x <= End_x)){
											if( yMin<0 )
													yi = 0;
											else
													yi = yMin;
											for (; yi <= y; yi ++){
													xOLED_DrawPoint ( xc-x, yc-yi, color);//-x, -y	/* 90-135 */
											}
									}
								}
							}
							
							
							/* 0-315   累加 y轴 */
							
							if( Quadrant_Porp[7] == Quadrant_Full ){//直接画点
									if( yMin<0 )
											yi = 0;
									else
											yi = yMin;
									for (; yi <= y; yi ++){
											xOLED_DrawPoint ( xc+yi, yc+x, color);//y, x		/* 0-315 */
									}
							}
							else if( Quadrant_Porp[7] == Quadrant_Empty ){//不操作

								;  
							}
							else if( Quadrant_Porp[7] == Quadrant_Start ){//小于 x画点
									if( x <= Start_y ){
											if( yMin<0 )
													yi = 0;
											else
													yi = yMin;
											for (; yi <= y; yi ++){
													xOLED_DrawPoint ( xc+yi, yc+x, color);//y, x		/* 0-315 */
											}
									}
							}
							else if( Quadrant_Porp[7] == Quadrant_End ){//大于x画点
									if( x >= End_y ){
											if( yMin<0 )
													yi = 0;
											else
													yi = yMin;
											for (; yi <= y; yi ++){
													xOLED_DrawPoint ( xc+yi, yc+x, color);//y, x		/* 0-315 */
											}
									}
							}
							else if( Quadrant_Porp[7] == Quadrant_StartEnd ){//	
									if( Angle <= 45){
											if( ( x >= End_y) && ( x <= Start_y)){
													if( yMin<0 )
															yi = 0;
													else
															yi = yMin;
													for (; yi <= y; yi ++){
															xOLED_DrawPoint ( xc+yi, yc+x, color);//y, x		/* 0-315 */
													}
											}
									}
									else{
											if( ( x >= End_y) || ( x <= Start_y)){
													if( yMin<0 )
															yi = 0;
													else
															yi = yMin;
													for (; yi <= y; yi ++){
															xOLED_DrawPoint ( xc+yi, yc+x, color);//y, x		/* 0-315 */
													}
											}
									}
							}



							/* 0-45   累加 y轴 */
							
							if( Quadrant_Porp[0] == Quadrant_Full ){//直接画点	
									if( yMin<0 )
											yi = 0;
									else
											yi = yMin;
									for (; yi <= y; yi ++){
											xOLED_DrawPoint ( xc+yi, yc-x, color);//y, -x		/* 0-45 */
									}						
							}
							else if( Quadrant_Porp[0] == Quadrant_Empty ){//不操作

								;  
							}
							else if( Quadrant_Porp[0] == Quadrant_Start ){//大于 x画点
									if( x >= Start_y ){
											if( yMin<0 )
													yi = 0;
											else
													yi = yMin;
											for (; yi <= y; yi ++){
													xOLED_DrawPoint ( xc+yi, yc-x, color);//y, -x		/* 0-45 */
											}
									}
							}
							else if( Quadrant_Porp[0] == Quadrant_End ){//小于x画点
									if( x <= End_y ){
											if( yMin<0 )
													yi = 0;
											else
													yi = yMin;
											for (; yi <= y; yi ++){
													xOLED_DrawPoint ( xc+yi, yc-x, color);//y, -x		/* 0-45 */
											}
									}
							}
							else if( Quadrant_Porp[0] == Quadrant_StartEnd ){//
								
									if( Angle <= 45){
											if( ( x >= Start_y) && ( x <= End_y)){
													if( yMin<0 )
															yi = 0;
													else
															yi = yMin;
													for (; yi <= y; yi ++){
															xOLED_DrawPoint ( xc+yi, yc-x, color);//y, -x		/* 0-45 */
													}
											}	
									}
									else{
											if( ( x >= Start_y) || ( x <= End_y)){
													if( yMin<0 )
															yi = 0;
													else
															yi = yMin;
													for (; yi <= y; yi ++){
															xOLED_DrawPoint ( xc+yi, yc-x, color);//y, -x		/* 0-45 */
													}
											}	
									}
							}


							/* 180-225   累加 y轴*/
							
							if( Quadrant_Porp[4] == Quadrant_Full ){//直接画点
									if( yMin<0 )
											yi = 0;
									else
											yi = yMin;
									for (; yi <= y; yi ++){
											xOLED_DrawPoint ( xc-yi, yc+x, color);//-y, x		/* 180-225 */	
									}	
							}
							else if( Quadrant_Porp[4] == Quadrant_Empty ){//不操作

								;  
							}
							else if( Quadrant_Porp[4] == Quadrant_Start ){//大于 x画点
									if( x >= Start_y ){
											if( yMin<0 )
													yi = 0;
											else
													yi = yMin;
											for (; yi <= y; yi ++){
													xOLED_DrawPoint ( xc-yi, yc+x, color);//-y, x		/* 180-225 */	
											}	
									}
							}
							else if( Quadrant_Porp[4] == Quadrant_End ){//小于x画点
									if( x <= End_y ){
											if( yMin<0 )
													yi = 0;
											else
													yi = yMin;
											for (; yi <= y; yi ++){
													xOLED_DrawPoint ( xc-yi, yc+x, color);//-y, x		/* 180-225 */	
											}	
									}
							}
							else if( Quadrant_Porp[4] == Quadrant_StartEnd ){//
								
									if( Angle <= 45){
											if( ( x >= Start_y) && ( x <= End_y)){
													if( yMin<0 )
															yi = 0;
													else
															yi = yMin;
													for (; yi <= y; yi ++){
															xOLED_DrawPoint ( xc-yi, yc+x, color);//-y, x		/* 180-225 */	
													}	
											}
									}
									else{
											if( ( x >= Start_y) || ( x <= End_y)){
													if( yMin<0 )
															yi = 0;
													else
															yi = yMin;
													for (; yi <= y; yi ++){
															xOLED_DrawPoint ( xc-yi, yc+x, color);//-y, x		/* 180-225 */	
													}	
											}
									}
							}








							/* 180-135   累加 y轴 */
							
							if( Quadrant_Porp[3] == Quadrant_Full ){//直接画点
									if( yMin<0 )
											yi = 0;
									else
											yi = yMin;
									for (; yi <= y; yi ++){
											xOLED_DrawPoint ( xc-yi,yc-x, color);//-y, -x 	 /* 180-135 */
									}
							}
							else if( Quadrant_Porp[3] == Quadrant_Empty ){//不操作

								;  
							}
							else if( Quadrant_Porp[3] == Quadrant_Start ){//小于 x画点
									if( x <= Start_y ){
											if( yMin<0 )
													yi = 0;
											else
													yi = yMin;
											for (; yi <= y; yi ++){
													xOLED_DrawPoint ( xc-yi,yc-x, color);//-y, -x 	 /* 180-135 */
											}
									}
							}
							else if( Quadrant_Porp[3] == Quadrant_End ){//大于x画点
									if( x >= End_y ){
											if( yMin<0 )
													yi = 0;
											else
													yi = yMin;
											for (; yi <= y; yi ++){
													xOLED_DrawPoint ( xc-yi,yc-x, color);//-y, -x 	 /* 180-135 */
											}
									}
							}
							else if( Quadrant_Porp[3] == Quadrant_StartEnd ){//
								
									if( Angle <= 45){
											if( ( x >= End_y) && ( x <= Start_y)){
													if( yMin<0 )
															yi = 0;
													else
															yi = yMin;
													for (; yi <= y; yi ++){
															xOLED_DrawPoint ( xc-yi,yc-x, color);//-y, -x 	 /* 180-135 */
													}
											}
									}
									else{
											if( ( x >= End_y) || ( x <= Start_y)){
													if( yMin<0 )
															yi = 0;
													else
															yi = yMin;
													for (; yi <= y; yi ++){
															xOLED_DrawPoint ( xc-yi,yc-x, color);//-y, -x 	 /* 180-135 */
													}
											}
									}
							}


							
							/*---------------------------------------------------------*/
							if (d < 0) {
									d = d + 4 * x + 6;
							}
							else {
									d = d + 4 * (x - y) + 10;
									y --;
							}
							//dMin
							if (dMin < 0) {
									dMin = dMin + 4 * x + 6;
							}
							else {
									dMin = dMin + 4 * (x - yMin) + 10;
									yMin --;
							}
							x ++;
						}
			}
			else{
					// 如果不填充（画空心圆）
					while (x <= y) {
	//            _draw_circle_8(img, xc, yc, x, y, c);
	//			xOLED_DrawPoint(xc+x,yc+y);
	//				CirclePt(xc,yc,x,y);
						/*
						画 对称点
						*/
						/*--------------------------------------*/
						/* 270-315   判断 x   */
						if( Quadrant_Porp[6] == Quadrant_Full ){//直接画点
							xOLED_DrawPoint ( xc+x, yc+y, color);//x,y		/* 270-315 */
						}
						else if( Quadrant_Porp[6] == Quadrant_Empty ){//不操作

							;  
						}
						else if( Quadrant_Porp[6] == Quadrant_Start ){//大于 x画点
							if( x >= Start_x )
								xOLED_DrawPoint ( xc+x, yc+y, color);//x,y		/* 270-315 */

						}
						else if( Quadrant_Porp[6] == Quadrant_End ){//小于x画点
							if( x <= End_x )
								xOLED_DrawPoint ( xc+x, yc+y, color);//x,y		/* 270-315 */

						}
						else if( Quadrant_Porp[6] == Quadrant_StartEnd ){//
							if( Angle <= 45){
								if( ( x >= Start_x) && ( x <= End_x))
									xOLED_DrawPoint ( xc+x, yc+y, color);//x,y		/* 270-315 */
							}
							else{
								if( ( x >= Start_x) || ( x <= End_x))
									xOLED_DrawPoint ( xc+x, yc+y, color);//x,y		/* 270-315 */
								
							}
						}
						

						/* 270-225   判断 x */
						

						if( Quadrant_Porp[5] == Quadrant_Full ){//直接画点
							xOLED_DrawPoint ( xc-x, yc+y, color);//-x,y		/* 270-225 */
						}
						else if( Quadrant_Porp[5] == Quadrant_Empty ){//不操作

							;  
						}
						else if( Quadrant_Porp[5] == Quadrant_Start ){//小于 x画点
							if( x <= Start_x )
								xOLED_DrawPoint ( xc-x, yc+y, color);//-x,y		/* 270-225 */

						}
						else if( Quadrant_Porp[5] == Quadrant_End ){//大于x画点
							if( x >= End_x )
								xOLED_DrawPoint ( xc-x, yc+y, color);//-x,y		/* 270-225 */
						}
						else if( Quadrant_Porp[5] == Quadrant_StartEnd ){//
							
							if( Angle <= 45){
								if( ( x >= End_x) && ( x <= Start_x))
									xOLED_DrawPoint ( xc-x, yc+y, color);//-x,y		/* 270-225 */
							}
							else{
								if( ( x >= End_x) || ( x <= Start_x))
									xOLED_DrawPoint ( xc-x, yc+y, color);//-x,y		/* 270-225 */
							}
						}



						/* 90-45   判断 x */
						

						if( Quadrant_Porp[1] == Quadrant_Full ){//直接画点
							xOLED_DrawPoint ( xc+x, yc-y, color);//x, -y		/* 90-45 */
						}
						else if( Quadrant_Porp[1] == Quadrant_Empty ){//不操作

							;  
						}
						else if( Quadrant_Porp[1] == Quadrant_Start ){//小于 x画点
							if( x <= Start_x )
								xOLED_DrawPoint ( xc+x, yc-y, color);//x, -y		/* 90-45 */

						}
						else if( Quadrant_Porp[1] == Quadrant_End ){//大于x画点
							if( x >= End_x )
								xOLED_DrawPoint ( xc+x, yc-y, color);//x, -y		/* 90-45 */
						}
						else if( Quadrant_Porp[1] == Quadrant_StartEnd ){//
							
							if( Angle <= 45){
								if( ( x >= End_x) && ( x <= Start_x))
									xOLED_DrawPoint ( xc+x, yc-y, color);//x, -y		/* 90-45 */
							}
							else{
								if( ( x >= End_x) || ( x <= Start_x))
									xOLED_DrawPoint ( xc+x, yc-y, color);//x, -y		/* 90-45 */
							}
						}



						/* 90-135   判断 x */
						
						if( Quadrant_Porp[2] == Quadrant_Full ){//直接画点
							xOLED_DrawPoint ( xc-x, yc-y, color);//-x, -y	/* 90-135 */
						}
						else if( Quadrant_Porp[2] == Quadrant_Empty ){//不操作

							;  
						}
						else if( Quadrant_Porp[2] == Quadrant_Start ){//大于 x画点
							if( x >= Start_x )
								xOLED_DrawPoint ( xc-x, yc-y, color);//-x, -y	/* 90-135 */

						}
						else if( Quadrant_Porp[2] == Quadrant_End ){//小于x画点
							if( x <= End_x )
								xOLED_DrawPoint ( xc-x, yc-y, color);//-x, -y	/* 90-135 */

						}
						else if( Quadrant_Porp[2] == Quadrant_StartEnd ){//
							
							if( Angle <= 45){
								if( ( x >= Start_x) && ( x <= End_x))
									xOLED_DrawPoint ( xc-x, yc-y, color);//-x, -y	/* 90-135 */
							}
							else{
								if( ( x >= Start_x) || ( x <= End_x))
									xOLED_DrawPoint ( xc-x, yc-y, color);//-x, -y	/* 90-135 */
							}
						}
						
						
						/* 0-315   判断 y */
						
						if( Quadrant_Porp[7] == Quadrant_Full ){//直接画点
							xOLED_DrawPoint ( xc+y, yc+x, color);//y, x		/* 0-315 */	
						}
						else if( Quadrant_Porp[7] == Quadrant_Empty ){//不操作

							;  
						}
						else if( Quadrant_Porp[7] == Quadrant_Start ){//小于 x画点
							if( x <= Start_y )
								xOLED_DrawPoint ( xc+y, yc+x, color);//y, x		/* 0-315 */	

						}
						else if( Quadrant_Porp[7] == Quadrant_End ){//大于x画点
							if( x >= End_y )
								xOLED_DrawPoint ( xc+y, yc+x, color);//y, x		/* 0-315 */	
						}
						else if( Quadrant_Porp[7] == Quadrant_StartEnd ){//
							
							if( Angle <= 45){
								if( ( x >= End_y) && ( x <= Start_y))
									xOLED_DrawPoint ( xc+y, yc+x, color);//y, x		/* 0-315 */	
							}
							else{
								if( ( x >= End_y) || ( x <= Start_y))
									xOLED_DrawPoint ( xc+y, yc+x, color);//y, x		/* 0-315 */	
							}
						}



						/* 0-45   判断 y */
						
						if( Quadrant_Porp[0] == Quadrant_Full ){//直接画点
							xOLED_DrawPoint ( xc+y, yc-x, color);//y, -x		/* 0-45 */		
						}
						else if( Quadrant_Porp[0] == Quadrant_Empty ){//不操作

							;  
						}
						else if( Quadrant_Porp[0] == Quadrant_Start ){//大于 x画点
							if( x >= Start_y )
								xOLED_DrawPoint ( xc+y, yc-x, color);//y, -x		/* 0-45 */	

						}
						else if( Quadrant_Porp[0] == Quadrant_End ){//小于x画点
							if( x <= End_y )
								xOLED_DrawPoint ( xc+y, yc-x, color);//y, -x		/* 0-45 */	
						}
						else if( Quadrant_Porp[0] == Quadrant_StartEnd ){//
							
							if( Angle <= 45){
								if( ( x >= Start_y) && ( x <= End_y))
									xOLED_DrawPoint ( xc+y, yc-x, color);//y, -x		/* 0-45 */	
							}
							else{
								if( ( x >= Start_y) || ( x <= End_y))
									xOLED_DrawPoint ( xc+y, yc-x, color);//y, -x		/* 0-45 */	
							}
						}




						/* 180-225   判断 y */
						
						if( Quadrant_Porp[4] == Quadrant_Full ){//直接画点
							xOLED_DrawPoint ( xc-y, yc+x, color);//-y, x		/* 180-225 */	
						}
						else if( Quadrant_Porp[4] == Quadrant_Empty ){//不操作

							;  
						}
						else if( Quadrant_Porp[4] == Quadrant_Start ){//大于 x画点
							if( x >= Start_y )
								xOLED_DrawPoint ( xc-y, yc+x, color);//-y, x		/* 180-225 */

						}
						else if( Quadrant_Porp[4] == Quadrant_End ){//小于x画点
							if( x <= End_y )
								xOLED_DrawPoint ( xc-y, yc+x, color);//-y, x		/* 180-225 */	
						}
						else if( Quadrant_Porp[4] == Quadrant_StartEnd ){//
							
							if( Angle <= 45){
								if( ( x >= Start_y) && ( x <= End_y))
									xOLED_DrawPoint ( xc-y, yc+x, color);//-y, x		/* 180-225 */
							}
							else{
								if( ( x >= Start_y) || ( x <= End_y))
									xOLED_DrawPoint ( xc-y, yc+x, color);//-y, x		/* 180-225 */
							}
						}








						/* 180-135   判断 y */
						
						if( Quadrant_Porp[3] == Quadrant_Full ){//直接画点
							xOLED_DrawPoint ( xc-y,yc-x, color);//-y, -x 	 /* 180-135 */
						}
						else if( Quadrant_Porp[3] == Quadrant_Empty ){//不操作

							;  
						}
						else if( Quadrant_Porp[3] == Quadrant_Start ){//小于 x画点
							if( x <= Start_y )
								xOLED_DrawPoint ( xc-y,yc-x, color);//-y, -x 	 /* 180-135 */

						}
						else if( Quadrant_Porp[3] == Quadrant_End ){//大于x画点
							if( x >= End_y )
								xOLED_DrawPoint ( xc-y,yc-x, color);//-y, -x 	 /* 180-135 */
						}
						else if( Quadrant_Porp[3] == Quadrant_StartEnd ){//
							
							if( Angle <= 45){
								if( ( x >= End_y) && ( x <= Start_y))
									xOLED_DrawPoint ( xc-y,yc-x, color);//-y, -x 	 /* 180-135 */
							}
							else{
								if( ( x >= End_y) || ( x <= Start_y))
									xOLED_DrawPoint ( xc-y,yc-x, color);//-y, -x 	 /* 180-135 */
							}
						}





						
						
						/*---------------------------------------------------------*/
						if (d < 0) {
								d = d + 4 * x + 6;
						}
						else {
								d = d + 4 * (x - y) + 10;
								y --;
						}
						x ++;
					}
			}
}







void xOLED_FillRectangle(TU32 x, TU32 y, TU32 width, TU32 xSize, TU32 ySize, const TU8* pData ,TU16 Color, TU8 Mode ){

	TU16 i,j,k;
//	TU16 index;
	TU8  tBYTE = 0;
	if( pData ){

		for( i=0; i<ySize/8; i++ ){//字节行数
			for( j=0; j<xSize; j++ ){//列数
			    tBYTE = pData[i*width+j];
				for( k=0; k<8; k++ ){//像素数
					if(tBYTE&0x80){
						xOLED_DrawPoint (x+j,y+i*8+k,Color); 
					}
					else{
						if( Mode ){
							
							xOLED_DrawPoint (x+j,y+i*8+k,!Color); 
						}	
					}
					tBYTE<<=1;		
				}
			}
		}
		if( ySize%8 ){
			for( j=0; j<xSize; j++ ){//列数
			    tBYTE = pData[i*width+j];
				for( k=0; k<ySize%8; k++ ){//像素数
					if(tBYTE&0x80){
						xOLED_DrawPoint (x+j,y+i*8+k,Color); 
					}
					else{
						if( Mode ){
							
							xOLED_DrawPoint (x+j,y+i*8+k,!Color); 
						}	
					}
					tBYTE<<=1;		
				}
			}
		}
	}			  				  			  
}

