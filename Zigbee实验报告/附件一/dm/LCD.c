/*******************************************************************************
 * �ļ����ƣ�hal_led.c
 * ��    �ܣ�OLED����
 *           ʹ��Ӳ��SPI��������128*64����OLEDҺ��
 * Ӳ�����ӣ�Һ��ģ����CC2530��Ӳ�����ӹ�ϵ���£�
 *                Һ��ģ��                       CC2530
 *                  CS                            P1.2
 *                  SDA                           P1.6
 *                  SCK                           P1.5
 *                  RESET                         P0.0
 *                  D/C#                          P2.2
 *                �ֿ�оƬ
 *                  CS#                           P2.1
 *                  SCLK                          P1.5
 *                  SI                            P1.6
 *                  SO                            P1.7
 ******************************************************************************/

/* ����ͷ�ļ� */
/********************************************************************/
#include "ioCC2530.h"
//#include "hal_board_cfg.h"
#include "LCD.h"
/********************************************************************/


/* ���ر��� */
/********************************************************************/
uint8 X_Witch = 6;
uint8 Y_Witch = 1;
uint8 X_Witch_cn = 16;
uint8 Y_Witch_cn = 16;
uint8 Dis_Zero = 0;
/********************************************************************/

#define FUNCTION_SET(options,OLED_DC)       halOLED_control(options,OLED_DC)

/*********************************************************************
 * �������ƣ�LCD_TimeDelay
 * ��    �ܣ���ʱ����
 * ��ڲ�����Timers  ��ʱʱ�����
 * ���ڲ�������
 * �� �� ֵ����
 ********************************************************************/
void LCD_TimeDelay(uint16 Timers)
{
  uint16 i;

  while(Timers)
  {
    Timers--;
    for(i = 0; i < 100; i++)NOP();
  }
}


/*********************************************************************
 * �������ƣ�LCD_SPISSSet
 * ��    �ܣ���SS��״̬
 * ��ڲ�����Status SS��״̬
 * ���ڲ�������
 * �� �� ֵ����
 ********************************************************************/
void LCD_SPISSSet(uint8 Status)
{
  NOP();NOP();NOP();
  if(Status)				
    H_LCD_CSn();
  else
    L_LCD_CSn();

  NOP();NOP();NOP();NOP();
}

/*********************************************************************
 * �������ƣ�LCD_SPI_DC
 * ��    �ܣ���DATA/COMMAND��״̬
 * ��ڲ�����Status SS��״̬
 * ���ڲ�������
 * �� �� ֵ����
 ********************************************************************/
void LCD_SPI_DC(uint8 Status)
{
  NOP();NOP();NOP();
  if(Status)				
    LCD_DATA();
  else
    LCD_COMMAND();

  NOP();NOP();NOP();NOP();
}

/*********************************************************************
 * �������ƣ�GT20L_SPI
 * ��    �ܣ�ƬѡGT20
 * ��ڲ�����Status SS��״̬
 * ���ڲ�������
 * �� �� ֵ����
 ********************************************************************/
void GT20L_SPI(uint8 Status)
{
  NOP();NOP();NOP();
  if(Status)				
    L_GT20_CSn();
  else
    H_GT20_CSn();

  NOP();NOP();NOP();NOP();
}
/*********************************************************************
 * �������ƣ�LCD_SPISendData
 * ��    �ܣ�ͨ������SPI������һ��byte��������ģ��
 * ��ڲ�����Data  Ҫ���͵�����
 * ���ڲ�����temp
 * �� �� ֵ��SPI�ӵ�����
 ********************************************************************/
uint8 LCD_SPISendData(uint8 Data)
{
  uint8 i=0;
  uint8 temp=0;

  for(i = 0; i < 8; i++)
  {
    NOP();NOP();NOP();NOP();NOP();NOP(); // �ʵ�����һЩ�ղ����Ա�֤SPIʱ���ٶ�С��2MHz
    L_LCD_SCK();	
		
    if(Data&0x80)
      H_LCD_SDA();
    else
      L_LCD_SDA();

    NOP();NOP();NOP();NOP();NOP(); //�ʵ�����һЩ�ղ����Ա�֤SPIʱ���ٶ�С��2MHz
    NOP();NOP();NOP();NOP();NOP();
    H_LCD_SCK();
    if(GT20_MISO==1)
    {
      temp=temp | BV(7-i);
    }
    NOP();NOP();NOP();NOP();NOP();
		
    Data = Data << 1;		   //��������һλ
  }
  NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();
  return temp;
}
/*********************************************************************
 * �������ƣ�halOLED_control
 * ��    �ܣ�ͨ������SPI������һ��byte��������ģ��
 * ��ڲ���������cmd, ������� OLED_DC
 * ���ڲ�������
 * �� �� ֵ����
 ********************************************************************/
