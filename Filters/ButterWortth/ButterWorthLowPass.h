/*
 *  ButterWorthLowPass.h
 *  PU_Library
 *
 *  Created by Helder Vasconcelos on 10/10/16.
 *  Copyright 2010 AuGear. All rights reserved.
 *
 */
#ifndef BUTTERWLOWPASS_H
#define BUTTERWLOWPASS_H

// Low Pass Butterworth filter
// Stable up to 53 poles (frequency min=0.13% of Nyquist)
#include "ButterWorthFilter.h"

class ButterLowPass : public ButterWorthFilter
{
public:
	
	ButterLowPass(UInt32 NPoles,UInt32 NChannels):ButterWorthFilter(NPoles,NChannels){ }
	ButterLowPass():ButterWorthFilter(int (4+1/2),2){}
	
	Complex GetZero            ( int i );
	
protected:
	Float32    PassbandHint    ( void );
};

//--------------------------------------------------------------------------

#endif


