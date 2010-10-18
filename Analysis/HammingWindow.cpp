/*********************************************************
//
// Module: Audio DSP Library
// Version: V0.1
// File: HammingWindow.cpp
// Creation date: 2010/10/18
// Author: Hélder Vasconcelos
// Description:
//
*******************************************************************/
#include "HammingWindow.h"


void HammingWindow::FillBuffer(){
	
	
	
	
	int i;
	const double M = this->NSamples-1;
	
	
	for (i = 0; i < this->NSamples; i++) {
		
		this->buffer[i] = 0.54 - (0.46*cos(2.0*M_PI*(double)i/M));
	
	}
	
	return;
	
	
	
}

