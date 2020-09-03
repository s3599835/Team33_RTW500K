/*
 * Design 3 - Group 33
 * RTW500k Function Generator
 * utility.h
 */

#ifndef UTILITY_H
#define UTILITY_H

#include <avr/io.h>
#include <util/delay.h>

#ifndef M_PI
#define M_PI 3.14159265
#endif

//SPI Stuff
//PORT B
#define SCK 5
#define MOSI 4
//Chip Select Lines
#define CS_AD9833 2
#define CS_MTP 1

//LCD
//PORT C
#define LCD_ENABLE 0
#define LCD_REGISTERSELECT 1
#define LCD_D4 2
#define LCD_D5 3
#define LCD_D6 4
#define LCD_D7 5

//Buttons
//PORT D
#define UP_PIN 0
#define DOWN_PIN 1
#define LEFT_PIN 2
#define RIGHT_PIN 3
#define FUNC_PIN 4

typedef enum
{
	SINE, SQURE, TRIANGLE
} WaveType;

typedef enum{
	UP, DOWN, LEFT, RIGHT, FUNCTION
} Buttons;

typedef enum {
	FREQUENCY, AMPLITUDE, OFFSET, WAVE
} FunctionSelect;

typedef struct {
	WaveType wavetype;
	int frequency;
	//Hold the current step digital pot
	int amplitudeIndex;
	float amplitude;
	int offsetIndex;
	float offset;
} OutputWaveForm;

typedef struct {
	char frequency[6];
	char amplitude[6];
	char voltageOffset[6];
	//SQR SIN TRI
	char wave[4];
	int cursorPositionx;
	int cursorPositiony;
} Display;

typedef struct {
	//If the input has been read set high
	int inputChange;
	//Input that has been read;
	int inputRead;
	//Current parameeter select
	FunctionSelect currentFunction;
} Control;

#endif