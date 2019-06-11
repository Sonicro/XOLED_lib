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

    RCC_APB1PeriphClockCmd(	RCC_APB1Periph_SPI2,  ENABLE );//SPI2ʱ��ʹ�� 	
    RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOB|RCC_AHBPeriph_GPIOC,ENABLE );
  
  
  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;  //PB13/14/15����������� 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOB

    GPIO_PinAFConfig(GPIOB,GPIO_PinSource13|GPIO_PinSource15,GPIO_AF_0);
    
    GPIO_SetBits(GPIOB,GPIO_Pin_13|GPIO_Pin_15);  //PB13/14/15����
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;  //PB13/14/15����������� 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOB
    GPIO_SetBits(GPIOB,GPIO_Pin_11|GPIO_Pin_12);  //PB13/14/15����

    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;  //PB13/14/15����������� 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOB
    GPIO_SetBits(GPIOC,GPIO_Pin_13);  //PB13/14/15����
    GPIO_ResetBits(GPIOC,GPIO_Pin_13);  //PB13/14/15����
    
    SPI_I2S_DeInit(SPI2);
    SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;  //����SPI�������˫�������ģʽ:SPI����Ϊ˫��˫��ȫ˫��
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//����SPI����ģʽ:����Ϊ��SPI
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;		//����ͬ��ʱ�ӵĿ���״̬Ϊ�ߵ�ƽ
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;	//����ͬ��ʱ�ӵĵڶ��������أ��������½������ݱ�����
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS�ź���Ӳ����NSS�ܽţ����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ����
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;		//���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ256
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ
    SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRCֵ����Ķ���ʽ
    SPI_Init(SPI2, &SPI_InitStructure);  //����SPI_InitStruct��ָ���Ĳ�����ʼ������SPIx�Ĵ���
   
   
//    SPI_NSSInternalSoftwareConfig(SPI2,SPI_NSSInternalSoft_Reset);
    SPI_Cmd(SPI2, ENABLE); //ʹ��SPI����	 
  
 
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
      while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET){ //���ָ����SPI��־λ�������:���ͻ���ձ�־λ
          retry++;
//          if(retry>2000)return 0;
      }	
      
      SPI_SendData8(SPI2, data[i]); //ͨ������SPIx����һ������
//#define SPI2_8Data ((uint32_t)SPI2 +  0x0c)
//  
//      *(__IO uint8_t *) SPI2_8Data = data[i];
   }
  
}


/*�ȴ�������� ����ˢ����Ļ�������׳�������*/
void xOLED_Itf_WaitTransFinish( void ){
    u16 retry=0;
    while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET){ //���ָ����SPI��־λ�������:���ͻ���ձ�־λ
         retry++;
        if(retry>10000)
        return ;
    }
}

