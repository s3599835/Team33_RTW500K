/*
* Design 3 - Group 33
* RTW500k Function Generator
* input.c
*/

#include "input.h"
#include <math.h>

int getInput(Control *cont){
	
	//Joel
	
	int new;
	while(1)
	{
		//Read the inputs;
		//new = butons;
		if(new != cont->inputRead)
		{
			cont->inputRead = new;
			cont->inputChange = 1;
			break;
		}
		
	}
}

int processInput(Control *control, OutputWaveForm *waveform, Display *disp)
{
	//Joel
	
	//initial cursor pos
	int curPos = disp->cursorPositionx;
	
	//up button pressed
	if (control->inputRead & (1<< UP_PIN))
	{

		//move up changes values depending on cursor pos
		//current selection
		switch(control->currentFunction)
		{
			case FREQUENCY:
			changeInput(waveform, curPos, FREQUENCY, 1);
			break;
			
			case AMPLITUDE:
			changeInput(waveform, curPos, AMPLITUDE, 1);
			break;
			
			case OFFSET:
			changeInput(waveform, curPos, OFFSET, 1);
			break;
			
			case WAVE:
			//cycle through wavetypes
			if(waveform->wavetype == SINE){
				waveform->wavetype = TRIANGLE;
			}
			
			if(waveform->wavetype == TRIANGLE){
				waveform->wavetype = SQURE;
			}
			
			if(waveform->wavetype == SQURE){
				waveform->wavetype = SINE;
			}
			break;
		}
	}
	
	//down button pressed
	if (control->inputRead & (1<< DOWN_PIN))
	{
		//move down changes values depending on cursor pos
		//current selection
		switch(control->currentFunction)
		{
			case FREQUENCY:
			changeInput(waveform, curPos, FREQUENCY, 2);
			break;
			
			case AMPLITUDE:
			changeInput(waveform, curPos, AMPLITUDE, 2);
			break;
			
			case OFFSET:
			changeInput(waveform, curPos, OFFSET, 2);
			break;
			
			case WAVE:
			//cycle through wave types
			if(waveform->wavetype == SINE){
				waveform->wavetype = SQURE;
			}
			
			if(waveform->wavetype == TRIANGLE){
				waveform->wavetype = SINE;
			}
			
			if(waveform->wavetype == SQURE){
				waveform->wavetype = TRIANGLE;
			}
			break;
		}
	}
	
	//left button pressed
	if (control->inputRead & (1<< LEFT_PIN))
	{
		//move left changes cursor
		//current selection
		switch(control->currentFunction)
		{
			case FREQUENCY:
			//ensure cursor cant go past min
			if(curPos != MIN_FREQ){
				disp->cursorPositionx = curPos - 1;
			}
			break;
			
			case AMPLITUDE:
			//avoid decimal
			if(curPos == 5){
				disp->cursorPositionx = curPos - 2;
			}
			if(curPos == 3){
				disp->cursorPositionx = curPos - 1;
			}
			break;
			
			case OFFSET:
			//avoid decimal
			if(curPos == 14){
				disp->cursorPositionx = curPos - 2;
			}
			break;
			
			case WAVE:
			//nothing for wavetype
			break;
		}
	}
	
	//right button pressed
	if (control->inputRead & (1<< RIGHT_PIN))
	{
		//move right changes cursor
		//current selection
		switch(control->currentFunction)
		{
			case FREQUENCY:
			//ensure cursor cant go past max
			if(curPos != MAX_FREQ){
				disp->cursorPositionx = curPos + 1;
			}
			break;
			
			case AMPLITUDE:
			//avoid decimal
			if(curPos == 3){
				disp->cursorPositionx = curPos + 2;
			}
			if(curPos == 2){
				disp->cursorPositionx = curPos + 1;
			}
			break;
			
			case OFFSET:
			//avoid decimal
			if(curPos == 12){
				disp->cursorPositionx = curPos + 2;
			}
			break;
			
			case WAVE:
			//nothing for wavetype
			break;
		}
	}
	//wavefunction button pressed causes modes to function.
	//also resets cursor position to leftmost place.
	if (control->inputRead & (1<< FUNC_PIN))
	{
		//increment wavefunction
		//changes function selected on screen
		switch(control->currentFunction)
		{
			case FREQUENCY:
			control->currentFunction = AMPLITUDE;
			disp->cursorPositionx = 2;
			disp->cursorPositiony = 1;
			break;
			
			case AMPLITUDE:
			control->currentFunction = WAVE;
			disp->cursorPositionx = 11;
			disp->cursorPositiony = 0;
			break;
			
			case WAVE:
			control->currentFunction = OFFSET;
			disp->cursorPositionx = 2;
			disp->cursorPositiony = 1;
			break;
			
			case OFFSET:
			control->currentFunction = FREQUENCY;
			disp->cursorPositionx = 12;
			disp->cursorPositiony = 0;
			break;
		}
	}
	
	return 0;
}

int changeInput(OutputWaveForm * waveform, int curPos, FunctionSelect funct, int type)
{
	//rightmost pos is max and left is min
	//decimal skipping is done in left/right buttons
	//add base 10 power position to number
	
	//increase value
	if(type == 1)
	{
		switch(funct)
		{
			case FREQUENCY:
			if(digitAtPos(waveform->frequency, curPos) != 9)
			{
				waveform->frequency = waveform->frequency + pow(10, MAX_FREQ-curPos);
				//upper boundary of 500k for freq
				if(waveform->frequency > 500000){
					waveform->frequency = 500000;
				}
			}
			break;
			
			case AMPLITUDE:
			if(digitAtPos(waveform->amplitude, curPos) != 9)
			{
				//three pos, decimal is separate first
				if(curPos == 5){
					waveform->amplitude = waveform->amplitude + pow(10, -1);
				}
				//other two pos are together
				else{
					waveform->amplitude = waveform->amplitude + pow(10, 3 - curPos);
				}
			}
			break;
			
			case OFFSET:
			if(digitAtPos(waveform->offset, curPos) != 9)
			{
				//only 2 positions for offset value (12[ones] and 14[tenths])
				if(curPos == 14){
					waveform->offset = waveform->offset + pow(10, -1);
				}
				else{
					waveform->offset = waveform->offset + pow(10, -0);
				}	
			}
			break;
		}
		
	}
	//decrease value
	else if(type == 2){
		switch(funct)
		{
			case FREQUENCY:
			if(digitAtPos(waveform->frequency, curPos) != 0)
			{
				waveform->frequency = waveform->frequency - pow(10, MAX_FREQ-curPos);
			}
			break;
			
			case AMPLITUDE:
			if(digitAtPos(waveform->amplitude, curPos) != 0)
			{
				//three pos, decimal is separate first
				if(curPos == 5){
					waveform->amplitude = waveform->amplitude - pow(10, -1);
				}
				//other two pos are together
				else{
					waveform->amplitude = waveform->amplitude - pow(10, 3 - curPos);
				}
			}
			break;
			
			case OFFSET:
			if(digitAtPos(waveform->offset, curPos) != 0)
			{
				//only 2 positions for offset value (12[ones] and 14[tenths])
				if(curPos == 14){
					waveform->offset = waveform->offset - pow(10, -1);
				}
				else{
					waveform->offset = waveform->offset - pow(10, -0);
				}
			}
			break;
		}
	}
	else{
		//should never reach here
		return -1;
	}
	
	return 0;
}


//Function returns digit to stop overflow/underflow when calculating (9 and 0)
int digitAtPos(int num, int pos)
{
	//cut digits off, find remainder when / 10.
	int n = num/pow(10, pos);
	n = n % 10;
	return n;
}