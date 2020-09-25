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
	DDRB |= (1<<MOSI)|(1<<SCK)|(1<<CS_AD9833)|(1<<CS_MTP);
	PORTB |= 1 << CS_AD9833;	//9833 CS Active Low
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);

	initAD9833();
	lcdInit();

	return 0;
}

int main(void)
{
	// setupcont
	Control cont = {
		.inputChange = 0, 
		.inputRead = 0, 
		.currentFunction = FREQUENCY	
	};
	OutputWaveForm waveform = {
		.wavetype = SQURE,
		.frequency = AD_DEFAULT_FREQ, //1 kHz
		.amplitudeIndex = 0,
		.amplitude = 5.0f,
		.offsetIndex = 128,
		.offset = 0.0f
	};
    Display display = {
		.frequency = {'0', '0', '1', '0', '0', '0'},
		.amplitude = {'0', '5', '.', '0'},
		.voltageOffset = {'0', '.', '0'},
		.wave = {'S', 'Q', 'R'},
		.cursorPositionx = 2,
		.cursorPositiony = 0
	};
	
	setup(&cont, &display, &waveform);
    
	while (1) 
    {
		drawScreen(&display);
		getInput(&cont);
		
		processInput(&cont, &waveform);	
		
		writeWave(&waveform);
		calculateVoltages(&waveform);	
		updateDisplay(&display, &waveform);	
		
		
    }
}

