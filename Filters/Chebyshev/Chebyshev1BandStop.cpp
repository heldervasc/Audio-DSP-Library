/*
 *  Chebyshev1BandStop.cpp
 *  PU_Library
 *
 *  Created by Helder Vasconcelos on 10/10/17.
 *  Copyright 2010 AuGear. All rights reserved.
 *
 */

#include "Chebyshev1BandStop.h"



void Chebyshev1BandStop::Setup( Float32 centerFreq, Float32 normWidth, Float32 rippleDb ){


}

int Chebyshev1BandStop::CountPoles( void ){

		return NPairs*2;

}
int Chebyshev1BandStop::CountZeroes( void ){

		return NPairs*2;

}

Complex Chebyshev1BandStop::GetPole( int i ){



}

Complex  Chebyshev1BandStop::GetZero( int i ){



}


void Chebyshev1BandStop::BrentHint( Float32 *w0, Float32 *w1 ){




}