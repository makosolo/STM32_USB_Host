#include <string.h>

#include "stm32f2xx.h"

#include "main.h"
#include "sys.h"
#include "usart.h"

#include "menu.h"

char over=0; //结束标志

//==================================== 
//结构体声明 
struct MenuItem m0_main[2];
struct MenuItem m1_USART[2]; 
struct MenuItem m1_Flash_Disk[2];

//函数声明 
void Nop(void);
void Run(struct MenuItem *manyou);
void USART_IAP(void);//串口操作函数
void IAP_FROM_Flash_Disk(void);//U盘升级系统
void IAP_FROM_Font_Disk(void);//U盘升级字库

//==================================== 
//结构体实现 
struct MenuItem m0_main[2]= 
{ 
	{1,120,123,"1 USART Drive       ",Nop,m1_USART,Null}, 
	{1,120,171,"2 Generic Flash Disk",Nop,m1_Flash_Disk,Null},
};

struct MenuItem m1_USART[2]= 
{ 
	{2,120,123,"1 System Upgrade",USART_IAP,Null,m0_main}, 
	{2,120,171,"2 Fort Upgrade  ",USART_IAP,Null,m0_main}, 
};

struct MenuItem m1_Flash_Disk[2]= 
{ 
	{2,120,123,"1 System Upgrade",IAP_FROM_Flash_Disk,Null,m0_main}, 
	{2,120,171,"2 Fort Upgrade  ",IAP_FROM_Font_Disk,Null,m0_main},
};

//==================================== 
void Run(struct MenuItem *currentMenu) 
{ 
	(*(currentMenu->Subs))(currentMenu);
}

void Nop(void) 
{}

void USART_IAP(void)//串口操作函数
{
	while(1)//等待上位机发送命令
	{
		if(rcv_frame_r == 1)
		{
			if(strcmp((char*)receive_r, "$07*") == 0)//【★注★意★这★里★】
			{
				RTC_WriteBackupRegister(UPDATA_RTC_BKP, IAP_FROM_USART);//写入IAP约定标识
				SystemReset();//复位系统
			}
			
			if(strcmp((char*)receive_r, "$TS*") == 0)//【下载程序字库到FLASH】
			{	
				RTC_WriteBackupRegister(UPDATA_RTC_BKP, IAP_Font_USART);//写入IAP约定标识
				SystemReset();//复位系统
			}			
		}
	}
}

void IAP_FROM_Flash_Disk(void)
{
	RTC_WriteBackupRegister(UPDATA_RTC_BKP, IAP_FROM_USB_Flash_Disk);//写入IAP约定标识
	SystemReset();//复位系统
}

void IAP_FROM_Font_Disk(void)
{
	RTC_WriteBackupRegister(UPDATA_RTC_BKP, IAP_Font_USB_Flash_Disk);//写入IAP约定标识
	SystemReset();//复位系统	
}
