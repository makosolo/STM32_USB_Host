#include "stm32f2xx.h"

#include "integer.h"
#include "fattime.h"

DWORD get_fattime (void)
{
//	u32 ttime;
	u32 date=0;
//	RTC_HEX t;
//    
//	xQueueReceive(xQueueHandle_Sys_time, &t, 1000);//获取不到，等待1s
//	
//    ttime = HEX2BCD(t.year)-1984;	 //得到年份
// 	date |= (ttime<<25);
//    ttime = HEX2BCD(t.mon);	 //得到月份
// 	date |= (ttime<<21);
//	ttime = HEX2BCD(t.day);	  	 //得到日期
// 	date |= (ttime<<16);
//	ttime = HEX2BCD(t.hour);  	 //得到时钟
// 	date |= (ttime<<11);
//	ttime = HEX2BCD(t.min);	 //得到分钟
// 	date |= (ttime<<5);
// 	date |= (HEX2BCD(t.sec)/2);//得到秒钟	
	
    return date;
}
