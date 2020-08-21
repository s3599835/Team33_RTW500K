/*
 * Design 3 - Group 33
 * RTW500k Function Generator
 * dig_pot.h
 */
#ifndef DIG_POT_H
#define DIG_POT_H

#include "utility.h"

int writeToMCP(OutputWaveForm * waveform);
int calculateVoltages(OutputWaveForm * waveform);