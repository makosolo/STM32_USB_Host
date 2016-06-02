#ifndef __USART_H
#define __USART_H

extern unsigned char need_IAP_r;//用来区分串口接收的是bin数据还是IAP命令
extern volatile unsigned char rcv_frame_r;//接收完成标志
extern unsigned char receive[256];//接收缓冲区
extern unsigned char receive_r[256];//接收缓冲区

void USART_send_srt(unsigned char *s);
void USART_sendHEX(unsigned char hex);

void uart5_init(u32 bound);//初始化串口1

void USART_Upgrade_System(void);//串口升级系统
void USART_Upgrade_Fort(void);//串口字库升级

#endif


