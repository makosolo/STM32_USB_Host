#ifndef _LCD_H_
#define _LCD_H_

extern u16 POINT_COLOR;//画笔颜色

//画笔颜色
//#define WHITE         	 0xFFFF
//#define BLACK         	 0x0000	  
//#define BLUE         	 0x001F  
//#define BRED             0XF81F
//#define GRED 			 0XFFE0
//#define GBLUE			 0X07FF
//#define RED           	 0xF800
//#define MAGENTA       	 0xF81F
//#define GREEN         	 0x07E0
//#define CYAN          	 0x7FFF
//#define YELLOW        	 0xFFE0
//#define BROWN 			 0XBC40 //棕色
//#define BRRED 			 0XFC07 //棕红色
//#define GRAY  			 0X8430 //灰色

#define WHITE         	 0xFFFF
#define BLACK         	 0x0000
#define BLUE         	 0xF800//0x001F
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0x001F
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //棕色
#define BRRED 			 0XFC07 //棕红色
#define GRAY  			 0X8430 //灰色

void LCD_Init(void);

u16 LCD_ReadReg(u8 LCD_Reg);
void LCD_Clear_Color(u16 color);//清屏
void LCD_Clear(u16 color);//清屏函数
void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color);//块填充函数
void LCD_DrawPoint(u16 x,u16 y);//画点函数
void Refurbish_LCD(void *tp);//刷屏函数
u16 LCD_ReadPoint(u16 x, u16 y);//读点函数
void BlockWrite(u16 sx,u16 sy,u16 ex,u16 ey,u16 color);//手动块填充
void Manual_Refurbish_LCD(void);//手动刷新
void Manual_LCD_Fill(u16 sx, u16 sy, u16 ex, u16 ey, u16 color);

#endif//_LCD_H_
