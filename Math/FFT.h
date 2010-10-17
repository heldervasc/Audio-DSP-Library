/*
 *  FFT.h
 *  Equalizer
 *
 *  Created by Helder Vasconcelos on 10/09/30.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */




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

