/*
 *  Chebyshev1HighPass.cpp
 *  PU_Library
 *
 *  Created by Helder Vasconcelos on 10/10/17.
 *  Copyright 2010 AuGear. All rights reserved.
 *
 */

#include "Chebyshev1HighPass.h"



void ChebyShev1HighPass::Setup( Float32 cutoffFreq, Float32 rippleDb )
{
	Chebyshev1Filter::Setup( cutoffFreq, rippleDb );
	// move peak of ripple down to 0dB
	if( !(NPoles&1) )
		CascadeStages::Normalize( pow( 10, -rippleDb/20.0 ) );
}


Float32 ChebyShev1HighPass::PassbandHint( void )
{
	return M_PI;
}