/*
 *  Chebyshev1HighPass.h
 *  PU_Library
 *
 *  Created by Helder Vasconcelos on 10/10/17.
 *  Copyright 2010 AuGear. All rights reserved.
 *
 */

#ifndef CHEBYSHEVHIGHPASS_H
#define CHEBYSHEVHIGHPASS_H

// High Pass Chebyshev Type I filter

#include "Chebyshev1Filter.h"

class ChebyShev1HighPass : public Chebyshev1Filter
{
public:
	ChebyShev1HighPass(UInt32 NPoles,UInt32 NChannels):Chebyshev1Filter(NPoles,NChannels){
		
		m_sgn=-1;
        m_hint=hintPassband;
		this->NPoles=NPoles;
		
	}
	ChebyShev1HighPass():Chebyshev1Filter(4,2){
		
		m_sgn=-1;
		m_hint=hintPassband;
		this->NPoles=4;
		
	}
	
	void    Setup            ( Float32 cutoffFreq, Float32 rippleDb );
	
protected:
	Float32    PassbandHint    ( void );
	UInt32 NPoles;
};


#endif




