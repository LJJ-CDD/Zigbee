#include <ioCC2530.h>
#include "timer.h"
#include "LCD.h"
#include "UART.h"

char *LED_num_judge(int num)
{
  switch(num)
  {
  case 0:       return "[D1:0 D2:0 D3:0]";
  case 1:       return "[D1:1 D2:0 D3:0]";
  case 2:       return "[D1:0 D2:1 D3:0]";
  case 3:       return "[D1:0 D2:0 D3:1]";
  case 4:       return "[D1:1 D2:1 D3:1]";
  case 5:       return "Input: ";
  case 6:       return "\nEnter test2 mode: ";
  case 7:       return "\nButton2 Press down:\n";
  }
  return "\nERROR : LED_num_judge Functions do not accept 0-4 \n";
}

void running_LCD_WriteChar(char a,char b,char c)
{
  LCD_WriteChar(105,3,a);
  LCD_WriteChar(105,4,b);
  LCD_WriteChar(105,5,c);
}


void button_LCD()
{
  LCD_WriteString(0,2,"| ButtonNum : 1  |");
  LCD_WriteString(0,3,"| LED P1_0  :  0 |");
  LCD_WriteString(0,4,"| LED P1_1  :  0 |");
  LCD_WriteString(0,5,"| LED P1_4  :  0 |");
}

void button_LCD_Num(int a)
{
  if(a==1)
  {
    button_LCD();
  }
  else
  { 
    LCD_WriteChar(98,2,a+48);
  }
}

void running()
{
  running_LCD_WriteChar('1','0','0');
  UART0SendString(LED_num_judge(1));
  P1_0=1; 
  P1_1=0;
  P1_4=0;
  delay();
  delay();
  running_LCD_WriteChar('0','1','0');
  UART0SendString(LED_num_judge(2));
  P1_0=0; 
  P1_1=1;
  P1_4=0;
  delay();
  delay();
  running_LCD_WriteChar('0','0','1');
  UART0SendString(LED_num_judge(3));  
  P1_0=0; 
  P1_1=0;
  P1_4=1;
  delay();
  UART0SendByte('\n');
  delay();  
}

void running2()
{
  running_LCD_WriteChar('0','0','0');
  UART0SendString(LED_num_judge(0)); 
  P1_0=0; 
  P1_1=0;
  P1_4=0;
  delay(); 
  delay();
  running_LCD_WriteChar('1','1','1');
  UART0SendString(LED_num_judge(4));  
  P1_0=1; 
  P1_1=1;
  P1_4=1;
  delay();
  UART0SendByte('\n');
  delay();
}

void zijian()
{
  P1_0=0; 
  P1_1=0;
  P1_4=0;
  delay();
  delay();
  P1_0=1; 
  P1_1=1;
  P1_4=1;
  delay();
  delay();
  delay(); 
  P1_0=0; 
  P1_1=0;
  P1_4=0;
  delay();
  delay();
  delay(); 
  running();
  delay();
  delay();
  running2();
  delay();
  delay();
}

void All_OFF()
{
  P1_0=0; 
  P1_1=0;
  P1_4=0;   
}

void button_Init()
{
    
  //让P0_1处于普通IO口，处于输入模式
  P0SEL &= ~(0x01<<1);
  P1DIR &= ~(0X01<<1);//1111 1101 0XfD
  
  //让P0_1处于上拉模式
  P0INP &= ~(0x01<<1);//让P0_1处于上下拉模式
  P2INP &= ~(0X01<<5);//让P0_1(P0）处于上拉模式（端口0）
}

