#include "sys.h"
#include "stm32f2xx.h"

#include "usart.h"

//struct __FILE 
//{ 
//	int handle; 

//}; 

//FILE __stdout;

////定义_sys_exit()以避免使用半主机模式    
//_sys_exit(int x) 
//{ 
//	x = x; 
//} 

////重定义fputc函数 
//int fputc(int ch, FILE *f)
//{      
//	USART_ClearFlag(UART5, USART_FLAG_TC);
//    USART_SendData(UART5,(uint8_t)ch);  
//	while(USART_GetFlagStatus(UART5,USART_FLAG_TC)==RESET);  
//	return ch;
//}

void UART5_send_byte(unsigned char c)
{
	USART_ClearFlag(UART5, USART_FLAG_TC);
	USART_SendData(UART5, (u16)c);
	while(USART_GetFlagStatus(UART5, USART_FLAG_TC) != SET);//等待发送完成
}

void USART_send_srt(unsigned char *s)
{
	while(*s != '\0')
	{
		UART5_send_byte(*s++);
	}
}

//按字符串形式发送16进制数据
void USART_sendHEX(unsigned char hex)
{
	unsigned char const tab[]={"0123456789ABCDEF"};

	UART5_send_byte(tab[hex >> 4]);
	UART5_send_byte(tab[hex & 0x0f]);
	UART5_send_byte(' ');
}

/*******************************************************************************
* 函数名	: uart5_init
* 描述  	: 初始化串口1 
* 参数  	: bound:波特率
* 返回值	: 无
*******************************************************************************/
void uart5_init(u32 bound)
{
    //GPIO端口设置
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD, ENABLE);//使能GPIOb时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);//UART5
    
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource12, GPIO_AF_UART5);//重映射，TX
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource2, GPIO_AF_UART5); //重映射，RX
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   //翻转速度
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //输入输出设置，输入/输出/复用/模拟
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //输出模式，开漏/推挽
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //输入模式，浮空/上拉/下拉
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   //翻转速度
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //输入输出设置，输入/输出/复用/模拟
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //输出模式，开漏/推挽
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //输入模式，浮空/上拉/下拉
	GPIO_Init(GPIOD, &GPIO_InitStructure); 

   //USART 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//一般设置为9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//收发模式
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
    
	USART_Init(UART5, &USART_InitStructure);//初始化串口 
    
    //Usart1 NVIC 配置	
	NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;//抢占优先级5
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;       //子优先级3,子优先级不能为0？？？
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;          //IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);//根据指定的参数初始化VIC寄存器

	USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);//开启中断
	USART_Cmd(UART5, ENABLE);//使能串口
}

/*******************************************************************************
* 函数名	: USART1_IRQHandler
* 描述  	: 串口1中断服务函数,接收调试信息
* 参数  	: 无
* 返回值	: 无
*******************************************************************************/
void UART5_IRQHandler(void)
{	
	if(USART_GetITStatus(UART5, USART_IT_RXNE) == SET)//检查指定的USART中断发生与否
	{

	}
}
