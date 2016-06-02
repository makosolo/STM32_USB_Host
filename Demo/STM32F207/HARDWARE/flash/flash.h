#ifndef __FLASH_H
#define __FLASH_H			    
	 
//#include "sys.h"

//W25X系列/Q系列芯片列表	   
//W25Q80  ID  0XEF13
//W25Q16  ID  0XEF14
//W25Q32  ID  0XEF15
//W25Q64  ID  0XEF16	
//W25Q128 ID  0XEF17	
#define W25Q80 	0XEF13 	
#define W25Q16 	0XEF14
#define W25Q32 	0XEF15
#define W25Q64 	0XEF16
#define W25Q128	0XEF17

#define    W25X_WriteEnable 		0x06 
#define    W25X_WriteDisable		0x04 
#define    W25X_ReadStatusReg		0x05 
#define    W25X_WriteStatusReg		0x01 
#define    W25X_ReadData			0x03 
#define    W25X_FastReadData		0x0B 
#define    W25X_FastReadDual		0x3B 
#define    W25X_PageProgram	    	0x02 
#define    W25X_BlockErase			0xD8 
#define    W25X_SectorErase		    0x20 
#define    W25X_ChipErase			0xC7 
#define    W25X_PowerDown			0xB9 
#define    W25X_ReleasePowerDown	0xAB 
#define    W25X_DeviceID			0xAB 
#define    W25X_ManufactDeviceID	0x90 
#define    W25X_JedecDeviceID		0x9F 

extern u16 W25QXX_TYPE;

void SPI1_FLASH_Init(void);

//u16 SPI_Flash_ReadID(void);//读取芯片ID
//void SPI_Flash_Read(u8* buf, u32 add,u16 len);//读数据
void SPI_Flash_Write(u8* buf, u32 add, u16 len);//无检验写SPI FLASH 
void SPI_Flash_Erase_Chip(void);//擦除整个芯片
void SPI_Flash_Erase_Sector(u32 Dst_Addr);//擦除一个扇区
//void SPI_Flash_Write_Data(u8 *buf, u32 add, u16 len);//把采集数据写入FLASH，只能向前写

#endif
















