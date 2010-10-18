/************************************************************************
 
 Product: Portable Audio Dsp Library 
 Version: V0.0.1
 File: FFT.h
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


#include "Utils.h"
#include "Complex.h"

#include <stdlib.h>

#ifndef FFT_H
#define FFT_H	 

enum FFT_direction {
	
	DIRECT_DIRECTION=1,
	INVERSE_DIRECTION=-1,
	
};


typedef FFT_direction FFT_Direction;

class FFT {

	
	public :

	FFT(Float32 SampleFrequency);
	
	~FFT();
	
	int AllocateFTBuffer(long nSamples);

	
	/////////////////////////////////
	//
	//		Direct Fourier Transform 
	//		input: Array of Complex Number
	//      output: Stored in results Array of Complexs;
	//
	////////////////////////////////
	
	
	int GetDFT(Complex *x,long nSamples,FFT_Direction dir);

	
	/////////////////////////////////
	//
	//		Cooley-Tukey FFT algorithm 
	//		input: Array of Complex Number
	//      output: Stored in results Array of Complexs;
	//
	////////////////////////////////
	
    void CT_FFT(Complex *x,long nSamples);
	
	Complex* FFT_get_twiddle_factors(int N);
	
	
	///////////////////////////////////////////////
	//
	// Sorrensen Split Radix FFT for real values
	// input : Array of Floats
	// ouput :  Array of Complex Stored in Results 
	//
	//////////////////////////////////////////////
	
	void RealSplitRadixFFT(Float32 *data,int n);
	
	
	///////////////////////////////////////////////
	//
	// Sorrensen Inverse Split Radix FFT for real values
	// input :	Results 
	// ouput :  Array of Floats 
	//
	//////////////////////////////////////////////
	
	void IRealSplitRadixFFT(Float32 *y,int n);
	

	
	
	void FreeFTBuffer();
	
	
	int SetSampleFrequency(Float32 SampleFrequency);
	Float32 GetSampleFrequency();
	

	Float32 GetFrequency(long n);
	Float32 GetMagnitude(long n);
	Float32 GetPhase(long n);
	
	private:
	
	
	Complex *results;
	
	Float32 SampleFrequency;
	long nSamples;
	

};


#endif

