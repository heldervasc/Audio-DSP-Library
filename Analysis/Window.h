/*
 *  Window.h
 *  PU_Library
 *
 *  Created by Helder Vasconcelos on 10/10/14.
 *  Copyright 2010 AuGear. All rights reserved.
 *
 */
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

