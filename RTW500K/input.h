/*
 * Design 3 - Group 33
 * RTW500k Function Generator
 * input.h
 */

#ifndef INPUT_H
#define INPUT_H

#include "utility.h"

//Max/min cursor pos
#define MAX_FREQ 7
#define MIN_FREQ 2


int getInput(Control *cont);
int processInput(Control *control, OutputWaveForm *waveform, Display *disp);
int changeInput(OutputWaveForm * waveform, int curPos, FunctionSelect funct, int type)
int digitAtPos(int num, int pos)

#endif