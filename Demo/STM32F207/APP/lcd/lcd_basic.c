#include "stm32f2xx.h"

#include "lcd.h"
#include "lcd_basic.h"

/*******************************************************************************
* 函数名	: LCD_Fastlines
* 描述  	: 快速画线函数
* 参数  	: -    x    :x轴坐标
*			  -    y    :y轴坐标
*			  -   len   :长度
*			  -direction:方向；0，画横线；1，画竖线；
* 返回值	: 无
*******************************************************************************/
void LCD_Fastlines(u16 x,u16 y,u16 len,u8 direction)
{
	u16 i;
	
	if(direction == 0)
	{
		if((x+len) > 480) return;	//超出屏幕范围则退出
		
		for(i=0;i<len;i++)
		{
		 	LCD_DrawPoint(x+i, y);
		}
	}
	else if(direction==1)
	{
		if((y+len) > 320) return;	//超出屏幕范围则退出
		
		for(i=0;i<len;i++)
		{
		 	LCD_DrawPoint(x, y+i);
		}
	}
}

/*******************************************************************************
* 函数名	: LCD_Fast_Brokenlines
* 描述  	: 快速画虚线函数
* 参数  	: -    x    :x轴坐标
*			  -    y    :y轴坐标
*			  -   len   :长度
*			  -interval :间隔
*			  -direction:方向；0，画横线；1，画竖线；
* 返回值	: 无
*******************************************************************************/
void LCD_Horizontal_Dottedlines(u16 x, u16 y, u16 len, u8 interval, u8 direction)//水平画虚线
{
	s16 i;
		
	if(direction == 0)//从左往右
	{
		if((x+len) > 480) return;	//超出屏幕范围则退出
		
		for(i=0;i<len;i+=interval)
		{
		 	LCD_DrawPoint(x+i, y);
		}
	}
	else if(direction == 1)//从右往左
	{
		if((x-(len-1)) < 0) return;	//超出屏幕范围则退出
		
		for(i=x;i>x-(len-1);i-=interval)
		{
		 	LCD_DrawPoint(i, y);
		}
	}
}

void LCD_Vertical_Dottedlines(u16 x, u16 y, u16 len, u8 interval, u8 direction)//垂直画虚线
{
	s16 i;
		
	if(direction == 0)//从上往下
	{
		if((y+len) > 320) return;//超出屏幕范围则退出
		
		for(i=0;i<len;i+=interval)
		{
		 	LCD_DrawPoint(x, y+i);
		}
	}
	else if(direction == 1)//从下往上
	{
		if((y-len) < 0) return;//超出屏幕范围则退出
		
		for(i=y;i>y-(len-1);i-=interval)
		{
		 	LCD_DrawPoint(x, i);
		}
	}
}

/*******************************************************************************
* 函数名	: LCD_Line
* 描述  	: 通用画线函数，两点画线
* 参数  	: -x1:x1轴坐标
*			  -y1:y1轴坐标
*			  -x2:x2轴坐标
*			  -y2:y2轴坐标
* 返回值	: 无
*******************************************************************************/
void LCD_Line(u16 x1,u16 y1,u16 x2,u16 y2)
{
	unsigned int x,y; 
	unsigned int d_x,d_y;//d_x=x2-x1;d_y=y2-y1;
	int err=0;
	unsigned char temp=0;
	
	POINT_COLOR=WHITE;
	if(((x1>480)&&(x2>480))&&((y1>320)&&(y2>320))) return;	//超出屏幕范围则退出
	if(y2<y1)
	{
		x=x1;
		y=y1;
		x1=x2;
		y1=y2;
		x2=x;
		y2=y;
	}
	d_y=y2-y1; 			//两点间绝对距离
	if (d_y==0)			//当两点的X坐标不相等，Y坐标相等时，画一条水平线
	{
		if (x1>x2) 
		{
			x=x1;
			x1=x2;
			x2=x;
		}
		for (x=x1;x<=x2;x++) 
			LCD_DrawPoint(x,y1);
	}

	else			   //
	{
		if(x2>=x1)
		{
			temp=1;
			d_x=x2-x1;
		}
		else 
			d_x=x1-x2;
		x=x1;
		y=y1;
		LCD_DrawPoint(x,y);

		if(temp&&(d_y<=d_x))  //d_y>0,d_x>0,x2>=x1
			while(x!=x2)	  //x1!=x2
			{
				if(err<0)
				{
					x=x+1;
					err=err+(y2-y);
				}
				else 
				{
					x=x+1;
					y=y+1;
					err=err+(y2-y)-(x2-x);//err=err+d_y-d_x
				}
				LCD_DrawPoint(x,y);
			}

		else if(temp&&(d_y>d_x))
			while(y!=y2)
			{
				d_x=x2-x;
				d_y=y2-y; 
				if(err<0)
				{
					x=x+1;
					y=y+1;
					err=err+d_y-d_x;
				}
				else 
				{
					y=y+1;
					err=err-d_x;
				}
				LCD_DrawPoint(x,y);

			}

		else if(!temp&&(d_y<=d_x))
			while(x!=x2)
			{
				d_x=x-x2;
				d_y=y2-y; 
				if(err<0)
				{
					x=x-1;
					err=err+d_y;
				}
				else 
				{
					x=x-1;
					y=y+1;
					err=err+d_y-d_x;
				}
				LCD_DrawPoint(x,y);
			}

		else if(!temp &&(d_y>d_x))
			while(y!=y2)
			{
				d_x=x-x2;
				d_y=y2-y; 
				if(err<0)
				{
					x=x-1;
					y=y+1;
					err=err+d_y-d_x;
				}
				else 
				{
					y=y+1;
					err=err-d_x;
				}
				LCD_DrawPoint(x,y);
			}
	}
}

/*******************************************************************************
* 函数名	: LCD_DrawRectangle
* 描述  	: 画矩形函数
* 参数  	: -x1:x1轴坐标
*			  -y1:y1轴坐标
*			  -x2:x2轴坐标
*			  -y2:y2轴坐标
* 返回值	: 无
*******************************************************************************/
void LCD_DrawRectangle(u16 x1,u16 y1,u16 x2,u16 y2)
{
	unsigned char Temp;
        
	if(x1>x2)
	{
		Temp=x2;
		x2=x1;
		x2=Temp;
	}	
	if(y1>y2)
	{
		Temp=y2;
		y2=y1;
		y1=Temp;
	}
	LCD_Fastlines(x1,y1,x2-x1+1,0);//横线
	LCD_Fastlines(x1,y2,x2-x1+1,0);//横线

	LCD_Fastlines(x1,y1,y2-y1+1,1);//竖线
	LCD_Fastlines(x2,y1,y2-y1+1,1);//竖线
}


