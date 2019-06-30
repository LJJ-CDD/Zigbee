#include <ioCC2530.h>
#include "timer.h"


//延时程序 63us
void delayus(void)//因为我们CC2530上电默认�?6M高频 机器周期大概�?us
{
  char k=63;
  while(k--);
}

//初始化32M外部晶振
void Init32M()
{
  //1、让2个高频时钟源起振；
  SLEEPCMD &= 0xFB;//1111 1011 开启两个高频时钟源
  //2、等待目标时钟源振荡稳定；
  while(0==(SLEEPSTA & 0x40));//0100 0000 等待32M稳定下来 通过查询SLEEPSTA寄存器的第6位是否为0
                              //32M晶振是否稳定下来 0不稳定 1稳定
  //3、延时一小段时63us；
  delayus();
  //4、不分频输出；
  CLKCONCMD &= 0xF8;//1111 1000
  //5、选中目标高频时钟源作为系统主时钟；32M
  CLKCONCMD &= 0xBF;//1011 1111 ~0x40
  //6、确认一下当前工作的系统时钟是不是所选的高频时钟；
  while(CLKCONSTA & 0x40);//0100 0000 //查询CLKCONSTA第六位是否为0 为0 的时候表达式为假 已经选择32M作为系统主时钟
}
  
  //��ʱ
void delay()
{
  int i,j;
  for(i=0;i<1000;i++)
    for(j=0;j<100;j++);
}