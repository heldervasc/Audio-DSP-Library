/*
 *  Chebyshev1LowPass.h
 *  PU_Library
 *
 *  Created by Helder Vasconcelos on 10/10/17.
 *  Copyright 2010 AuGear. All rights reserved.
 *
 */

#ifndef CHEBYSHEVLOWPASS_H
#define CHEBYSHEVLOWPASS_H

#include "Chebyshev1Filter.h"

// Low Pass Chebyshev Type I filter

class ChebyShev1LowPass : public Chebyshev1Filter
{
public:
	ChebyShev1LowPass(UInt32 NPoles,UInt32 NChannels):Chebyshev1Filter(NPoles,NChannels){
		
		m_sgn=1;
        m_hint=hintPassband;
		this->NPoles=NPoles;
		
	}
	ChebyShev1LowPass():Chebyshev1Filter(4,2){

		m_sgn=1;
		m_hint=hintPassband;
		this->NPoles=4;
		
	}
	
	void    Setup            ( Float32 cutoffFreq, Float32 rippleDb );
	
protected:
	Float32    PassbandHint    ( void );
	UInt32 NPoles;
};


#endif



