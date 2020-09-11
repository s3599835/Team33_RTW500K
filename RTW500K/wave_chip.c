/*
 * Design 3 - Group 33
 * RTW500k Function Generator
 * wave_chip.c
 */

#include "wave_chip.h"

/** 
 *	Writes the user's desired waveform as specified by
 * the waveform struct to the AD9833, by calling the 
 * internal set frequency and set mode functions, and 
 * ensuring that frequency and phase channels 0 are 
 * selected, as these are the only ones required.
 */
void writeToAD9833 (OutputWaveForm * waveform)
{
	unsigned char upperByte = 0x00;
	unsigned char lowerByte = 0x00;
	
	// Write freq in 2 consecutive words
	setRegBit(&upperByte, AD_B28);
	sendCommandAD9833(upperByte, lowerByte);
	
	setFrequency(waveform->frequency);
	setMode(waveform->wavetype);
	
	// Select freq. and phase source registers
	clearRegBit(&upperByte, AD_FSELECT);
	clearRegBit(&upperByte, AD_PSELECT);
	sendCommandAD9833(upperByte, lowerByte);
	
	// Must wait 8 MCLK cycles for output to propagate
	_delay_us((double)8/AD_MCLK);
}

/** 
 *	Sends a 16-bit/2-byte command to the AD9833 by pulling 
 * the active-low 9833 chip select line low and pushing the 
 * bytes out over the SPI data line, then returning the chip
 * select high.
 */
void sendCommandAD9833(unsigned char byte1, unsigned char byte2)
{
	PORTB &= ~(1<<CS_AD9833);
	SPDR = byte1;
	while(!(SPSR & (1<<SPIF)));
	
	SPDR = byte2;
	while(!(SPSR & (1<<SPIF)));
	PORTB |= 1<<CS_AD9833;
	
}

/** 
 *	Follows the AD9833 data sheet information to set the 9833's
 * registers to known values at power on or reset.
 */
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
	
	// Clear reset, select channel 0 for freq. and phase.
	clearRegBit(&upperByte, AD_RESET);
	clearRegBit(&upperByte, AD_FSELECT);
	clearRegBit(&upperByte, AD_PSELECT);
	sendCommandAD9833(upperByte, lowerByte);
	
	// Must wait 8 MCLK cycles for output to propagate
	_delay_us((double)8/AD_MCLK);
}

/** 
 *	Sets the 2x 14-bit frequency registers to the appropriate
 * value to represent the frequency argument as determined by
 * the equation defined in the data sheet
 */
void setFrequency(int frequency)
{
	unsigned char firstUpperByte = 0x40;
	unsigned char secondUpperByte = 0x40;
	unsigned char firstLowerByte = 0x00;
	unsigned char secondLowerByte = 0x00;
	
	uint32_t freqreg = (frequency * AD_2POW28/AD_MCLK);
	
	firstLowerByte = freqreg;
	firstUpperByte |= ((freqreg >> 8) & 0x3f);
	secondLowerByte = freqreg >> 14;
	secondUpperByte |= ((freqreg >> 22) & 0x3f);
	
	sendCommandAD9833(firstUpperByte, firstLowerByte);
	sendCommandAD9833(secondUpperByte, secondLowerByte);
}

/** 
 *	Sets the 12-bit phase register to the appropriate
 * value to represent the phase (degrees) argument as determined by
 * the equation defined in the data sheet
 */
void setPhase(int phase)
{
	unsigned char upperByte = 0xC0;
	unsigned char lowerByte = 0x00;
	
	uint16_t phasereg = (phase * 4096/(2*M_PI));
	
	lowerByte = phasereg;
	upperByte |= ((phasereg >> 8) & 0x0f);
	
	sendCommandAD9833(upperByte, lowerByte);
}

/** 
 *	Sets or clears the appropriate bits in the AD9833 control register
 * to output the desired waveform as determined by the enumerated mode input.
 */
void setMode(WaveType mode)
{
	unsigned char upperByte = 0x00;
	unsigned char lowerByte = 0x00;
	
	switch(mode)
	{
		case SINE:
			clearRegBit(&lowerByte, AD_OPBITEN);
			clearRegBit(&lowerByte, AD_MODE);
		break;
		case SQURE:
			setRegBit(&lowerByte, AD_OPBITEN);
			clearRegBit(&lowerByte, AD_MODE);
		break;
		case TRIANGLE:
			clearRegBit(&lowerByte, AD_OPBITEN);
			setRegBit(&lowerByte, AD_MODE);
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
}