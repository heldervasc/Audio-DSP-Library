/*
 *  WindowedSincLowPass.cpp
 *  PU_Library
 *
 *  Created by Helder Vasconcelos on 10/10/14.
 *  Copyright 2010 AuGear. All rights reserved.
 *
 */

#include "WindowedSincLowPass.h"


void WindowedSincLowPass::Process( UInt32 frames , Float32 *dest, int skip){
	
	
	//Multiply  Window and GSync
	
	
	//	WindowedSincFilter
	

	
	this->wind->Mult(this->sinc, dest);
	
	
	return;
	
}




