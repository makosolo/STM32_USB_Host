#include "stm32f2xx.h"

#include "flash.h" 

#define  Dummy_byte 0xAA

#define	CS_0    GPIO_ResetBits(GPIOA, GPIO_Pin_4);
#define	CS_1    GPIO_SetBits(GPIOA, GPIO_Pin_4);

u16 W25QXX_TYPE = W25Q64;	//默认是W25Q64

//函数声明
void SPI_Flash_Wait_Busy(void);

/*******************************************************************************
* 函数名	: SPI1_FLASH_Init
* 描述  	: SPI1接口初始化
* 参数  	: 无
* 返回值	: 无
*******************************************************************************/
void SPI1_FLASH_Init(void)
{
	SPI_InitTypeDef  SPI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);//使能APB2外设时钟
			
	/* Enable SPI1 and GPIO clocks */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1 , ENABLE);
	
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_SPI1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_SPI1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_SPI1);
    
	/* Configure SPI1 pins: CS */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//推挽复用
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
    
	/* Configure SPI1 pins: SCK, MISO and MOSI */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//推挽复用
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Deselect the FLASH: Chip Select high */
	GPIO_SetBits(GPIOA, GPIO_Pin_4);//CS=1；
	
	/* SPI1 configuration */
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;//全双工
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;					  //主模式
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;				  //8bit
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;						  //CS由软件控制
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;//预分频2:36MHz
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;				  //首位为最高位
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(SPI1, &SPI_InitStructure);
	
	/* Enable SPI1  */
	SPI_Cmd(SPI1, ENABLE);
}

/*******************************************************************************
* 函数名	: SPI1_ReadWriteByte
* 描述  	: SPI1读写函数
* 参数  	: dat:要写入的数据
* 返回值	: 读取到的字节
*******************************************************************************/
u8 SPI1_ReadWriteByte(u8 dat)
{		
	u8 r;	
	
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	
	SPI_I2S_SendData(SPI1, dat); //通过外设SPIx发送一个数据

	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
		
	r = SPI_I2S_ReceiveData(SPI1);
	
	return(r);			    
}

/*******************************************************************************
* 函数名	: SPI_Flash_ReadSR
* 描述  	: 读取SPI_FLASH的状态寄存器
* 参数  	: 无
* 返回值	: //BIT7  6   5   4   3   2   1   0
*				SPR   RV  TB BP2 BP1 BP0 WEL BUSY
*				SPR:默认0,状态寄存器保护位,配合WP使用
*				TB,BP2,BP1,BP0:FLASH区域写保护设置
*				WEL:写使能锁定
*				BUSY:忙标记位(1,忙;0,空闲)
*				默认:0x00
*******************************************************************************/
u8 SPI_Flash_ReadSR(void)   
{  
	u8 r = 0;   
	
	CS_0
	
	SPI1_ReadWriteByte(W25X_ReadStatusReg);    //发送读取状态寄存器命令    
	r = SPI1_ReadWriteByte(Dummy_byte);        //读取一个字节  
	
	CS_1
	
	return(r);   
} 

/*******************************************************************************
* 函数名	: SPI_FLASH_Write_Enable
* 描述  	: SPI_FLASH写使能
* 参数  	: 无
* 返回值	: 无
*******************************************************************************/
void SPI_FLASH_Write_Enable(void)   
{
	CS_0
	
    SPI1_ReadWriteByte(W25X_WriteEnable);      //发送写使能  
	
	CS_1
} 

/*******************************************************************************
* 函数名	: SPI_Flash_ReadID
* 描述  	: 读取芯片ID
* 参数  	: 无
* 返回值	: 芯片ID
*******************************************************************************/
//u16 SPI_Flash_ReadID(void)
//{
//	u16 ID = 0;	 
//	 
//	CS_0	
//		    
//	SPI1_ReadWriteByte(0x90);//发送读取ID命令	    
//	SPI1_ReadWriteByte(0x00); 	    
//	SPI1_ReadWriteByte(0x00); 	    
//	SPI1_ReadWriteByte(0x00); 	 			   
//	ID |= SPI1_ReadWriteByte(Dummy_byte)<<8;  
//	ID |= SPI1_ReadWriteByte(Dummy_byte);	 

//	CS_1
//			    
//	return(ID);
//}   	

/*******************************************************************************
* 函数名	: SPI_Flash_Read
* 描述  	: 读数据(最大65535)
* 参数  	: -buf:数据缓存区指针
*			  -add:数据地址
*			  -len:读取长度
* 返回值	: 无
*******************************************************************************/
//void SPI_Flash_Read(u8* buf, u32 add,u16 len)   
//{ 
// 	u16 i;   
//	 												    
//	CS_0

//    SPI1_ReadWriteByte(W25X_ReadData);    //发送读取命令   
//	
//    SPI1_ReadWriteByte((u8)((add)>>16));  //发送24bit地址    
//    SPI1_ReadWriteByte((u8)((add)>>8));   
//    SPI1_ReadWriteByte((u8)add);   
//	
//    for(i=0;i<len;i++)
//	{ 
//        buf[i] = SPI1_ReadWriteByte(Dummy_byte);   //循环读数  
//    }

//	CS_1	      
//}  

