//#include "stm32f2xx.h"

#include "ff.h"
#include "fatfs_usr.h"

FATFS FS;	     //文件系统对象结构体
FIL fsr,fsw;   	 //文件对象结构
//FILINFO fileinfo;//文件信息
//DIR dir;  		 //目录
FRESULT FAT_flag;//文件函数的返回码

#if 0
/*******************************************************************************
* 函数名	: getfree
* 描述  	: -得到磁盘剩余容量
* 参数  	: -drv  :磁盘编号("0:"/"1:")
*			  -total:总容量
*			  -free :剩余容量
* 返回值	: 0,正常；其他,错误代码
*******************************************************************************/
u8 getfree(u8 *drv,u32 *total,u32 *free)//获取空闲簇
{
	FATFS *fs;
	u8 res;
    DWORD fre_clust=0, fre_sect=0, tot_sect=0;
	
	res = f_getfree((const TCHAR*)drv, &fre_clust, &fs);//"0:" or "" , 返回结果, **FATFS
	if(res == FR_OK)
	{
		tot_sect = (fs->n_fatent - 2) * fs->csize;//总扇区=簇数*每簇扇区数
		fre_sect = fre_clust * fs->csize;         //空闲扇区=空闲簇*每簇扇区数

		*total=tot_sect>>1;	//单位为KB
		*free=fre_sect>>1;	//单位为KB 
		
		printf("%lu KB total drive space.\n"
			   "%lu KB available.\n",
			   *total / 2,*free / 2);//每扇区512字节，扇区数*0.5K = 总K数
	}
	
	return res;
}
#endif
