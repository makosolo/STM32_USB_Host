/**
  ******************************************************************************
  * @file    usbh_usr.c
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    09-November-2015
  * @brief   This file includes the usb host library user callbacks
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "sys.h"

#include "usb_conf.h"
#include "usbh_msc_core.h"

#include "ff.h"
#include "fatfs_usr.h"

#include "usbh_usr.h"

#define NULL 0

USB_OTG_CORE_HANDLE      USB_OTG_Core;
USBH_HOST                USB_Host;
USB_OTG_CORE_HANDLE  USB_OTG_Core_dev; 

static vu8 AppState = USH_USR_FS_INIT;
_usb_app usbx;//USB状态控制器

//USB回调函数表，顺序执行
//实现方式OTG_FS_IRQHandler，枚举成功后一直执行USBH_USR_MSC_Application
USBH_Usr_cb_TypeDef USR_cb =
{
  USBH_USR_Init,						//初始化
  USBH_USR_DeInit,
  USBH_USR_DeviceAttached,				//检测到有USB设备插入
  USBH_USR_ResetDevice,					//重置设备
  USBH_USR_DeviceDisconnected,			//检测到有设备移除
  USBH_USR_OverCurrentDetected,
  USBH_USR_DeviceSpeedDetected,			//检测设备速度，例如高速、全速、低速
  USBH_USR_Device_DescAvailable,		//设备信息
  USBH_USR_DeviceAddressAssigned,	   	//分配地址成功
  USBH_USR_Configuration_DescAvailable,	//配置描述
  USBH_USR_Manufacturer_String,		  	//厂商信息（字符串）
  USBH_USR_Product_String,			  	//产品信息（字符串）
  USBH_USR_SerialNum_String,		   	//设备串号
  USBH_USR_EnumerationDone,			  	//枚举完成
  USBH_USR_UserInput,					//用户操作应用程序状态条目
  USBH_USR_MSC_Application,				//USB应用操作
  USBH_USR_DeviceNotSupported,			//设备不支持
  USBH_USR_UnrecoveredError 
};

/** @defgroup USBH_USR_Private_Functions
* @{
*/ 

void USBH_USR_Init(void){}//可以初始化一些东西

void USBH_USR_DeviceAttached(void)//检测到有USB设备插入
{	
	usbx.status = HOST_USER_CONNECTION;//检测到USB设备，减小空闲时间
	LCD_UsrLog("USB设备连接\r\n");
}

//无法恢复的错误!!  	
void USBH_USR_UnrecoveredError (void)//
{
	LCD_UsrLog("无法恢复的错误!!!\r\n\r\n");
}

void USBH_USR_DeviceDisconnected (void)//检测到有设备移除
{
    //设备移除，加大空闲时间
    usbx.status = 0;//连接状态
    usbx.fun = 0;//功能
    
    AppState = USH_USR_FS_INIT;
    
	f_mount(0 , NULL);//注销工作区
	
	LCD_UsrLog("设备已经移除\r\n");
}

void USBH_USR_ResetDevice(void)//重置驱动
{
  /* callback for USB-Reset */
	LCD_UsrLog("复位设备...\r\n");
}

void USBH_USR_DeviceSpeedDetected(uint8_t DeviceSpeed)//检测速度？？
{
  if(DeviceSpeed == HPRT0_PRTSPD_HIGH_SPEED)
  {
	  LCD_UsrLog("高速\r\n");
  }  
  else if(DeviceSpeed == HPRT0_PRTSPD_FULL_SPEED)
  {
	  LCD_UsrLog("全速\r\n");
  }
  else if(DeviceSpeed == HPRT0_PRTSPD_LOW_SPEED)
  {
	  LCD_UsrLog("低速\r\n");
  }
  else
  {
	  LCD_UsrLog("设备错误\r\n");
  }
}

void USBH_USR_Device_DescAvailable(void *DeviceDesc)//设备信息
{ 
  USBH_DevDesc_TypeDef *hs;
  hs = DeviceDesc;  
  
  LCD_UsrLog("VID : %04Xh\r\n" , (uint32_t)(*hs).idVendor); 
  LCD_UsrLog("PID : %04Xh\r\n" , (uint32_t)(*hs).idProduct);
}

