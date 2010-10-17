/*
 *  WindowedSincHighPass.cpp
 *  PU_Library
 *
 *  Created by Helder Vasconcelos on 10/10/14.
 *  Copyright 2010 AuGear. All rights reserved.
 *
 */

#include "WindowedSincHighPass.h"



void WindowedSincHighPass::Process( UInt32 frames , Float32 *dest, int skip=0 ){
	
	
	//Multiply  Window and GSync
	
	
	//	WindowedSincFilter
	
	int i;
	// 1. Generate lowpass filter
	
	this->wind->Mult(this->sinc, dest);
	
	// 2. Spectrally invert (negate all samples and add 1 to center sample) lowpass filter
	// = delta[n-((N-1)/2)] - h[n], in the time domain

	for (i = 0; i < this->NSamples; i++) {
		dest[i] *= -1.0;	// = 0 - h[i]
	}
	dest[(this->NSamples-1)/2] += 1.0;	// = 1 - h[(N-1)/2]
	
	
	
	return;
	
}




