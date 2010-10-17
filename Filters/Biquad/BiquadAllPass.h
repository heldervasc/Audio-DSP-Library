/*
 *  BiquadAllPass.h
 *  Library
 *
 *  Created by Helder Vasconcelos on 10/10/11.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef BIQUADALLPASS_H
#define BIQUADALLPASS_H

#include "BiquadFilter.h"




class BiquadAllPass: public BiquadFilter{
	
	
	
	
public:
	BiquadAllPass(UInt32 Nchan):BiquadFilter(Nchan){}
	BiquadAllPass():BiquadFilter(2){}
	
	void Setup            ( Float32 normFreq,Float32 q );
	void SetupFast        ( Float32 normFreq, Float32 q );
protected:
	void SetupCommon    ( Float32 sn, Float32 cs, Float32 q );
	
	
	
	
	
};


#endif

