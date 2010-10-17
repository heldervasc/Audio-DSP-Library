/*
 *  Chebyshev1BandStop.h
 *  PU_Library
 *
 *  Created by Helder Vasconcelos on 10/10/17.
 *  Copyright 2010 AuGear. All rights reserved.
 *
 */

#ifndef CHEBYSHEVBANDSTOP_H
#define CHEBYSHEVBANDSTOP_H

#include "Chebyshev1Filter.h"

class Chebyshev1BandStop : public Chebyshev1Filter
{
public:
	
	Chebyshev1BandStop(UInt32 NPairs,UInt32 NChannels):Chebyshev1Filter(NPairs*2,NChannels){ 
		
		this->NPairs=NPairs;
		m_sgn=1;
        m_hint=hintPassband;
		
	}
	Chebyshev1BandStop():Chebyshev1Filter(4,2){
		
		this->NPairs=2;
		m_sgn=1;
        m_hint=hintPassband;
	}
	
	
	void    Setup            ( Float32 centerFreq, Float32 normWidth, Float32 rippleDb );
	
	int        CountPoles        ( void );
	int        CountZeroes        ( void );
	Complex    GetPole            ( int i );
	Complex    GetZero            ( int i );
	
protected:
	void    BrentHint        ( Float32 *w0, Float32 *w1 );
	//CalcT    PassbandHint    ( void );
	
	UInt32 NPairs;
};


#endif
