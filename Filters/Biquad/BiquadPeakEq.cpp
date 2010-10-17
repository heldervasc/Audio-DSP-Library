/*
 *  BiquadPeakEq.cpp
 *  Library
 *
 *  Created by Helder Vasconcelos on 10/10/11.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "BiquadPeakEq.h"

/*
 
 A  = sqrt( 10^(dBgain/20) )
 =       10^(dBgain/40)  
 
 w0 = 2*pi*f0/Fs
 
 alpha = sin(w0)/(2*Q)    
 
 peakingEQ:  H(s) = (s^2 + s*(A/Q) + 1) / (s^2 + s/(A*Q) + 1)
 
 b0 =   1 + alpha*A
 b1 =  -2*cos(w0)
 b2 =   1 - alpha*A
 a0 =   1 + alpha/A
 a1 =  -2*cos(w0)
 a2 =   1 - alpha/A
 
 
 
 
 
 *in + s->b[1]*h->v[0] + s->b[2]*h->v[1] + s->a[1]*h->v[2] + s->a[2]*h->v[3];
 
 void SetStage    ( CalcT a1, CalcT a2, CalcT b0, CalcT b1, CalcT b2 );
 
 */


void BiquadPeakEq::Setup            ( Float32 normFreq, Float32 dB, Float32 bandWidth){

	Float32 A  = pow( 10, dB/40 );
	Float32 w0 = 2 * M_PI * normFreq;
	Float32 cs = cos(w0);
	Float32 sn = sin(w0);
	Float32 alph = sn * sinh( kLn2/2 * bandWidth * w0/sn );
	SetupCommon( sn, cs, alph, A );

}

void BiquadPeakEq::SetupFast        ( Float32 normFreq, Float32 dB, Float32 bandWidth){

	Float32 A  = pow( 10, dB/40 );
	Float32 w0 = 2 * M_PI * normFreq;
	Float32 sn, cs;
	fastsincos( w0, &sn, &cs );
	Float32 alph = sn * sinh( kLn2/2 * bandWidth * w0/sn );
	SetupCommon( sn, cs, alph, A );

}


void BiquadPeakEq::SetupCommon    ( Float32 sn, Float32 cs, Float32 alph, Float32 A ){

	Float32 t=alph*A;
	Float32 b0 =  1 - t;
	Float32 b2 =  1 + t;
	t=alph/A;
	Float32 a0 =  1 / ( 1 + t );
	Float32 a2 =  t - 1;
	Float32 b1 = a0 * ( -2 * cs );
	Float32 a1 = -b1;
	
	this->SetStage( a1, a2*a0, b0*a0, b1, b2*a0 );


}


