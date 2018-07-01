/*
 * LCD_attempts.c
 *
 * Created: 9/6/2014 2:19:21 AM
 *  Author: ADITYA
 */ 

//Program to Display string on LCD using AVR Microcontroller (ATmega16)
/*
LCD DATA port----PORT D
signal port------PORT B
rs-------PB0
rw-------PB1
en-------PB2
*/

#include<avr/io.h>
#include<util/delay.h>

#define LCD_DATA PORTD	//LCD data port

#define ctrl PORTB
#define en PB2	// enable signal
#define rw PB1	// read/write signal
#define rs PB0	// register select signal

void LCD_cmd(unsigned char cmd);
void init_LCD(void);
void LCD_write(unsigned char data);

int main()
{
	DDRD=0xff;
	DDRB=0x07;
	init_LCD();	// initialization of LCD
	_delay_ms(50);	// delay of 50 mili seconds
	LCD_write_string("Vishu Bhai");	// function to print string on LCD
	return 0;
}

void init_LCD(void)
{
	LCD_cmd(0x38);	// initialization of 16X2 LCD in 8bit mode
	_delay_ms(1);

	LCD_cmd(0x01);	// clear LCD
	_delay_ms(1);

	LCD_cmd(0x0E);	// cursor ON
	_delay_ms(1);

	LCD_cmd(0x80);	// ---8 go to first line and --0 is for 0th position
	_delay_ms(1);
	return;
}

void LCD_cmd(unsigned char cmd)
{
	LCD_DATA=cmd;
	ctrl =(0<<rs)|(0<<rw)|(1<<en);
	_delay_ms(1);
	ctrl =(0<<rs)|(0<<rw)|(0<<en);
	_delay_ms(50);
	return;
}

void LCD_write(unsigned char data)
{
	LCD_DATA= data;
	ctrl = (1<<rs)|(0<<rw)|(1<<en);
	_delay_ms(1);
	ctrl = (1<<rs)|(0<<rw)|(0<<en);
	_delay_ms(50);
	return ;
}

void LCD_write_string(unsigned char *str)	//store address value of the string in pointer *str
{
	int i=0;
	while(str[i]!='\0')	// loop will go on till the NULL character in the string
	{
		LCD_write(str[i]);	// sending data on LCD byte by byte
		i++;
	}
	return;
}