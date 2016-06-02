#include "sys.h"

#include "HW_Init.h"

/*******************************************************************************
* 函数名	: NVIC_Configuration
* 描述  	: 中断配置
* 参数  	: 无
* 返回值	: 无
*******************************************************************************/
void NVIC_Configuration(void)
{
	//设置中断向量表在Flash里，偏移量是C000H(32Kb,bootloader占用28K)(偏移量必须是100H的整数倍)重新映射中断向量表(在开启任一中断之前执行)
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0000);//BootLoader中中断向量在0处，主程序在0x8000(32Kb)
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//只有0-15的先占优先级
}

/*******************************************************************************
* 函数名	: HW_Init
* 描述  	: 硬件初始化
* 参数  	: 无
* 返回值	: 无
*******************************************************************************/
void HW_Init(void)
{    	
	NVIC_Configuration();    //中断分组
	uart5_init(115200);		 //	
	SPI1_FLASH_Init();
	LED_Init();              //LED初始化
	KEY_Init();              //按键初始化
	USBH_Init(&USB_OTG_Core, USB_OTG_FS_CORE_ID, &USB_Host, &USBH_MSC_cb, &USR_cb);//USB初始化
    
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR , ENABLE);//使能PWR和BKP外设时钟 
	PWR_BackupAccessCmd(ENABLE);//使能后备寄存器访问
}
