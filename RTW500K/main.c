/*
 * RTW500K.c
 *
 * Created: 21/08/2020 9:43:00 AM
 * Author : Steve
 */ 

#include <avr/io.h>

//PORT B
//SPI STUFF
#define SCK 5
#define MOSI 4
//Chip Select Lines
#define CS_AD9833 2
#define CS_MTP 1

//LCD
//PORT C
#define LCD_ENABLE 0
#define LCD_REGISTERSELECT 1

#define LCD_D4 2
#define LCD_D5 3
#define LCD_D6 4
#define LCD_D7 5


//Buttons
//PORT D
#define UP_PIN 0
#define DOWN_PIN 1
#define LEFT_PIN 2
#define RIGHT_PIN 3
#define FUNC_PIN 4



typedef enum
{
	SINE, SQURE, TRIANGLE
	} WaveType;

typedef enum{
	UP, DOWN, LEFT, RIGHT, FUNCTION
} Buttons;

typedef enum {
	
	FREQUENCY, AMPLITUDE, OFFSET, WAVE
	
	} FunctionSelect;	
typedef struct {
	
	WaveType wavetype;
	int frequency;
	//Hold the current step digital pot
	int amplitudeIndex;
	float amplitude;
	int offsetIndex;
	float offset;
	
	} OutputWaveForm;
	
typedef struct {
	
	char frequency[6];
	char amplitude[6];
	char voltageOffset[6];
	//SQR SIN TRIG
	char wave[4];
	int cursorPositionx;
	int cursorPositiony;
	
	} Display;
	
typedef struct {
	
	//If the input has been read set high
	int inputChange;
	//Input that has been read;
	int inputRead;
	//Current parameeter select
	FunctionSelect currentFunction;
	
	} Control;
	


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

int drawScreen(Display *display)
{
	//Liam
	//Actually draw to the screen

	return 0;
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

int writeSPI (int chipselect)
{
	
}
int writeToAD9833 (OutputWaveForm * waveform)
{
	//Liam 
	return 0
}

int writeToMCP(OutputWaveForm * waveform)
{
	//Trung - 
	//Digital Pots
	return 0;
}

int writeWave(OutputWaveForm * waveform)
{
	writeToAD9833(waveform);
	writeToMCP(waveform);
	return 0
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
int updateDisplay(Display * display)
{
	//Stephen 
	//Function to update the display struct (not write to display)
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