void halOLED_control(uint8 cmd, uint8 OLED_DC)
{
  LCD_SPISSSet(0);	   //SS�õ͵�ƽ
  if(OLED_DC==COMMAND)
  {
    LCD_SPI_DC(0);
  }
  else
  {
    LCD_SPI_DC(1);
  }
  LCD_SPISendData(cmd);   //��ָ��0x80
  LCD_SPI_DC(1);
  LCD_SPISSSet(1);	   //��ɲ�����SS�ߵ�ƽ
}

/*********************************************************************
 * �������ƣ�HalLed_SET_XY
 * ��    �ܣ����� x y ��ַ
 * ��ڲ�����x   x��ַ
 *           y   y��ַ
 * ���ڲ�������
 * �� �� ֵ����
 ********************************************************************/
void HalLed_SET_XY(unsigned char x,unsigned char y)
{
  FUNCTION_SET(0x22,COMMAND);	//����ָ��0x22
  FUNCTION_SET(y,COMMAND);	//Ҫ��ʾ�ַ������Ͻǵ�Y��λ��
  FUNCTION_SET(Dis_Y_MAX ,COMMAND);	//Ҫ��ʾ�ַ������Ͻǵ�Y��λ��
  FUNCTION_SET(0x21,COMMAND);	//����ָ��0x21
  FUNCTION_SET(x,COMMAND);	//Ҫ��ʾ�ַ������Ͻǵ�X��λ��
  FUNCTION_SET(Dis_X_MAX ,COMMAND);	//Ҫ��ʾ�ַ������Ͻǵ�Y��λ��
}

/*********************************************************************
 * �������ƣ�HalGT20L_TX_CMD
 * ��    �ܣ�GT20LӲ��д�����
 * ��ڲ�����cmd   д������
 * ���ڲ�������
 * �� �� ֵ����
 ********************************************************************/
int8 HalGT20L_TX_CMD(uint8 cmd )
{
  return LCD_SPISendData(cmd);
}

/*********************************************************************
 * �������ƣ�halGT20L_HRD_Font
 * ��    �ܣ�GT23L��ȡ�ַ���ֵ����
 * ��ڲ����� Dst �ֿ��ַ, no_bytes һ���ַ���Ҫ����ֵ �ֽ��� ,  *buffer ��ֵ
 * ���ڲ�������
 * �� �� ֵ����
 ********************************************************************/
void halGT20L_HRD_Font(uint16 * Dst, uint8 no_bytes,uint8 *buffer)
{
    unsigned char i = 0;
    GT20L_SPI(1);                                // enable device
    HalGT20L_TX_CMD(0x0B);                       // read command
    HalGT20L_TX_CMD(Dst[1]);  // send 3 address bytes
    HalGT20L_TX_CMD(((Dst[0]) >> 8));
    HalGT20L_TX_CMD(Dst[0] & 0xFF);
    HalGT20L_TX_CMD(0xFF);                       //dummy byte
    for (i = 0; i < no_bytes; i++)              // read until no_bytes is reached
    {
      buffer[i] =HalGT20L_TX_CMD(0xFF);    // receive byte and store at address 80H - FFH
    }
    GT20L_SPI(0);                                // disable device
}
/*********************************************************************
 * �������ƣ�halASCII_Searh_ADDR
 * ��    �ܣ�ASCII���ַ�����
 * ��ڲ�����uint8 ASCIICode,uint16 * CODE_ADDR
 * ���ڲ�������
 * �� �� ֵ����
 ********************************************************************/
void halASCII_Searh_ADDR(uint8 ASCIICode,uint16 * CODE_ADDR)
{
  uint16 ASCII_Code_Addr = 0;
 // ASCII_Code_Addr = ((((uint16)ASCIICode) - (uint16)0x20) * 8) +0x66C0;//�л�����
  ASCII_Code_Addr = ((((uint16)ASCIICode) - (uint16)0x20) * 8) +0xbfC0;
  CODE_ADDR[0]=ASCII_Code_Addr ;
  CODE_ADDR[1]=0x03;
}

/*********************************************************************
 * �������ƣ�LCD_WriteChar
 * ��    �ܣ���ʾASCII���ַ�
 * ��ڲ�����x  Ҫ��ʾ���ַ�x��ַ
 *           y  Ҫ��ʾ���ַ�y��ַ
 *           a  Ҫ��ʾ��ASCII���ַ�ֵ
 * ���ڲ�������
 * �� �� ֵ����
 ********************************************************************/
