/*
 *  BiquadBandPass1.h
 *  Library
 *
 *  Created by Helder Vasconcelos on 10/10/11.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef BIQUADBANDPASS1_H
#define BIQUADBANDPASS1_H

#include "BiquadFilter.h"


class BiquadBandPass1: public BiquadFilter{
	
	
	
	
public:

	BiquadBandPass1(UInt32 Nchan):BiquadFilter(Nchan){}
	BiquadBandPass1():BiquadFilter(2){}
	
	void Setup            ( Float32 normFreq,Float32 q );
	void SetupFast        ( Float32 normFreq, Float32 q );
protected:
	void SetupCommon    ( Float32 sn, Float32 cs, Float32 q );
	
	
	
	
	
};


#endif

