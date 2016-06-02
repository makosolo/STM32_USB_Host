#include "sys.h"
#include "HW_Init.h"

int main(void)
{
	HW_Init();
	
	while(1)
    {
        LED1 = 0;//点亮
        
        //检测U盘
        USBH_Process(&USB_OTG_Core, &USB_Host);//处理USB事务
        
        while(usbx.status == HOST_USER_CONNECTION)//检测得到USB设备，但还未连接成功
        {
            USBH_Process(&USB_OTG_Core, &USB_Host);//处理USB事务

            if(USBH_Check_EnumeDead(&USB_Host))	//检测USB HOST 是否死机了?死机了,则重新初始化
            { 	    
                USBH_Init(&USB_OTG_Core, USB_OTG_FS_CORE_ID, &USB_Host, &USBH_MSC_cb, &USR_cb);//USB初始化
            }
        }
	}
}

