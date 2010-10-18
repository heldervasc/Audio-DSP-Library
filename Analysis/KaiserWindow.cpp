/************************************************************************
 
 Product: Portable Audio Dsp Library 
 Version: V0.0.1
 File: KaiserWindow.cpp
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

#include "KaiserWindow.h"

//template<WindowType wtype, UInt32 NSamples>



KaiserWindow::KaiserWindow(): Window(KAISER_WINDOW,2048) {
	
	
	this->Beta=6.0;
	mBesselIOofBeta=BesselFunctionI0(this->Beta);
	
	
} 


KaiserWindow::KaiserWindow(UInt32 NSamples,double Beta): Window(KAISER_WINDOW,NSamples) {
	
	
	this->Beta=6.0;
	mBesselIOofBeta=BesselFunctionI0(this->Beta);
	
	
} 


void KaiserWindow::SetBeta(double Beta){
	
	this->Beta=Beta;
	mBesselIOofBeta=BesselFunctionI0(Beta);
	
}

double KaiserWindow::GetBeta(){
	
	
	return this->Beta;
	
}


void KaiserWindow::FillBuffer(){
	
	int i;
	double twom;
	for (i = 0; i <NSamples; i++) {
		
		twom=(2.0*i)/NSamples-1;
		this->buffer[i] = BesselFunctionI0(Beta * sqrt(1.0 -(twom*twom)))   /   mBesselIOofBeta;
		
	}
	
	
}


double KaiserWindow::BesselFunctionI0(double x){
	
	
	
	double denominator;
	double numerator;
	double z;
	
	if (x == 0.0) {
		return 1.0;
	} else {
		z = x * x;
		numerator = (z* (z* (z* (z* (z* (z* (z* (z* (z* (z* (z* (z* (z* 
																	 (z* 0.210580722890567e-22  + 0.380715242345326e-19 ) +
																	 0.479440257548300e-16) + 0.435125971262668e-13 ) +
															 0.300931127112960e-10) + 0.160224679395361e-7  ) +
													 0.654858370096785e-5)  + 0.202591084143397e-2  ) +
											 0.463076284721000e0)   + 0.754337328948189e2   ) +
									 0.830792541809429e4)   + 0.571661130563785e6   ) +
							 0.216415572361227e8)   + 0.356644482244025e9   ) +
					 0.144048298227235e10);
		
		denominator = (z*(z*(z-0.307646912682801e4)+
						  0.347626332405882e7)-0.144048298227235e10);
	}
	
	return -numerator/denominator;
}










