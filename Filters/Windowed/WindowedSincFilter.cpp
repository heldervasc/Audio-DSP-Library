/*
 *  WindowedFilter.cpp
 *  PU_Library
 *
 *  Created by Helder Vasconcelos on 10/10/14.
 *  Copyright 2010 AuGear. All rights reserved.
 *
 */

#include "WindowedSincFilter.h"



WindowedSincFilter::~WindowedSincFilter(){
	
	
	
	if(sinc){
		
		free(sinc);
		
		
	}
}



void WindowedSincFilter::GenSync(UInt32 NSamples, Float32 normCutFreq ){
	
	
	int i;
	const Float32 M = NSamples-1;
	Float32 n;
	
	
	if (sinc){
		
		free(sinc);
		
	}
	sinc=malloc(NSamples*sizeof(Float32));
	
	// Generate sinc delayed by (N-1)/2
	
	for (i = 0; i < NSamples; i++) {
		if (i == M/2.0) {
			sinc[i] = 2.0 * normCutFreq;
		}
		else {
			n = (Float32)i - M/2.0;
			sinc[i] = sin(2.0*M_PI*normCutFreq*n) / (M_PI*n);
		}
	}        
	
	return;
	
}





void WindowedSincFilter::SetupWSFIR(UInt32 NSamples,WindowType wtype,Float32 f0,Float32 f1){
	
	
	
	
	if (wind){
		
		if(wind->NSamples!=NSamples||wind->type!=wtype){
			
			delete wind;
			
			wind =(HammingWindow *)new HammingWindow(NSamples);
								
			
		}
		
	}else {
		
		
	}
	
	if (sinc){
		
		if(this->NSamples!=NSamples||this->f0!=f0){
			
			this->GenSync(NSamples,f0);
			
		}
		
	}else {
		
		this->GenSync(NSamples,f0);
	}
	
	
	this->wtype=wtype;	
	this->NSamples=NSamples;
	this->f0=f0;
	this->f1=f1;
	
	
}



