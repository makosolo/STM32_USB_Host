#ifndef __MENU_H
#define __MENU_H	

#define Null 0

//结构体类型定义 
struct MenuItem     
{
//	char range_max,range_min; //当前显示的项开始及结束序号
	char MenuCount; //结构体数组的元素个数
//	char selected;//当前先选中项
	char x,y;//显示串的位置
	char *DisplayString;//当前LCD显示的信息
	void (*Subs)();  //执行的函数的指针. 
	struct MenuItem *Childrenms;  //指向子节点的指针 
	struct MenuItem *Parentms;  //指向父节点的指针 
}; 

//==================================== 
//结构体声明 
extern struct MenuItem m0_main[2];
extern struct MenuItem m1_USART[2]; 
extern struct MenuItem m1_Flash_Disk[2];

void Run(struct MenuItem *currentMenu);

#endif//__MENU_H
