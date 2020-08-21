/*
 * Design 3 - Group 33
 * RTW500k Function Generator
 * dig_pot.c
 */

#include "dig_pot.h"

int writeToMCP(OutputWaveForm * waveform)
{
	//Trung -
	//Digital Pots
	return 0;
}

int calculateVoltages(OutputWaveForm * waveform)
{
	//Trung
	//Calculate the floating point voltage repersentation from voltageindex etc
	//potvalue = index*1K;
	//voltage divider rule to calculate offset Vout  = vin* potvalue/(refrenceValue + potvalue);
	//gainofamp = invertingopamp
	//output voltage = peaktoopeakofwavechip * gainofAmp
	return 0;
}