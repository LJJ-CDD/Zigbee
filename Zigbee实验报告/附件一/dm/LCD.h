/*******************************************************************************
 * �ļ����ƣ�LCD.h
 * ��    �ܣ�LCD����
 *           ����128*64����ͼ��Һ����MzLH04-12864��
 * Ӳ�����ӣ�Һ��ģ����CC2530��Ӳ�����ӹ�ϵ���£�
 *                Һ��ģ��                         CC2530
 *
 *               CS(PIN2)                           P1.2
 *               SDA(PIN3)                          P1.6
 *               SCK(PIN5)                          P1.5
 *               RESET(PIN6)                        P0.0
 *               VDD(PIN1)                           x
 *               NC(PIN4)                            x
 *               VSS(PIN7)                           x
 ******************************************************************************/


#ifndef _LCD_H_
#define _LCD_H_ 
//��ֹͷ�ļ�����

//�궨��
#ifndef BV
#define BV(n)      (1 << (n))
#endif

/* ���Ͷ��� */
/********************************************************************/
typedef signed   char   int8;
typedef unsigned char   uint8;

typedef signed   short  int16;
typedef unsigned short  uint16;

typedef signed   long   int32;
typedef unsigned long   uint32;

typedef unsigned char   bool;

typedef uint8           halDataAlign_t;
/********************************************************************/

/* ������Ŷ��� */
/*===================================================*/
#define      LCD_SDA            P1_6
#define      LCD_SCK            P1_5
#define      LCD_CSn            P1_2
#define      LCD_RESETn         P0_0
#define      LCD_DC             P2_2

#define      GT20_MISO          P1_7
#define      GT20_CS            P2_1
/*===================================================*/


/* ������������ƽ���� */
/*===================================================*/
#define      H_LCD_SCK()        LCD_SCK = 1
#define      L_LCD_SCK()        LCD_SCK = 0

#define      H_LCD_SDA()        LCD_SDA = 1
#define      L_LCD_SDA()        LCD_SDA = 0

#define      H_LCD_CSn()        LCD_CSn = 1
#define      L_LCD_CSn()        LCD_CSn = 0

#define      H_LCD_RESETn()     LCD_RESETn = 1
#define      L_LCD_RESETn()     LCD_RESETn = 0

#define      LCD_DATA()         LCD_DC = 1
#define      LCD_COMMAND()      LCD_DC = 0

#define      H_GT20_CSn()        GT20_CS = 1
#define      L_GT20_CSn()        GT20_CS = 0

/*===================================================*/


#define      NOP()              asm("nop")
//��Ļ128*64 ���Էֳ�X��Y��
#define      Dis_X_MAX		127
#define      Dis_Y_MAX		7

#define      COMMAND		0
#define     DATA		1
/*********************************************************************
 * �������ƣ�LCD_Init
 * ��    �ܣ�LCD��ʼ��
 * ��ڲ�������
 * ���ڲ�������
 * �� �� ֵ����
 ********************************************************************/
extern void LCD_Init(void);


/*********************************************************************
 * �������ƣ�LCD_Clear
 * ��    �ܣ�LCD����
 * ��ڲ�������
 * ���ڲ�������
 * �� �� ֵ����
 ********************************************************************/
extern void LCD_Clear(void);


/********************************************************************
 * �������ƣ�LCD_WriteString
 * ��    �ܣ���x��yΪ��ʼ���괦д��һ���ַ�
 * ��ڲ�����x  X�����꣬ȡֵ��Χ��0 - 127
 *           y  Y�����꣬ȡֵ��Χ0-63
 *           p  Ҫ��ʾ���ַ���
 * ���ڲ�������
 * �� �� ֵ����
 ********************************************************************/
extern void LCD_WriteString(uint8 x, uint8 y, const char *p);


/*********************************************************************
 * �������ƣ�LCD_WriteChar
 * ��    �ܣ���ʾASCII���ַ�
 * ��ڲ�����x  Ҫ��ʾ���ַ�x��ַ
 *           y  Ҫ��ʾ���ַ�y��ַ
 *           a  Ҫ��ʾ��ASCII���ַ�ֵ
 * ���ڲ�������
 * �� �� ֵ����
 ********************************************************************/
extern void LCD_WriteChar(uint8 x, uint8 y, const char a);

#endif	/* _LCD_H_ */
