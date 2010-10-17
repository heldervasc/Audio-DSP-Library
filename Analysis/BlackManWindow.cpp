/*
 *  BlackManWindow.cpp
 *  PU_Library
 *
 *  Created by Helder Vasconcelos on 10/10/15.
 *  Copyright 2010 AuGear. All rights reserved.
 *
 */

#include "BlackManWindow.h"


void BlackManWindow::FillBuffer(){
	
	
	int i;
	const double M = this->NSamples-1;
	
	for (i = 0; i < this->NSamples; i++) {
		this->buffer[i] = 0.42 - (0.5 * cos(2.0*M_PI*(double)i/M)) + (0.08*cos(4.0*M_PI*(double)i/M));
	}
	
	
	
	
}

