/*
 *  WindowedFilter.h
 *  PU_Library
 *
 *  Created by Helder Vasconcelos on 10/10/14.
 *  Copyright 2010 AuGear. All rights reserved.
 *
 */
/*
 Windowed Sinc FIR Generator
 Bob Maling (BobM.DSP@gmail.com)
 Contributed to musicdsp.org Source Code Archive
 Last Updated: April 12, 2005
 
 Usage:
 Lowpass:	wsfirLP(h, N, WINDOW, fc)
 Highpass:	wsfirHP(h, N, WINDOW, fc)
 Bandpass:	wsfirBP(h, N, WINDOW, fc1, fc2)
 Bandstop:	wsfirBS(h, N, WINDOW, fc1, fc2)
 
 where:
 h (double[N]):	filter coefficients will be written to this array
 N (int):		number of taps
 WINDOW (int):	Window (W_BLACKMAN, W_HANNING, or W_HAMMING)
 fc (double):	cutoff (0 < fc < 0.5, fc = f/fs)
 --> for fs=48kHz and cutoff f=12kHz, fc = 12k/48k => 0.25
 
 fc1 (double):	low cutoff (0 < fc < 0.5, fc = f/fs)
 fc2 (double):	high cutoff (0 < fc < 0.5, fc = f/fs)
 
 
 Windows included here are Blackman, Hanning, and Hamming. Other windows	can be
 added by doing the following:
 1. "Window type constants" section: Define a global constant for the new window.
 2. wsfirLP() function: Add the new window as a case in the switch() statement.
 3. Create the function for the window
 
 For windows with a design parameter, such as Kaiser, some modification
 will be needed for each function in order to pass the parameter.
 
 
 */
#ifndef WINDOWEDSFIR_H
#define WINDOWEDSFIR_H

#include "CascadeStages.h"
#include "Utils.h"
#include "Window.h"
#include "HammingWindow.h"

class WindowedSincFilter{
	
		
public:
	
	WindowedSincFilter(int channels){
	
		this->NChan=channels;
	}
	WindowedSincFilter(){
		
		this->NChan=2;
	}	
	
	~WindowedSincFilter();

virtual void Process( UInt32 frames , Float32 *dest, int skip=0 )=0;

void SetupWSFIR(UInt32 NSamples,WindowType wtype,Float32 f0,Float32 f1);
	
void GenSync(UInt32 NSamples, Float32 normCutFreq );

	
protected:
	
	Float32 *sinc;
	
	WindowType wtype;
	UInt32 NChan;
	UInt32 NSamples;
	
	Window *wind;
	
	Float32 f0;
	Float32 f1;

private:

		
	
	
			
		
};

#endif



