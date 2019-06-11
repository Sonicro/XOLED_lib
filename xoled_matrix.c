#include "xoled_matrix.h"
#include "xoled_core.h"

const TU8 ByteTable[8] = {
	0x00,//0
	0x01,//1 	0 0 0 0 0 0 0 1 
	0x03,//2 	0 0 0 0 0 0 1 1 
	0x07,//3 	0 0 0 0 0 1 1 1 
	0x0f,//4 	0 0 0 0 1 1 1 1 
	0x1f,//5 	0 0 0 1 1 1 1 1
	0x3f,//6 	0 0 1 1 1 1 1 1 
	0x7f,//7 	0 1 1 1 1 1 1 1 
};


void Matrix_DrawPiont( TU16 x, TU16 y, Matrix_t *pMatrix, TU8 Value ){
	

		TU16 pos,bx,temp=0;
		if( ( x>=pMatrix->XSize ) ||
				( y>=pMatrix->YSize ) )
				return;//超出范围了.

		pos=y/8;
		bx= y%8;
		temp=1<<bx;

		if( Value ){
				*(pMatrix->GRAM+pos*pMatrix->XSize+x)|=temp;
		}
		else{
				*(pMatrix->GRAM+pos*pMatrix->XSize+x)&=~temp;
		}
}
TU8 Matrix_ReadPiont( TU16 x, TU16 y, Matrix_t *pMatrix ){
	

		TU16 pos,bx,temp=0;
		if( (x>=pMatrix->XSize) ||
				(y>=pMatrix->YSize) )
				return 0 ;//超出范围了.

		pos=y/8;
		bx= y%8;
		temp=1<<bx;

		if( *(pMatrix->GRAM+pos*pMatrix->XSize+x) &temp ){
				return 1;
		}
		else{
				return 0;
		}
}


void Matrix_ScrollX_1( Matrix_t *pMatrix , TU8 Dir ){
		TU16 i=0,j=0;
		TU16 X=pMatrix->XSize,Y=pMatrix->YSize;
		volatile TU8 Temp = 0 ,*tPiont = 0;
		Y/=8;
		for(j=0;j<Y;j++){
				if( Dir ){//左移
						tPiont = pMatrix->GRAM+j*X;
						Temp = *tPiont;
						for(i=0;i<X-1;i++){
							*(tPiont+i) = *(tPiont+i+1);
						}
						*(tPiont+X-1) = Temp;
				}
				else{//右移
					
						tPiont = pMatrix->GRAM+j*X+X-1;
						Temp = *tPiont;
						for(i=0;i<X-1;i++){
							*(tPiont-i) = *(tPiont-i-1);
						}
						*(tPiont-X+1) = Temp;
				}
		}
}

