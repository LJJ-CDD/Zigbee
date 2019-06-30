#ifndef _LED_H_
#define _LED_H_
#include "ioCC2530.h"

void running(void);	/* 跑马�?*/
void running2(void);	/* 闪烁 */
void zijian(void);	/* 自检 */
void All_OFF(void);
void button_LCD(void);
void button_LCD_Num(int );
void running_LCD_WriteChar(char a,char b,char c);
char *LED_num_judge(int num);

void button_Init();
#endif	/* _LED_H_ */

