/*
 *  TrapezoidWindow.cpp
 *  PU_Library
 *
 *  Created by Helder Vasconcelos on 10/10/15.
 *  Copyright 2010 AuGear. All rights reserved.
 *
 */

#include "TrapezoidWindow.h"



TrapezoidWindow::TrapezoidWindow():Window(TRAPEZOID_WINDOW,2048)  {
	
	this->Fade=0.25;
}


TrapezoidWindow::TrapezoidWindow(UInt32 NSamples,double Fade):Window(TRAPEZOID_WINDOW,NSamples)  {
	
	this->Fade=Fade;
}



void TrapezoidWindow::FillBuffer(){
	
	
	int i;
	
	for (i = 0; i <this->NSamples; i++) {
		this->buffer[i] = (2.0*this->Fade) * (1 - fabs(2. * i-1));;
	}
	
	
	
	
	
}




