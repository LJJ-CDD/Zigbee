#include "ioCC2530.h"
#include "UART.h"
#include "LCD.h"
#include "LED.h"
char ch;
char buff[20];




/*
  	1、指定串口的IO位置；
	2、相应IO配置成偏上外设功能；
	3、8个数据位、1个停止位、无流控、无校验确立。（我们先最简单的通信）
		传送一个UART字节包含一个起始位，8个数为，1个作为可选的第9位数据或校验位，
		再加上一个或者2个停止位
	4、波特率；（9600或者115200）
        5、开CPU中断、对应串口接收中断；
*/
//串口初始化
void InitUART(void)
{
  //1、指定串口的IO位置；P0_2 3 UART0 第一个位置 把PERCFG的第0位置0
  PERCFG &= 0xFE;//1111 1110 选中串口0的备用位置1
  //2、相应IO配置成偏上外设功能；
  P0SEL |= 0x0C;//0000 1100 P0_2 P0_3置1 为偏上外设功能
  //3、8个数据位、1个停止位、无流控、无校验确立。（我们先最简单的通信）
  U0CSR |= 0xC0;//1100 0000 选择 UART模式 接收器使能置1
  //4、波特率；（9600或者115200）
  U0GCR=8;
  U0BAUD=59;//设置成9600
  //5、开CPU中断、对应串口接收中断；
  EA=1;//开启总中断
  URX0IE=1;//USRAT0中断使能
}


/*********************************************************************
 * 函数名称：UART0SendByte
 * 功    能：UART0发送一个字节
 * 入口参数：c
 * 出口参数：无
 * 返 回 值：无
 ********************************************************************/
void UART0SendByte(unsigned char c)
{
  U0DBUF = c;       // 将要发送的1字节数据写入U0DBUF(串口 0 收发缓冲器)  
  while (!UTX0IF);  // 等待TX中断标志，即U0DBUF就绪
  UTX0IF = 0;       // 清零TX中断标志 
}


/*********************************************************************
 * 函数名称：UART0SendString
 * 功    能：UART0发送一个字符串
 * 入口参数：无
 * 出口参数：无
 * 返 回 值：无
 ********************************************************************/
void UART0SendString(char *str)
{
  while(1)
  {
    if(*str == '\0') break;  // 遇到结束符，退出
    UART0SendByte(*str++);   // 发送一字节
  } 
}


#pragma optimize=none//优化函数 放在被优化函数之前
#pragma vector=URX0_VECTOR
__interrupt void MYuart()
{
  //串口0来数据的标志位，硬件会置1，我们软件要清0
  URX0IF=0;
  //数据的交换
  ch=U0DBUF;//从接受寄存器里取字节存入到变量ch里
      
  if(ch=='0')
  {
    P1_0=0; 
    P1_1=0;
    P1_4=0;
    UART0SendString(LED_num_judge(0));
    UART0SendString(LED_num_judge(5));
  }
  if(ch=='1')
  {
    P1_0=1; 
    P1_1=0;
    P1_4=0;
    UART0SendString(LED_num_judge(1));
    UART0SendString(LED_num_judge(5));
  }
  if(ch=='2')
  {
    P1_0=0; 
    P1_1=1;
    P1_4=0;
    UART0SendString(LED_num_judge(2));
    UART0SendString(LED_num_judge(5));
  }
  if(ch=='3')
  {
    P1_0=0; 
    P1_1=0;
    P1_4=1;
    UART0SendString(LED_num_judge(3));
    UART0SendString(LED_num_judge(5));
  }
  if(ch=='4')
  {
    P1_0=1; 
    P1_1=1;
    P1_4=1;
    UART0SendString(LED_num_judge(4));
    UART0SendString(LED_num_judge(5));
  }
  if(ch=='T')
  {
    UART0SendString(LED_num_judge(6));
    UART0SendString(LED_num_judge(5));
  }

  U0DBUF=ch;//把变量ch里的值赋给串口0发送寄存器
  *buff = U0DBUF;
  
  //判断发送有没有完成，判断寄存器的位UTX0IF有没有被置1
  while(0==UTX0IF);
  //手动置0
  UTX0IF=0;
  UART0SendByte('\n');
}