void LCD_WriteChar(uint8 x, uint8 y, const char a)
{
  uint8 i=0;
  uint16 ASCII_CODE_ADDR[2];
  uint8 font_buffer[8];

  halASCII_Searh_ADDR(a ,ASCII_CODE_ADDR);
  halGT20L_HRD_Font(ASCII_CODE_ADDR,8,font_buffer);
  HalLed_SET_XY(x,y);
  for(i=0;i<8;i++)
  {
  FUNCTION_SET(font_buffer[i],DATA);
  }

}


/********************************************************************
 * �������ƣ�LCD_WriteString
 * ��    �ܣ���x��yΪ��ʼ���괦д��һ���ַ�
 * ��ڲ�����x  X�����꣬ȡֵ��Χ��0 - 127
 *           y  Y�����꣬ȡֵ��Χ0-63
 *           p  Ҫ��ʾ���ַ���
 * ���ڲ�������
 * �� �� ֵ����
 ********************************************************************/
void LCD_WriteString(uint8 x, uint8 y, const char *p)
{
  while(*p != 0)
  {
    LCD_WriteChar(x, y, *p);
    x += 7;
    if(x > Dis_X_MAX)
    {
      x = Dis_Zero;
      if((Dis_Y_MAX - y) < Y_Witch) break;
      else y += 1;
    }
    p+=1;
  }
}



/********************************************************************
 * �������ƣ�LCD_SetBackLight
 * ��    �ܣ����ñ������ȵȼ�
 * ��ڲ�����Deg  ���ȵȼ�0~127
 * ���ڲ�������
 * �� �� ֵ����
 ********************************************************************/
void LCD_SetBackLight(uint8 Deg)
{
  GT20L_SPI(1);                                // enable device
  HalGT20L_TX_CMD(0x81);
  LCD_SPISendData(Deg);	   //������������ֵ
  GT20L_SPI(0);
}


/*********************************************************************
 * �������ƣ�LCD_Clear
 * ��    �ܣ�LCD����
 * ��ڲ�������
 * ���ڲ�������
 * �� �� ֵ����
 ********************************************************************/
void LCD_Clear(void)
{
  uint8 i,j;
  //��������
  FUNCTION_SET(0x22,COMMAND);
  FUNCTION_SET(0,COMMAND);
  FUNCTION_SET(7,COMMAND);
  FUNCTION_SET(0x21,COMMAND);
  FUNCTION_SET(0,COMMAND);
  FUNCTION_SET(127,COMMAND);

  for(i=0;i<8;i++)
  {
    for(j=0;j<128;j++)
      FUNCTION_SET(0x00,DATA);
  }
}



/*********************************************************************
 * �������ƣ�LCD_Init
 * ��    �ܣ�LCD��ʼ��
 * ��ڲ�������
 * ���ڲ�������
 * �� �� ֵ����
 ********************************************************************/
void LCD_Init(void)
{
  P0DIR |= (0x01<<0);  // P0.0Ϊ���
  P1DIR |= (0x01<<2);  // P1.2Ϊ���
  P1DIR |= (0x01<<5);  // P1.5Ϊ���
  P1DIR |= (0x01<<6);  // P1.6Ϊ���

  P1DIR &= (0X7F);  // P1.7Ϊ����
  P2DIR |= (0x01<<1);  // P2.1Ϊ���
  P2DIR |= (0x01<<2);  // P2.2Ϊ���

  /* ��λLCD */
  L_LCD_RESETn();
  LCD_TimeDelay(3000);
  H_LCD_RESETn();
  LCD_TimeDelay(3000);

  //Charge Pump Setting
  FUNCTION_SET(0x8d,COMMAND);
  FUNCTION_SET(0x14,COMMAND);
  FUNCTION_SET(0xaf,COMMAND);
  //Set Display Clock
  FUNCTION_SET(0xD5,COMMAND);
  FUNCTION_SET(0xF0,COMMAND);
  //Set Pre-charge Period
  FUNCTION_SET(0xD9,COMMAND);
  FUNCTION_SET(0x11,COMMAND);
  //Set VCOMH Deselect Level
  FUNCTION_SET(0xDb,COMMAND);
  FUNCTION_SET(0x0,COMMAND);
  //Set Norma Display
  FUNCTION_SET(0xa6,COMMAND);
  //Entire Display ON
  //FUNCTION_SET(0xa5,COMMAND);
  //Set Contrast Control
  FUNCTION_SET(0x81,COMMAND);
  FUNCTION_SET(0xff,COMMAND);  //1-256
  //Set Segment Re-map
  FUNCTION_SET(0xa1,COMMAND);
  //Set COM Output Scan Direction
  FUNCTION_SET(0xc8,COMMAND);
  //Set Memory Addressing Mode
  FUNCTION_SET(0x20,COMMAND);
  FUNCTION_SET(0x00,COMMAND);
  LCD_SetBackLight(100); // ���ڱ�������
}





