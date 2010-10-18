/************************************************************************
 
 Product: Portable Audio Dsp Library 
 Version: V0.0.1
 File: Window.h
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

#ifndef WINDOW_H
#define WINDOW_H	

#include "Utils.h"

enum Windowtype{


	BLACKMAN_WINDOW=0,
	HANNING_WINDOW=1,
	HAMMING_WINDOW=2,
	KAISER_WINDOW=3,
	RECTANGULAR_WINDOW=4,
	TRAPEZOID_WINDOW=5,
	WELCH_WINDOW=6,
	BARTLET_WINDOW=7,
	
};


typedef Windowtype WindowType;



class Window{


public:
	
	Window();
	
	Window(WindowType wtype,UInt32 NSamples);

	~Window();
	
	
	void Mult(Float32 *data,Float32 *out);
	void Div(Float32 *data,Float32 *out);
	void Sub(Float32 *data,Float32 *out);
	void Add(Float32 *data,Float32 *out);

	void Mult(double *data,double *out);
	void Div(double *data,double *out);
	void Sub(double *data,double *out);
	void Add(double *data,double *out);
	
	
	WindowType GetType();
	double GetValue(unsigned int i);
	UInt32 GetNSamples();
	
	
	virtual void FillBuffer()=0;	
	
	
	
	UInt32 NSamples;
	WindowType type;
	
	double *buffer;

	protected :
	

	
};

#endif

