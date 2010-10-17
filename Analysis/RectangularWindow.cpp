/*
 *  RectangularWindow.cpp
 *  PU_Library
 *
 *  Created by Helder Vasconcelos on 10/10/15.
 *  Copyright 2010 AuGear. All rights reserved.
 *
 */

#include "RectangularWindow.h"


void RectangularWindow::FillBuffer(){
	
	
	
	int i;
	
	for (i = 0; i <this->NSamples; i++) {
		this->buffer[i] = 1;
	}
	
	
	
}


