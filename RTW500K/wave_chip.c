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
	//Liam
	
	return 0;
<<<<<<< Updated upstream
=======
}

void sendCommandAD9833(unsigned char byte1, unsigned char byte2)
{
	PORTB &= ~(1<<CS_AD9833);
	SPDR = byte1;
	while(!(SPSR & (1<<SPIF)));
	
	SPDR = byte2;
	while(!(SPSR & (1<<SPIF)));
	PORTB |= 1<<CS_AD9833;
	
}

void initAD9833()
{
	unsigned char upperByte = 0x00;
	unsigned char lowerByte = 0x00;
	
	// Set reset and consecutive freq. write bits
	setRegBit(&upperByte, AD_RESET);
	setRegBit(&upperByte, AD_B28);
	sendCommandAD9833(upperByte, lowerByte);
	
	// Initialize frequency and phase registers to known vals
	setFrequency(AD_DEFAULT_FREQ);
	setPhase(AD_DEFAULT_PHASE);
	setMode(SINE);
	
	// Clear reset
	clearRegBit(&upperByte, AD_RESET);
	sendCommandAD9833(upperByte, lowerByte);
	
	
}

void setFrequency(int frequency)
{
	unsigned char firstUpperByte = 0x40;
	unsigned char secondUpperByte = 0x40;
	unsigned char firstLowerByte = 0x00;
	unsigned char secondLowerByte = 0x00;
	
	uint32_t freqreg = (frequency * AD_2POW28/AD_MCLK);
	
	firstLowerByte = freqreg;
	firstUpperByte |= ((freqreg >> 8) & 0x3f);
	secondLowerByte = freqreg >> 16;
	secondUpperByte |= ((freqreg >> 24) & 0x3f);
	
	sendCommandAD9833(firstUpperByte, firstLowerByte);
	sendCommandAD9833(secondUpperByte, secondLowerByte);
}

// phase in degrees
void setPhase(int phase)
{
	unsigned char upperByte = 0xC0;
	unsigned char lowerByte = 0x00;
	
	uint16_t phasereg = (phase * 4096/(2*M_PI));
	
	lowerByte = phasereg;
	upperByte |= ((phasereg >> 8) & 0x0f);
	
	sendCommandAD9833(upperByte, lowerByte);
}

void setMode(WaveType mode)
{
	unsigned char upperByte = 0x00;
	unsigned char lowerByte = 0x00;
	
	switch(mode)
	{
		case SINE:
			clearRegBit(lowerByte, AD_OPBITEN);
			clearRegBit(lowerByte, AD_MODE);
		break;
		case SQURE:
			setRegBit(lowerByte, AD_OPBITEN);
			clearRegBit(lowerByte, AD_MODE);
		break;
		case TRIANGLE:
			clearRegBit(lowerByte, AD_OPBITEN);
			setRegBit(lowerByte, AD_MODE);
		break;
	}
	
	sendCommandAD9833(upperByte, lowerByte);
}

void setRegBit(unsigned char *byte, int bit)
{
	if (bit > 7)
	{
		*byte |= 1 << (bit-8);
	} else
	{
		*byte |= 1 << bit;
	}
}

void clearRegBit(unsigned char *byte, int bit)
{
	if (bit > 7)
	{
		*byte &= ~(1 << (bit-8));
	} else
	{
		*byte &= ~(1 << bit);
	}
>>>>>>> Stashed changes
}