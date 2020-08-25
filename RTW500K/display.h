/*
 * Design 3 - Group 33
 * RTW500k Function Generator
 * display.h
 */
#ifndef DISPLAY_H
#define DISPLAY_H

#include "utility.h"

int drawScreen(Display *display);
int updateDisplay(Display *display);
void lcdGotoXY(unsigned char x, unsigned char y);
void lcdPrintString (char * string);
void lcdInit();
void lcdWriteData(unsigned char data);
void lcdWriteCommand(unsigned char command);

#endif
