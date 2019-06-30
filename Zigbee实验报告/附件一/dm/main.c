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
  //�ⲿ�ж�
  Init32M();
  InitUART();
  //��ʱ��1�ж�
  Init_Timer1();	
  
  //��ť�ж�
  P0IE=1;
  P0IEN |= 0X02;
  
  //��ť��ʼ��
  button_Init();
  
  //��ʼ��LED
  P1DIR|=0X13;
  All_OFF();
  
  //zijian();	//�Լ캯������д��ʱ����˵��
  
  //��ʼ��Һ����
  LCD_Init();
  //����
  LCD_Clear();
  //��ʾ��Ϣ
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

//#pragma optimize=none//�Ż����� ���ڱ��Ż�����֮ǰ
#pragma vector=P0INT_VECTOR
__interrupt void love()
{
  if(P0IFG & 0X02)//0000 0010 0000 0000 
  {//P0���2λP0_1��û�������ⲿ�ж� �������ⲿ�ж� P0IFG��Ӧ��λ�ͻᱻ��1
    delay();
    if(1==P0_1)
    {//�������ȷʵ������ ��ôȷʵ��������P0_1�İ����������ⲿ�ж�
      key_num++;
      UART0SendString(LED_num_judge(7));
    }
  }
  P0_1=0;
  P0IFG=0;//P0�ж�״̬��־ 
  P0IF=0;//�˿�0�жϱ�־ 1��ʾ�жϹ��� 0��ʾ�ж�δ����
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
