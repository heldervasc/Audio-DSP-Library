/*
 *  BiquadPeakEq.h
 *  Library
 *
 *  Created by Helder Vasconcelos on 10/10/11.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef BIQUADPEAKEQ_H
#define BIQUADPEAKEQ_H

#include "BiquadFilter.h"


class BiquadPeakEq: public BiquadFilter{
	
	
	
	
public:

	BiquadPeakEq(UInt32 Nchan):BiquadFilter(Nchan){}
	BiquadPeakEq():BiquadFilter(2){};
	
	void Setup            ( Float32 normFreq, Float32 dB, Float32 bandWidth);
	void SetupFast        (Float32 normFreq, Float32 dB, Float32 bandWidth);
protected:
	void SetupCommon    (Float32 sn, Float32 cs, Float32 alph, Float32 A);
	
	
	
	
	
};


#endif

