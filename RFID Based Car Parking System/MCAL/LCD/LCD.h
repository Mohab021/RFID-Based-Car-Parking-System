/*
 * ATmega LCD16x2 4 bit .h file
 * www.electronicwings.com
 */ 


#ifndef LCD_H_
#define LCD_H_
#define  F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#define LCD_DPRT PORTD
#define LCD_DDDR DDRD
#define LCD_RS 2
#define LCD_EN 3

void lcdcommand(unsigned char cmnd);
void lcddata(unsigned char data);
void lcdinit();
void lcd_print_xy(char row, char pos, char* str);
void lcd_print(char *str);
void lcd_clear();




#endif /* LCD_H_ */