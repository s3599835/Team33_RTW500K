/*
 * Design 3 - Group 33
 * RTW500k Function Generator
 * display.c
 */

#include "display.h"

//LCD
//PORT C
//#define LCD_ENABLE 0
//#define LCD_REGISTERSELECT 1
//#define LCD_D4 2
//#define LCD_D5 3
//#define LCD_D6 4
//#define LCD_D7 5


void lcdWriteCommand(unsigned char command)
{
	PORTB = ((command & 0xF0)>>4) << 2; //Top nibble
	PORTB &= ~(1<<LCD_REGISTERSELECT);
	PORTB |= (1<<LCD_ENABLE);
	_delay_us(100);
	PORTB &= ~(1<<LCD_ENABLE);
	PORTB = ((command & 0x0F)<< 2); //Bottom nibble
	PORTB |= (1<<LCD_ENABLE);
	_delay_us(1);
	PORTB &= ~(1<<LCD_ENABLE);
	_delay_us(100);
	
}

void lcdWriteData(unsigned char data)
{
	PORTB = ((data & 0xF0)>>4)<<2; //top nibble
	PORTB |= (1<<LCD_REGISTERSELECT);
	PORTB |= (1<<LCD_ENABLE);
	_delay_us(1);
	PORTB &= ~ (1<<LCD_ENABLE);
	_delay_us(100);
	PORTB &= (1<<LCD_REGISTERSELECT); 
	PORTB |= (data & 0x0F) << 2;//bottom nibble
	PORTB |= (1<<LCD_ENABLE);
	_delay_us(1);
	PORTB &= ~ (1<<LCD_ENABLE);
	_delay_us(100);
	
}
void lcdInit()
{
	DDRC = 0xFF;
	PORTC &= ~(1<<LCD_ENABLE);
	lcdWriteCommand(0x33); //For init
	lcdWriteCommand(0x32); //For init
	lcdWriteCommand(0x28); //2 Rows 5x7 character
	lcdWriteCommand(0x0e);//LCD on, cursor on
	lcdWriteCommand(0x01); //Clear display
	_delay_us(2000);
	lcdWriteCommand(0x06); //Set up cursor
	
}

void lcdPrintString (char * string)
{
	
	unsigned char index = 0;
	while(string[index] != 0)
	{
		
		lcdWriteData(string[index]);
		index++;
	}
	
}
void lcdGotoXY(unsigned char x, unsigned char y)
{
	unsigned char indexArray[] = {0x80, 0xC0, 0x94, 0xD4};//row and coloum via pixel index
	lcdWriteCommand(indexArray[y-1]+ x -1);
	_delay_us(1000);
}
int drawScreen(Display *display)
{
	//Liam
	//Actually draw to the screen

	return 0;
}

int updateDisplay(Display * display)
{
	//Stephen
	//Function to update the display struct (not write to display)
	return 0;
}