/*******************************************************************************
* 函数名	: SPI_Flash_Write_Page
* 描述  	: SPI在一页(0~65535)内写入少于256个字节的数据
* 参数  	: -buf:数据缓存区指针
*			  -add:数据地址
*			  -len:写入长度
* 返回值	: 无
*******************************************************************************/
void SPI_Flash_Write_Page(u8* buf, u32 add, u16 len)
{
 	u16 i;  
	
    SPI_FLASH_Write_Enable();         
	
	CS_0
	   
    SPI1_ReadWriteByte(W25X_PageProgram); //发送写页命令   
	
    SPI1_ReadWriteByte((u8)((add)>>16)); //发送24bit地址    
    SPI1_ReadWriteByte((u8)((add)>>8));   
    SPI1_ReadWriteByte((u8)add);   
	
    for(i=0;i<len;i++)
	{
		SPI1_ReadWriteByte(buf[i]);//循环写数  
	}
	
	CS_1
	
	SPI_Flash_Wait_Busy();					   //等待写入结束
} 

/*******************************************************************************
* 函数名	: SPI_Flash_Write
* 描述  	: 无检验写SPI FLASH 
* 参数  	: -buf:数据缓存区指针
*			  -add:数据地址
*			  -len:写入长度
* 返回值	: 无
*******************************************************************************/
void SPI_Flash_Write(u8* buf, u32 add, u16 len)   
{ 			 		 
	u16 start;
		   
	start = 256 - (add & 255); //单页剩余的字节数
			 	    
	if(len <= start)
	{
		start = len;//不大于256个字节
	}
	
	while(1)
	{	   
		SPI_Flash_Write_Page(buf, add, start);
		
		if(len == start)
		{
			break;
		}
	 	else
		{
			buf += start;
			add += start;	

			len -= start;		
			
			if(len > 256)
			{
				start = 256;
			}
			else
			{
				start = len; 	  //不够256个字节了
			}
		}
	}    
} 

/*******************************************************************************
* 函数名	: SPI_Flash_Erase_Chip
* 描述  	: 擦除整个芯片,等待时间超长...
* 参数  	: 无
* 返回值	: 无
*******************************************************************************/
//void SPI_Flash_Erase_Chip(void)   
//{                                             
//    SPI_FLASH_Write_Enable();                  //SET WEL 
//    SPI_Flash_Wait_Busy();   

//	CS_0

//    SPI1_ReadWriteByte(W25X_ChipErase);        //发送片擦除命令  

//	CS_1
//      
//	SPI_Flash_Wait_Busy();   				   //等待芯片擦除结束
//}

/*******************************************************************************
* 函数名	: SPI_Flash_Erase_Sector
* 描述  	: 擦除一个扇区:150ms
* 参数  	: Dst_Addr:扇区地址
* 返回值	: 无
*******************************************************************************/
void SPI_Flash_Erase_Sector(u32 Dst_Addr)   
{   
    SPI_FLASH_Write_Enable();                  //SET WEL 	 
    SPI_Flash_Wait_Busy();   

	CS_0

    SPI1_ReadWriteByte(W25X_SectorErase);      //发送扇区擦除指令 
	
    SPI1_ReadWriteByte((u8)((Dst_Addr)>>16));  //发送24bit地址    
    SPI1_ReadWriteByte((u8)((Dst_Addr)>>8));   
    SPI1_ReadWriteByte((u8)Dst_Addr);  

	CS_1

    SPI_Flash_Wait_Busy();   				   //等待擦除完成
} 
 
/*******************************************************************************
* 函数名	: SPI_Flash_Wait_Busy
* 描述  	: 等待空闲
* 参数  	: 无
* 返回值	: 无
*******************************************************************************/
void SPI_Flash_Wait_Busy(void)   
{   
	while((SPI_Flash_ReadSR()&0x01) == 0x01);   // 等待BUSY位清空
}  

/*******************************************************************************
* 函数名	: SPI_Flash_Write_Data
* 描述  	: 把采集数据写入FLASH，只能向前写
* 参数  	: -buf:数据存储区
*			  -add:开始写入的地址(24bit)
*			  -len:要写入的字节数
* 返回值	: 无
*******************************************************************************/
//void SPI_Flash_Write_Data(u8 *buf, u32 add, u16 len)
//{
//    u16 Residue;	//剩余大小
//	u32 Erasure_Add;//要擦除的扇区地址，范围：
//	
//	Residue = 4096-(add&4095);//把要写的地址取余4kb（一个扇区），计算出跨扇区的剩余大小；4095的二进制：1111 1111 1111，add&4095 == add%4096
//		
//	if(Residue < len)//如果扇区剩余大小小于要写入的数据长度（即将会出现跨扇区写数据），必须先擦掉下一个扇区
//	{		
//		Erasure_Add = (add&0xFFFFF000) + 4096;//擦除的下一个扇区
//		SPI_Flash_Erase_Sector(Erasure_Add);
//		
////		printf(">>>>>>>>擦除扇区:%X\r\n",Erasure_Add);
//	}
//	else if(Residue == 4096)//如果在一个扇区的起始地址上
//	{		
//		SPI_Flash_Erase_Sector(add);//擦除当前扇区
//		
////		printf("********擦除扇区:%X\r\n",add);
//	}
//	
//	SPI_Flash_Write(buf, add, len);
//}
