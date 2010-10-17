/*
 *  Chebyshev1LowPass.cpp
 *  PU_Library
 *
 *  Created by Helder Vasconcelos on 10/10/17.
 *  Copyright 2010 AuGear. All rights reserved.
 *
 */

#include "Chebyshev1LowPass.h"



void ChebyShev1LowPass::Setup( Float32 cutoffFreq, Float32 rippleDb )
{
	Chebyshev1Filter::Setup( cutoffFreq, rippleDb );
	// move peak of ripple down to 0dB
	if( !(NPoles&1) )
		CascadeStages::Normalize( pow( 10, -rippleDb/20.0 ) );
}


Float32 ChebyShev1LowPass::PassbandHint( void )
{
	return 0;
}