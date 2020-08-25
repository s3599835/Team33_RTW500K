/*
 * Design 3 - Group 33
 * RTW500k Function Generator
 * wave_chip.c
 */

#include "wave_chip.h"

int writeSPI (int chipselect)
{
	//Liam
	
	return 0;
}

int writeToAD9833 (OutputWaveForm * waveform)
{
		unsigned char byte0, byte1, byte2, byte3, byte4, byte5;
		//Set chip enable
		sendCommandAD9833(byte0, byte1);
		sendCommandAD9833(byte2, byte3);
		sendCommandAD9833(byte4, byte5);
		//deselect if you need to
	
	return 0;
}

void sendCommandAD9833(unsigned char byte1, unsigned char byte2)
{
	//set datatowrite
	SPDR = byte1;
	while(!(SPSR & (1<<SPIF)));
	
	SPDR = byte2;
	while(!(SPSR & (1<<SPIF)));
	
}