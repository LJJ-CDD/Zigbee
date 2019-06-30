#ifndef _UART_H_
#define _UART_H_
#include "ioCC2530.h"

void InitUART(void);						/* 串口初始化 */
void UART0SendByte(unsigned char c);		/* UART0发送一个字节 */
void UART0SendString(char *str);	/* UART0发送一个字符串 */
__interrupt void MYuart();					/* 串口中断 */


#endif	/* _UART_H_ */



