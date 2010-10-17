/*
 *  BiquadBandStop.h
 *  Library
 *
 *  Created by Helder Vasconcelos on 10/10/11.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef BIQUADBANDSTOP_H
#define BIQUADBANDSTOP_H

#include "BiquadFilter.h"


class BiquadBandStop: public BiquadFilter{
	
	
	
	
public:
	
	BiquadBandStop(UInt32 Nchan):BiquadFilter(Nchan){}
	BiquadBandStop():BiquadFilter(2){}
	
	void Setup            ( Float32 normFreq,Float32 q );
	void SetupFast        ( Float32 normFreq, Float32 q );
protected:
	void SetupCommon    ( Float32 sn, Float32 cs, Float32 q );
	
	
	
	
	
};


#endif

