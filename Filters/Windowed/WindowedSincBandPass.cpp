/*
 *  WindowedSincBandPass.cpp
 *  PU_Library
 *
 *  Created by Helder Vasconcelos on 10/10/14.
 *  Copyright 2010 AuGear. All rights reserved.
 *
 */

#include "WindowedSincBandPass.h"

void WindowedSincBandPass::Process( UInt32 frames , Float32 *dest, int skip=0 ){
	
	
	//Multiply  Window and GSync
	
	
	//	WindowedSincFilter
	

	int i;
	Float32 *h1 = new Float32[this->NSamples];
	Float32 *h2 = new Float32[this->NSamples];
	
	
	
	this->wind->Mult(this->sinc, h1);
	
	this->wind->Mult(this->sinc, h2);
	
	
	for (i = 0; i < this->NSamples; i++) {
		h2[i] *= -1.0;	// = 0 - h[i]
	}
	
	h2[(this->NSamples-1)/2] += 1.0;	// = 1 - h[(N-1)/2]
	
	
	for (i = 0; i < this->NSamples; i++) {
		
		dest[i] = h1[i] + h2[i];
		
	}

	for (i = 0; i < this->NSamples; i++) {
		dest[i] *= -1.0;	// = 0 - h[i]
	}
	dest[(this->NSamples-1)/2] += 1.0;	// = 1 - h[(N-1)/2]
	
	delete []h1;
	delete []h2;
	
	
	
	return;
	
}


