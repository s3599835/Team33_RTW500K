/*
 * Design 3 - Group 33
 * RTW500k Function Generator
 * wave_chip.h
 */
#ifndef WAVE_CHIP_H
#define WAVE_CHIP_H

#include "utility.h"

int writeSPI(int chipselect);
int writeToAD9833(OutputWaveForm * waveform);
void sendCommandAD9833(unsigned char byte1, unsigned char byte2);

#endif