/*
 * Design 3 - Group 33
 * RTW500k Function Generator
 * main.c
 */

#include "input.h"
#include "display.h"
#include "wave_chip.h"
#include "dig_pot.h"

// Could probably just do these in where ever
// it's getting called
int writeWave(OutputWaveForm * waveform)
{
	writeToAD9833(waveform);
	writeToMCP(waveform);
	return 0;
}

int setup(Control * cont, Display * display, OutputWaveForm * waveform)
{
	
	updateDisplay(display);
}

int main(void)
{
	// setupcont
	Control cont;
    Display display;
	OutputWaveForm waveform;
	
	setup(&cont, &display, &waveform);
    
	while (1) 
    {
		drawScreen(&display);
		getInput(&cont);
		
		processInput(&cont, &waveform);	
		
		writeWave(&waveform);
		calculateVoltages(&waveform);	
		updateDisplay(&display);	
		
		
    }
}

