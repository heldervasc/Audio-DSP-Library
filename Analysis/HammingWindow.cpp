/*
 *  HammingWindow.cpp
 *  PU_Library
 *
 *  Created by Helder Vasconcelos on 10/10/15.
 *  Copyright 2010 AuGear. All rights reserved.
 *
 */

#include "HammingWindow.h"


void HammingWindow::FillBuffer(){
	
	
	
	
	int i;
	const double M = this->NSamples-1;
	
	
	for (i = 0; i < this->NSamples; i++) {
		
		this->buffer[i] = 0.54 - (0.46*cos(2.0*M_PI*(double)i/M));
	
	}
	
	return;
	
	
	
}

