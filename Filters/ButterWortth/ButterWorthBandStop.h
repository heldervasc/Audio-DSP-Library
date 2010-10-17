/*
 *  ButterWorthBandStop.h
 *  PU_Library
 *
 *  Created by Helder Vasconcelos on 10/10/16.
 *  Copyright 2010 AuGear. All rights reserved.
 *
 */

#ifndef BUTTERWBANDSTOP_H
#define BUTTERWBANDSTOP_H

#include "ButterWorthFilter.h"

// Band Stop Butterworth filter
// Stable up to 109 pairs

class ButterBandStop : public ButterWorthFilter
{
public:
	
	// centerFreq = freq / sampleRate
	// normWidth  = freqWidth / sampleRate
	
	ButterBandStop(UInt32 NPairs,UInt32 NChannels):ButterWorthFilter(NPairs*2,NChannels){ this->NPairs=NPairs;}
	ButterBandStop():ButterWorthFilter(4,2){this->NPairs=2;}
	void    Setup            ( Float32 centerFreq, Float32 normWidth );
	
	virtual int        CountPoles        ( void );
	virtual int        CountZeroes        ( void );
	virtual Complex GetPole            ( int i );
	virtual Complex GetZero            ( int i );
	
protected:
	Float32    PassbandHint    ( void );
	UInt32 NPairs;
};


#endif


