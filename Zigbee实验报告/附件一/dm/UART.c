#include "ioCC2530.h"
#include "UART.h"
#include "LCD.h"
#include "LED.h"
char ch;
char buff[20];




/*
  	1��ָ�����ڵ�IOλ�ã�
	2����ӦIO���ó�ƫ�����蹦�ܣ�
	3��8������λ��1��ֹͣλ�������ء���У��ȷ��������������򵥵�ͨ�ţ�
		����һ��UART�ֽڰ���һ����ʼλ��8����Ϊ��1����Ϊ��ѡ�ĵ�9λ���ݻ�У��λ��
		�ټ���һ������2��ֹͣλ
	4�������ʣ���9600����115200��
        5����CPU�жϡ���Ӧ���ڽ����жϣ�
*/
//���ڳ�ʼ��
void InitUART(void)
{
  //1��ָ�����ڵ�IOλ�ã�P0_2 3 UART0 ��һ��λ�� ��PERCFG�ĵ�0λ��0
  PERCFG &= 0xFE;//1111 1110 ѡ�д���0�ı���λ��1
  //2����ӦIO���ó�ƫ�����蹦�ܣ�
  P0SEL |= 0x0C;//0000 1100 P0_2 P0_3��1 Ϊƫ�����蹦��
  //3��8������λ��1��ֹͣλ�������ء���У��ȷ��������������򵥵�ͨ�ţ�
  U0CSR |= 0xC0;//1100 0000 ѡ�� UARTģʽ ������ʹ����1
  //4�������ʣ���9600����115200��
  U0GCR=8;
  U0BAUD=59;//���ó�9600
  //5����CPU�жϡ���Ӧ���ڽ����жϣ�
  EA=1;//�������ж�
  URX0IE=1;//USRAT0�ж�ʹ��
}


/*********************************************************************
 * �������ƣ�UART0SendByte
 * ��    �ܣ�UART0����һ���ֽ�
 * ��ڲ�����c
 * ���ڲ�������
 * �� �� ֵ����
 ********************************************************************/
void UART0SendByte(unsigned char c)
{
  U0DBUF = c;       // ��Ҫ���͵�1�ֽ�����д��U0DBUF(���� 0 �շ�������)  
  while (!UTX0IF);  // �ȴ�TX�жϱ�־����U0DBUF����
  UTX0IF = 0;       // ����TX�жϱ�־ 
}


/*********************************************************************
 * �������ƣ�UART0SendString
 * ��    �ܣ�UART0����һ���ַ���
 * ��ڲ�������
 * ���ڲ�������
 * �� �� ֵ����
 ********************************************************************/
void UART0SendString(char *str)
{
  while(1)
  {
    if(*str == '\0') break;  // �������������˳�
    UART0SendByte(*str++);   // ����һ�ֽ�
  } 
}


#pragma optimize=none//�Ż����� ���ڱ��Ż�����֮ǰ
#pragma vector=URX0_VECTOR
__interrupt void MYuart()
{
  //����0�����ݵı�־λ��Ӳ������1���������Ҫ��0
  URX0IF=0;
  //���ݵĽ���
  ch=U0DBUF;//�ӽ��ܼĴ�����ȡ�ֽڴ��뵽����ch��
      
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

  U0DBUF=ch;//�ѱ���ch���ֵ��������0���ͼĴ���
  *buff = U0DBUF;
  
  //�жϷ�����û����ɣ��жϼĴ�����λUTX0IF��û�б���1
  while(0==UTX0IF);
  //�ֶ���0
  UTX0IF=0;
  UART0SendByte('\n');
}








