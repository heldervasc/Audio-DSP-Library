/*
 *  Chebyshev1.h
 *  PU_Library
 *
 *  Created by Helder Vasconcelos on 10/10/16.
 *  Copyright 2010 AuGear. All rights reserved.
 *
 */
#ifndef CHEBYSHEVFILTER_H
#define CHEBYSHEVFILTER_H

#include "PoleFilter.h"

class Chebyshev1Filter : public PoleFilter
{
public:
	
	Chebyshev1Filter(UInt32 NPoles,UInt32 NChannels):PoleFilter(int (NPoles+1/2),NChannels){
		
		nPoles=UInt32 (NPoles+1/2);
		m_hint=hintBrent;
		
	}
	Chebyshev1Filter():PoleFilter(int (4+1/2),2){
		
		m_hint=hintBrent;
		nPoles=UInt32(4+1/2);
		
	}
	
	// cutoffFreq = freq / sampleRate
	
	virtual    void    Setup            ( Float32 cutoffFreq, Float32 rippleDb );
	
	virtual int        CountPoles        ( void );
	virtual int        CountZeroes        ( void );
	virtual Complex    GetPole            ( int i );
	virtual Complex    GetZero            ( int i );
	
protected:
	void            SetupCommon        ( Float32 rippleDb );
	virtual    Complex GetSPole        ( int i, Float32 wc );
	
protected:
	Float32    m_sgn;
	Float32    m_eps;
	UInt32 nPoles;
};


#endif

