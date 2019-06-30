#include "ioCC2530.h"
#include "LCD.h"
#include "UART.h"
#include "timer.h"
#include "LED.h"
#include "Date.h"

int key_num=0;
void key_1();
void key_2();

void main(void)
{
  //外部中断
  Init32M();
  InitUART();
  //定时器1中断
  Init_Timer1();	
  
  //按钮中断
  P0IE=1;
  P0IEN |= 0X02;
  
  //按钮初始化
  button_Init();
  
  //初始化LED
  P1DIR|=0X13;
  All_OFF();
  
  //zijian();	//自检函数，想写的时候再说吧
  
  //初始化液晶屏
  LCD_Init();
  //清屏
  LCD_Clear();
  //显示信息
  LCD_WriteString(0,1,"+----------------+");
  LCD_WriteString(0,2,"|     Welcome    |");
  LCD_WriteString(0,3,"|                |");
  LCD_WriteString(0,4,"|   Writer:LJJ   |");
  LCD_WriteString(0,5,"|                |");
  LCD_WriteString(0,6,"|2019.06.01 00:00|");
  LCD_WriteString(0,7,"+----------------+");
  UART0SendByte('\n');
    while(1)
    {
      if(key_num==0)
      {        
        
      }
      else if(key_num%2==0)
      {
        button_LCD_Num(key_num);
        key_1();
      }
      else if(key_num%2==1)
      {
        button_LCD_Num(key_num);
         key_2();
      }
    }
}

//#pragma optimize=none//优化函数 放在被优化函数之前
#pragma vector=P0INT_VECTOR
__interrupt void love()
{
  if(P0IFG & 0X02)//0000 0010 0000 0000 
  {//P0组第2位P0_1有没有引发外部中断 引发了外部中断 P0IFG对应的位就会被置1
    delay();
    if(1==P0_1)
    {//如果按键确实被按下 那么确实是连接在P0_1的按键触发了外部中断
      key_num++;
      UART0SendString(LED_num_judge(7));
    }
  }
  P0_1=0;
  P0IFG=0;//P0中断状态标志 
  P0IF=0;//端口0中断标志 1表示中断挂起 0表示中断未挂起
}


void key_1()
{
  while(1) 
    {
    running2();
    delay();
    if(key_num%2!=0)
    {
      P0_1=0;
      break;
    }
  }  
}

void key_2()
{
  while(1) 
    {
    running();
    delay();
    if(key_num%2!=1)
    {
      P0_1=0;
      break;
    }
  }  
}
