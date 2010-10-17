/*
 *   BiquadHighPass.h
 *  Library
 *
 *  Created by Helder Vasconcelos on 10/10/11.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef BIQUADHIGHPASS_H
#define BIQUADHIGHPASS_H

#include "BiquadFilter.h"


class BiquadHighPass: public BiquadFilter{


public:

	BiquadHighPass(UInt32 Nchan):BiquadFilter(Nchan){}
	BiquadHighPass():BiquadFilter(2){}
	
	void Setup            ( Float32 normFreq,Float32 q );
	void SetupFast        ( Float32 normFreq, Float32 q );
protected:
	void SetupCommon    ( Float32 sn, Float32 cs, Float32 q );





};


#endif
