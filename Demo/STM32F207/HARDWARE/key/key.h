#ifndef __KEY_H
#define __KEY_H	 

//USART1 mode 高电平有效
//#define U1_MOD		   (GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_15))//按下WK_UP键系统升级
//#define U2_MOD		   (GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_13))//按下WK_UP键系统升级

#define KEY6  (GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_15))//读取按键6【exit】
#define KEY5  (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)) //读取按键5【ok】
#define KEY4  (GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_14))//读取按键4【↓】 
#define KEY3  (GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_12))//读取按键3【↑】
#define KEY2  (GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_11))//读取按键2【→】 
#define KEY1  (GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_13))//读取按键1【←】 

#define UP 	  3
#define Down  4
#define Left  1
#define Right 2
#define Enter 5
#define Esc   6
#define Reset 7

void KEY_Init(void); //按键初始化
//u8 KEY_Scan(u8 mode);//按键扫描函数

#endif
