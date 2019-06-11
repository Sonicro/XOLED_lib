#include "xoled_interface.h"


void xOLED_Itf_HadwareInit( void ){
	
/*
	wiringPiSPISetupMode(0,10000000,0);
	pinMode(21,OUTPUT);
	pinMode(22,OUTPUT);
	pinMode(28,OUTPUT);
	pinMode(29,OUTPUT);
	
	MX_SPI1_Init();
 */	
    GPIO_InitTypeDef GPIO_InitStructure;
  	SPI_InitTypeDef  SPI_InitStructure;

    RCC_APB1PeriphClockCmd(	RCC_APB1Periph_SPI2,  ENABLE );//SPI2时钟使能 	
    RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOB|RCC_AHBPeriph_GPIOC,ENABLE );
  
  
  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;  //PB13/14/15复用推挽输出 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOB

    GPIO_PinAFConfig(GPIOB,GPIO_PinSource13|GPIO_PinSource15,GPIO_AF_0);
    
    GPIO_SetBits(GPIOB,GPIO_Pin_13|GPIO_Pin_15);  //PB13/14/15上拉
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;  //PB13/14/15复用推挽输出 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOB
    GPIO_SetBits(GPIOB,GPIO_Pin_11|GPIO_Pin_12);  //PB13/14/15上拉

    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;  //PB13/14/15复用推挽输出 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOB
    GPIO_SetBits(GPIOC,GPIO_Pin_13);  //PB13/14/15上拉
    GPIO_ResetBits(GPIOC,GPIO_Pin_13);  //PB13/14/15上拉
    
    SPI_I2S_DeInit(SPI2);
    SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;  //设置SPI单向或者双向的数据模式:SPI设置为双线双向全双工
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//设置SPI工作模式:设置为主SPI
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//设置SPI的数据大小:SPI发送接收8位帧结构
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;		//串行同步时钟的空闲状态为高电平
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;	//串行同步时钟的第二个跳变沿（上升或下降）数据被采样
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;		//定义波特率预分频的值:波特率预分频值为256
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
    SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRC值计算的多项式
    SPI_Init(SPI2, &SPI_InitStructure);  //根据SPI_InitStruct中指定的参数初始化外设SPIx寄存器
   
   
//    SPI_NSSInternalSoftwareConfig(SPI2,SPI_NSSInternalSoft_Reset);
    SPI_Cmd(SPI2, ENABLE); //使能SPI外设	 
  
 
}

void xOLED_Itf_WriteBytes(TU8 *data, TU32 Num){
	/*
	TU8 receivedbyte;
	if(HAL_SPI_TransmitReceive(&hspi1, (uint8_t*) data, (uint8_t*) &receivedbyte, Num, SPIx_TIMEOUT_MAX) != HAL_OK)
  {
//    SPIx_Error();
  }
	*/
  /*
	wiringPiSPIDataRW(0,data,Num);  
	*/
 
   u16 retry=0;
   TU32 i=0;
   for(i=0;i<Num;i++){
      while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET){ //检查指定的SPI标志位设置与否:发送缓存空标志位
          retry++;
//          if(retry>2000)return 0;
      }	
      
      SPI_SendData8(SPI2, data[i]); //通过外设SPIx发送一个数据
//#define SPI2_8Data ((uint32_t)SPI2 +  0x0c)
//  
//      *(__IO uint8_t *) SPI2_8Data = data[i];
   }
  
}


/*等待传输结束 用于刷新屏幕，否则易出现乱码*/
void xOLED_Itf_WaitTransFinish( void ){
    u16 retry=0;
    while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET){ //检查指定的SPI标志位设置与否:发送缓存空标志位
         retry++;
        if(retry>10000)
        return ;
    }
}

