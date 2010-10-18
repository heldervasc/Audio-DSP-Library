/*********************************************************
//
// Module: Audio DSP Library
// Version: V0.1
// File: BartletWindow.cpp
// Creation date: 2010/10/18
// Author: Hélder Vasconcelos 
// Description: 
//
*******************************************************************/

#include "BartletWindow.h"


void BartletWindow::FillBuffer() {
	

	int i;
	
	for (i = 0; i <this->NSamples; i++) {
	
		
		if (i<=NSamples/2){
		
			this->buffer[i]=2*i/NSamples;
		}else {
			this->buffer[i]=1-2*i/NSamples;
		}

	}
	
	
}

