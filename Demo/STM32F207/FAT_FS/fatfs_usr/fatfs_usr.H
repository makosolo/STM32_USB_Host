#ifndef __FATFS_USR_H
#define __FATFS_USR_H	

extern FATFS FS;	    //文件系统对象结构体
extern FIL fsr,fsw;   	//文件对象结构
//extern FILINFO fileinfo;//文件信息
//extern DIR dir;  		//目录
extern FRESULT FAT_flag;//文件函数的返回码

#endif//__FATFS_USR_H
