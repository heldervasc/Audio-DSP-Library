/*
 *  WelchWindow.cpp
 *  PU_Library
 *
 *  Created by Helder Vasconcelos on 10/10/15.
 *  Copyright 2010 AuGear. All rights reserved.
 *
 */

#include "WelchWindow.h"



void WelchWindow::FillBuffer(){

	// welch(i) = 1.0 - ((i-n/2)/(n/2)) * ((i-n/2)/(n/2))
	int i;
	 double w ;
	
	for (i = 0; i < this->NSamples; i++) {
		w= (i-this->NSamples/2)/(this->NSamples/2);
		this->buffer[i] = 1-(w*w);
	}


}



