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

#endif