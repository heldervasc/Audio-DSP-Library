/************************************************************************
 
 Product: Portable Audio Dsp Library 
 Version: V0.0.1
 File: HanningWindow.cpp
 Creation date: 2010/08/10
 Author: Hélder Vasconcelos helder.vasc@e-2points.com 
 Description: Class Tester
 
 
 Copyright (c) 2010 Hélder Vasconcelos
 
 This library is free software; you can redistribute it and/or modify 
 it under the terms of the GNU Lesser General Public License as published by 
 the Free Software Foundation; either version 2.1 of the License, or 
 (at your option) any later version.
 
 This library is distributed in the hope that it will be useful, 
 but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
 or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License 
 for more details.
 
 You should have received a copy of the GNU Lesser General Public License 
 along with this library; if not, write to the Free Software Foundation, Inc., 
 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA 
 
 ****************************************************************************/

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



