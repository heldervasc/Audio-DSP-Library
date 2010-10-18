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

#include "WindowedSincBandStop.h"

void WindowedSincBandStop::Process( UInt32 frames , Float32 *dest, int skip=0 ){
	
	

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
		
	delete []h1;
	delete []h2;
	
	return;
	
}




