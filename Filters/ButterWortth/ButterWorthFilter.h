/*
 *  ButterWorth.h
 *  PU_Library
 *
 *  Created by Helder Vasconcelos on 10/10/16.
 *  Copyright 2010 AuGear. All rights reserved.
 *
 */

#ifndef BUTTERWFIR_H
#define BUTTERWFIR_H

#include "PoleFilter.h"

class ButterWorthFilter : public PoleFilter
{
public:
	
	ButterWorthFilter(UInt32 NPoles,UInt32 NChannels):PoleFilter(int (NPoles+1/2),NChannels){

		nPoles=UInt32 (NPoles+1/2);
		m_hint=hintPassband;
		
	}
	ButterWorthFilter():PoleFilter(int (4+1/2),2){
		
		m_hint=hintPassband;
		nPoles=UInt32(4+1/2);
	
	}
	
	// cutoffFreq = freq / sampleRate
	
	void            Setup            ( Float32 cutoffFreq );
	
	virtual int        CountPoles        ( void );
	virtual int        CountZeroes        ( void );
	virtual Complex    GetPole            ( int i );
	
protected:
	Complex GetSPole        ( int i, Float32 wc );
	
	UInt32 nPoles;
	
};


#endif