void Matrix_ScrollY_1( Matrix_t *pMatrix , TU8 Dir ){
	
		TU16 i=0,j=0;
		TU16 X=pMatrix->XSize,Y=pMatrix->YSize;
		volatile TU8 Temp = 0 ,Temp1 = 0,*tPiont = 0;
		
		Y /=8 ;
		for(j=0;j<X;j++){
				if( Dir ){//上移		
						tPiont = pMatrix->GRAM+j;
						Temp = *tPiont;
						for(i=0;i<Y-1;i++){
							Temp1 = 0;
							Temp1 = (*(tPiont+i*X)>>1)|(*(tPiont+(i+1)*X)<<7);
							*(tPiont+i*X) = Temp1;
						}
						Temp1 = 0;
						*(tPiont+(Y-1)*X) = (*(tPiont+(Y-1)*X)>>1)|(Temp<<7);
				}
				else{//下移
					
						tPiont = pMatrix->GRAM+(Y-1)*X+ j;
						Temp = *tPiont;
						for(i=0;i<Y-1;i++){
							Temp1 = 0;
							Temp1 = (*(tPiont-i*X)<<1)|(*(tPiont-i*X-X)>>7);
							*(tPiont-i*X) = Temp1;
						}
						Temp1 = 0;
						*(tPiont-(Y-1)*X) = (*(tPiont-(Y-1)*X)<<1)|(Temp>>7);
				}
		}
}
void Matrix_Copy(  Matrix_t		*MatrixDes, 
									 Matrix_t 	*MatrixSrc ,
									 TU16 Dx, 
									 TU16 Dy, 
									 TU16 Sx, 
									 TU16 Sy, 
									 TU16 xSize, 
									 TU16 ySize ){
					   			   
		TU16 i = 0, n = 0;
							 
		TU16 PageRemD0 = 0;
		TU16 PageIntD0 = 0;
		TU16 PageIntD1 = 0;
		TU16 PageRemD1 = 0;
							 
		TU16 PageRemS = 0;
		TU16 NPageRemS = 0;
		TU16 PageIntS = 0;
							 
		TU8  PageChar = 0;
		TU16 TV0 ,TV1 ,TV2;
	//	Rectdad.Rect = Rect;
		PageRemD0 = Dy%8;
		PageIntD0 = Dy/8;	
		
		PageIntS = Sy/8;;
		PageRemS = Sy%8;	
		NPageRemS = 8-PageRemS;
		if( PageRemD0 ){
				/*复制 REM0  余数行*/			
				TV0 = Sx+MatrixSrc->XSize*PageIntS;
				TV1 = TV0+MatrixSrc->XSize;
				for(i=0;i<xSize;i++){
						*(MatrixDes->GRAM+(Dx+i)+MatrixDes->XSize*PageIntD0) &= ByteTable[PageRemD0];
						PageChar = 0;
						if( !PageRemS ){
								PageChar = *(MatrixSrc->GRAM+TV0+i);
						}
						else{
								PageChar = __CombineChar__(*(MatrixSrc->GRAM+TV0+i),*(MatrixSrc->GRAM+TV1+i),PageRemS,NPageRemS);			
						}
						*(MatrixDes->GRAM+(Dx+i)+MatrixDes->XSize*PageIntD0) |= PageChar<<PageRemD0;
				}
				Sy   += (8-PageRemD0);//修改已经复制了的行
				Dy	  += (8-PageRemD0);
				ySize -= (8-PageRemD0);
		}
		PageIntS = Sy/8;
		PageRemS = Sy%8;
		NPageRemS = 8-PageRemS;
		
		PageIntD0 = Dy/8;
		PageIntD1 = ySize/8;
		PageRemD1 = ySize%8;
		/*复制 INT0整数 行*/
		for(n=0;n<PageIntD1;n++){
				
				TV0 = Sx+MatrixSrc->XSize*(PageIntS+n);
				TV1 = TV0+MatrixSrc->XSize;
				TV2 = Dx+MatrixDes->XSize*(PageIntD0+n);
				for(i=0;i<xSize;i++){
						PageChar = 0;
//						PageChar = (*(MatrixSrc->GRAM+(i+Sx0)+MatrixSrc->XSize*(PageIntS+n)))>>PageRemS | 
//											 (*(MatrixSrc->GRAM+(i+Sx0)+MatrixSrc->XSize*(PageIntS+n+1)))<<(8-PageRemS);
						if( !PageRemS ){
								PageChar = *(MatrixSrc->GRAM+TV0+i);
						}
						else{
								PageChar = __CombineChar__(*(MatrixSrc->GRAM+TV0+i),*(MatrixSrc->GRAM+TV1+i),PageRemS,NPageRemS);			
						}
//						*(MatrixDes->GRAM+(Dx0+i)+MatrixDes->XSize*(PageIntD0+n)) = PageChar;
						*(MatrixDes->GRAM+TV2+i) = PageChar;
				}
		}
		if( PageRemD1 ){
				/*复制 REM1*/
				TV0 = Sx+MatrixSrc->XSize*(PageIntS+n);
				TV1 = TV0+MatrixSrc->XSize;
				TV2 = Dx+MatrixDes->XSize*(PageIntD0+PageIntD1);
				for(i=0;i<xSize;i++){ 
						PageChar = 0;
						if( !PageRemS ){
								PageChar = *(MatrixSrc->GRAM+TV0+i);
						}
						else{
								PageChar = __CombineChar__(*(MatrixSrc->GRAM+TV0+i),*(MatrixSrc->GRAM+TV1+i),PageRemS,NPageRemS);			
						}
						
						*(MatrixDes->GRAM+TV2+i) &= ~ByteTable[PageRemD1];
						PageChar &= ByteTable[PageRemD1];
						*(MatrixDes->GRAM+TV2+i) |= PageChar;
				}		
		}				   
}

