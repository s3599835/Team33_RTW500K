/*
 * Design 3 - Group 33
 * RTW500k Function Generator
 * input.c
 */

#include "input.h"

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

int processInput(Control * control, OutputWaveForm *waveform)
{
	//Joel
	
	if (control->inputRead & (1<< FUNC_PIN))
	{
		//increment wavefunction
	}
	
	
	
	return 0;
}