void USBH_USR_DeviceAddressAssigned(void)//分配地址成功
{
  LCD_UsrLog("设备地址分配成功\r\n");
}

void USBH_USR_Configuration_DescAvailable(USBH_CfgDesc_TypeDef * cfgDesc, 	  //配置描述
										  USBH_InterfaceDesc_TypeDef *itfDesc, 
										  USBH_EpDesc_TypeDef *epDesc)
{
	USBH_InterfaceDesc_TypeDef *id; 
	id = itfDesc;   
	if((*id).bInterfaceClass==0x08)
	{
		LCD_UsrLog("可移动存储器设备!\r\n"); 
	}else if((*id).bInterfaceClass==0x03)
	{
		LCD_UsrLog("HID 设备!\r\n"); 
	} 
}

//厂商（字符串）信息                                          
void USBH_USR_Manufacturer_String(void *ManufacturerString)
{
  LCD_UsrLog("Manufacturer : %s\r\n", (char *)ManufacturerString);
}

//产品信息（字符串）
void USBH_USR_Product_String(void *ProductString)
{
  LCD_UsrLog("Product : %s\r\n", (char *)ProductString);
}

//设备串号
void USBH_USR_SerialNum_String(void *SerialNumString)
{
  LCD_UsrLog( "Serial Number : %s\r\n", (char *)SerialNumString); 
}

void USBH_USR_EnumerationDone(void)//枚举完成
{
  LCD_UsrLog("枚举完成\r\n");
}

//无法识别的USB设备
void USBH_USR_DeviceNotSupported(void)
{	
  LCD_ErrLog("设备不支持\r\n");
}  

//等待用户输入按键,执行下一步操作
USBH_USR_Status USBH_USR_UserInput(void)//跳过
{
  return USBH_USR_RESP_OK;
}  

//USB接口电流过载
void USBH_USR_OverCurrentDetected (void)
{
	LCD_ErrLog("端口电流过大!!!\r\n");
}


FIL *fpr;//文件对象结构的指针

int USBH_USR_MSC_Application(void)//应用操作
{    
	fpr = &fsr;
	
	switch(AppState)
	{
		case USH_USR_FS_INIT://初始化，注册FATFS工作区
		{
            usbx.status = HOST_USER_CLASS_ACTIVE;//连接状态
            
			FAT_flag = f_mount(0 , &FS);//注册设备
			
			if(FAT_flag != 0)
			{
				USART_send_srt("f_mount err：%d");
				USART_sendHEX(FAT_flag);
				USART_send_srt("\r\n");
				return 0;
			}
			
			USART_send_srt("U盘正常连接\r\n");

			AppState = USH_USR_FS_READLIST;//跳转到下一步
		}break;

		case USH_USR_FS_READLIST://读取列表，打开/创建文件
		{
            AppState = USH_USR_FS_WRITEFILE;
		}break;
		
		case USH_USR_FS_WRITEFILE://写入文件
		{
            AppState = USH_USR_FS_READLIST;
		}break;
		
		default: break;
	}
		
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////
//USB枚举状态死机检测,防止USB枚举失败导致的死机
//phost:USB_HOST结构体指针
//返回值:0,没有死机
//       1,死机了,外部必须重新启动USB连接.
u8 USBH_Check_EnumeDead(USBH_HOST *phost)
{
	static u16 errcnt=0;
	//这个状态,如果持续存在,则说明USB死机了.
	if(phost->gState==HOST_CTRL_XFER&&(phost->EnumState==ENUM_IDLE||phost->EnumState==ENUM_GET_FULL_DEV_DESC))
	{
		errcnt++;
		if(errcnt>2000)//死机了
		{ 
			errcnt=0;
			RCC->AHB2RSTR|=1<<7;	//USB OTG FS 复位
			USB_OTG_BSP_mDelay(5);
			RCC->AHB2RSTR&=~(1<<7);	//复位结束  
			return 1;
		} 
	}else errcnt=0;
	return 0;
} 

void USBH_USR_DeInit(void)
{
  AppState = USH_USR_FS_INIT;
}
