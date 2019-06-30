/*******************************************************************************
 * 文件名称：LCD.h
 * 功    能：LCD驱动
 *           驱动128*64点阵图形液晶（MzLH04-12864）
 * 硬件连接：液晶模块与CC2530的硬件连接关系如下：
 *                液晶模块                         CC2530
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
//防止头文件重名

//宏定义
#ifndef BV
#define BV(n)      (1 << (n))
#endif

/* 类型定义 */
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

/* 相关引脚定义 */
/*===================================================*/
#define      LCD_SDA            P1_6
#define      LCD_SCK            P1_5
#define      LCD_CSn            P1_2
#define      LCD_RESETn         P0_0
#define      LCD_DC             P2_2

#define      GT20_MISO          P1_7
#define      GT20_CS            P2_1
/*===================================================*/


/* 相关引脚输出电平定义 */
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
//屏幕128*64 可以分成X和Y轴
#define      Dis_X_MAX		127
#define      Dis_Y_MAX		7

#define      COMMAND		0
#define     DATA		1
/*********************************************************************
 * 函数名称：LCD_Init
 * 功    能：LCD初始化
 * 入口参数：无
 * 出口参数：无
 * 返 回 值：无
 ********************************************************************/
extern void LCD_Init(void);


/*********************************************************************
 * 函数名称：LCD_Clear
 * 功    能：LCD清屏
 * 入口参数：无
 * 出口参数：无
 * 返 回 值：无
 ********************************************************************/
extern void LCD_Clear(void);


/********************************************************************
 * 函数名称：LCD_WriteString
 * 功    能：在x、y为起始坐标处写入一串字符
 * 入口参数：x  X轴坐标，取值范围：0 - 127
 *           y  Y轴坐标，取值范围0-63
 *           p  要显示的字符串
 * 出口参数：无
 * 返 回 值：无
 ********************************************************************/
extern void LCD_WriteString(uint8 x, uint8 y, const char *p);


/*********************************************************************
 * 函数名称：LCD_WriteChar
 * 功    能：显示ASCII码字符
 * 入口参数：x  要显示的字符x地址
 *           y  要显示的字符y地址
 *           a  要显示的ASCII码字符值
 * 出口参数：无
 * 返 回 值：无
 ********************************************************************/
extern void LCD_WriteChar(uint8 x, uint8 y, const char a);

#endif	/* _LCD_H_ */
