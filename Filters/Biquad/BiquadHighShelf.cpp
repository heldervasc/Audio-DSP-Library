/************************************************************************
 
 Product: Portable Audio Dsp Library 
 Version: V0.0.1
 File: HanningWindow.cpp
 Creation date: 2010/08/10
 Author: Hélder Vasconcelos helder.vasc@e-2points.com 
 Description: Class Tester
 
 
 Copyright (c) 2010 Hélder Vasconcelos
 
 This library is free software; you can redistribute it and/or modify 
 it under the terms of the GNU Lesser General Public License as published by 
 the Free Software Foundation; either version 2.1 of the License, or 
 (at your option) any later version.
 
 This library is distributed in the hope that it will be useful, 
 but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
 or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License 
 for more details.
 
 You should have received a copy of the GNU Lesser General Public License 
 along with this library; if not, write to the Free Software Foundation, Inc., 
 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA 
 
 ****************************************************************************/

#include "BiquadHighShelf.h"

/*
 
 A  = sqrt( 10^(dBgain/20) )
 =       10^(dBgain/40)  
 
 w0 = 2*pi*f0/Fs
 
 alpha = sin(w0)/(2*Q)    
 
 highShelf: H(s) = A * (A*s^2 + (sqrt(A)/Q)*s + 1)/(s^2 + (sqrt(A)/Q)*s + A)
 
 b0 =    A*( (A+1) + (A-1)*cos(w0) + 2*sqrt(A)*alpha )
 b1 = -2*A*( (A-1) + (A+1)*cos(w0)                   )
 b2 =    A*( (A+1) + (A-1)*cos(w0) - 2*sqrt(A)*alpha )
 a0 =        (A+1) - (A-1)*cos(w0) + 2*sqrt(A)*alpha
 a1 =    2*( (A-1) - (A+1)*cos(w0)                   )
 a2 =        (A+1) - (A-1)*cos(w0) - 2*sqrt(A)*alpha
 
 
 *in + s->b[1]*h->v[0] + s->b[2]*h->v[1] + s->a[1]*h->v[2] + s->a[2]*h->v[3];
 
 void SetStage    ( CalcT a1, CalcT a2, CalcT b0, CalcT b1, CalcT b2 );
 
 */




void BiquadHighShelf::Setup            ( Float32 normFreq, Float32 dB, Float32 shelfSlope){

	Float32 A  = pow( 10, dB/40 );
	Float32 w0 = 2 * M_PI * normFreq;
	Float32 cs = cos(w0);
	Float32 sn = sin(w0);
	
	Float32 alph = sn / 2 * ::sqrt( (A + 1/A) * (1/shelfSlope - 1) + 2 );
	Float32 sa   =      2 * ::sqrt( A ) * alph;
	SetupCommon( cs, A, sa );

}


void BiquadHighShelf::SetupFast        ( Float32 normFreq, Float32 dB, Float32 shelfSlope ){


	Float32 A  = pow( 10, dB/40 );
	Float32 w0 = 2 * M_PI * normFreq;
	Float32 sn, cs;
	fastsincos( w0, &sn, &cs );
	
	Float32 alph = sn / 2 * fastsqrt1( (A + 1/A) * (1/shelfSlope - 1) + 2 );
	Float32 sa   =      2 * fastsqrt1( A ) * alph;
	SetupCommon( cs, A, sa );
	
	
}


void BiquadHighShelf::SetupCommon    ( Float32 cs, Float32 A, Float32 sa ){

	Float32 An    = A-1;
	Float32 Ap    = A+1;
	Float32 Ancs    = An*cs;
	Float32 Apcs    = Ap*cs;
	Float32 b0 =        A * (Ap + Ancs + sa );
	Float32 b1 = -2 * A * (An + Apcs);
	Float32 b2 =        A * (Ap + Ancs - sa );
	Float32 a0 =            (Ap - Ancs + sa );
	Float32 a2 =             Ancs + sa - Ap;
	Float32 a1 = -2    *    (An - Apcs);
	this->SetStage( a1/a0, a2/a0, b0/a0, b1/a0, b2/a0 );

}

