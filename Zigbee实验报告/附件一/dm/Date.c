#include "ioCC2530.h"
#include "LCD.h"

unsigned int count_date = 0;  
int second_one=0,second_two=0;		//秒
int branch_one=0,branch_two=0;		//分

void Init_Timer1()
{
  T1CC0L = 0xd4;        //设置最大计数值的低8位
  T1CC0H = 0x30;        //设置最大计数值的高8位
  T1CCTL0 |= 0x04;      //开启通道0的输出比较模式
  T1IE = 1;             //使能定时器1中断
  T1OVFIM = 1;          //使能定时器1溢出中断
  EA = 1;               //使能总中断
  T1CTL = 0x0e;         //分频系数是128,模模式
} 

unsigned int count_branch_num = 0;      //分计时 
void branch_count()       //分
{
  branch_one++;
  if(branch_one > 9)
     branch_one = 0;
  if(count_branch_num %10 == 0)  // 十分到
  {
    branch_two++;
    if(branch_two > 5)
    {
      branch_two = 0;
    }
    LCD_WriteChar(83,6,(branch_two+48));
    LCD_WriteChar(91,6,(branch_one+48));
  }
  else
  {
    LCD_WriteChar(91,6,(branch_one+48));
  }   
}

void second_count(unsigned int s)           //秒计时 
{
  second_one++;
  if(second_one > 9)
     second_one = 0;
  if(s %100 == 0)               // 十秒到
  {
    second_two++;
    if(second_two > 5)
    {
      second_two = 0;
    }
    LCD_WriteChar(105,6,(second_two+48));
    LCD_WriteChar(112,6,(second_one+48));
  }
  else
  {
    LCD_WriteChar(112,6,(second_one+48));
  }  
}

/*================定时器1服务函数--日历==================*/
#pragma vector = T1_VECTOR
__interrupt void Timer1_Sevice()
{
  T1STAT &= ~0x01;      //清除定时器1通道0中断标志
  count_date++;
  if(count_date%10 == 0)     //定时1秒到
  {
    second_count(count_date);
    if(count_date%600 == 0)     //如果到六十秒
    {
      count_branch_num++;       //秒数显示的十位数到达 6 时，分数计数器 +1 
      branch_count();
      count_date=0;
      if(count_branch_num%60 == 0)      //如果到60分
        count_branch_num=0;
    }
  }
}