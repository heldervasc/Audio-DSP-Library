/*
 *  BiquadLowPass.h
 *  Library
 *
 *  Created by Helder Vasconcelos on 10/10/11.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef BIQUADLOWPASS_H
#define BIQUADLOWPASS_H

#include "BiquadFilter.h"


class BiquadLowPass : public BiquadFilter
{
	
public:
	
	BiquadLowPass(UInt32 Nchan):BiquadFilter(Nchan){}
	BiquadLowPass():BiquadFilter(2){}
	
	//~BiquadLowPass();
	
	void Setup            ( Float32 normFreq, Float32 q );
	void SetupFast        ( Float32 normFreq, Float32 q );
	
protected:
	void SetupCommon    ( Float32 sn, Float32 cs, Float32 q );
};

#endif

