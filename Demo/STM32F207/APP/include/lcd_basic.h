#ifndef __LCD_BASIC_H
#define __LCD_BASIC_H

void LCD_Fastlines(u16 x,u16 y,u16 len,u8 direction);		   //快速画线函数，给出初始坐标，指定长度画一条横线或竖线
void LCD_Fast_Brokenlines(u16 x, u16 y, u16 len, u8 direction);//快速画虚线函数，给出初始坐标，指定长度画一条横虚线或竖虚线
void LCD_Line(u16 x1,u16 y1,u16 x2,u16 y2);			 		   //通用画线函数，向LCD指定起始坐标和结束坐标之间画一条指定颜色的直线
void LCD_DrawRectangle(u16 x1,u16 y1,u16 x2,u16 y2); 		   //向LCD指定起始坐标和结束坐标之间画一个指定颜色的矩形

#endif//__LCD_BASIC_H
