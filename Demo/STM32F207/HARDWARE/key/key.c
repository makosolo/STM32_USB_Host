#include "stm32f2xx.h"

#include "delay.h"
#include "key.h"

//按键初始化函数
void KEY_Init(void) //IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
    
	//初始化KEY0-->GPIOA.13,KEY1-->GPIOA.15  上拉输入
 	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG | RCC_AHB1Periph_GPIOE, ENABLE);//使能PORTA,PORTE时钟

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//输入输出设置，输入/输出/复用/模拟
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//输入模式，上拉
	GPIO_InitStructure.GPIO_Pin  =  GPIO_Pin_13 | GPIO_Pin_15;//PG12、PG13
 	GPIO_Init(GPIOG, &GPIO_InitStructure);//初始化GPIOG13、15
}
//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//0，没有任何按键按下
//1，S1按下
//2，S2按下
//3，S3按下 
//4，S4按下
//5，S5按下
//6，S6按下 
//注意此函数有响应优先级,S1>S2>S3>S4>S5>S6!!
/*u8 KEY_Scan(u8 mode)
{	
	static u8 key_up = 1;//按键按松开标志
	static u8 key_cnt = 0;
	static u8 key_value;

	Delay_ms(5);
	
	if(key_up == 1)
	{
		key_value = 0;
	}
	
	if(mode && (key_cnt++ >= 50))//支持连按
	{
		key_up = 1;
		key_cnt = 50;
	}
	
	if((KEY6 == 0) && (KEY1 == 0))//组合按键
	{
		key_value = 7;
		goto END;//直接返回按键值
	}	

	if((KEY6 == 0) && (KEY2 == 0))//组合按键
	{
		key_value = 8;
		goto END;//直接返回按键值
	}
	
	if(key_up && (KEY1==0 || KEY2==0 || KEY3==0 || KEY4==0 || KEY5==0 || KEY6==0))
	{
		Delay_ms(5);//去抖动 
		
		if(mode == 1)
		{
			key_up = 0;
			
			if     (KEY1 == 0) return 1;
			else if(KEY2 == 0) return 2;
			else if(KEY3 == 0) return 3;
			else if(KEY4 == 0) return 4;
			else if(KEY5 == 0) return 5;
			else if(KEY6 == 0) return 6;
		}
		else
		{
			key_up = 0;

			if     (KEY1 == 0) key_value = 1;
			else if(KEY2 == 0) key_value = 2;
			else if(KEY3 == 0) key_value = 3;
			else if(KEY4 == 0) key_value = 4;
			else if(KEY5 == 0) key_value = 5;
			else if(KEY6 == 0) key_value = 6;
		}			
	}
	else if(KEY1==1 && KEY2==1 && KEY3==1 && KEY4==1 && KEY5==1 && KEY6==1)
	{
		END:
		
		key_up = 1;
		key_cnt = 0;
		
		return key_value;
	}

	return 0;// 无按键按下
}*/
