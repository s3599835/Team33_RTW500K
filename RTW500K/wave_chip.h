/*
 * Design 3 - Group 33
 * RTW500k Function Generator
 * wave_chip.h
 */
#ifndef WAVE_CHIP_H
#define WAVE_CHIP_H

// Upper byte (AD_X-8)
#define AD_B28		13
#define AD_HLB		12
#define AD_FSELECT	11
#define AD_PSELECT	10
#define AD_RESET	8

// Lower byte (AD_X)
#define AD_SLEEP1	7
#define AD_SLEEP12	6
#define AD_OPBITEN	5
#define AD_DIV2		3
#define AD_MODE		1

#define AD_2POW28	(1 << 28)
#define AD_MCLK		25000000
#define AD_DEFAULT_FREQ 1000
#define AD_DEFAULT_PHASE 0

#include "utility.h"

int writeSPI(int chipselect);
int writeToAD9833(OutputWaveForm * waveform);
<<<<<<< Updated upstream
=======
void sendCommandAD9833(unsigned char byte1, unsigned char byte2);
void initAD9833();
void setRegBit(unsigned char *byte, int bit);
void clearRegBit(unsigned char *byte, int bit);
>>>>>>> Stashed changes

#endif