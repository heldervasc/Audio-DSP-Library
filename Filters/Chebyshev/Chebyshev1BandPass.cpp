/*
 *  Chebyshev1BandPass.cpp
 *  PU_Library
 *
 *  Created by Helder Vasconcelos on 10/10/17.
 *  Copyright 2010 AuGear. All rights reserved.
 *
 */

#include "Chebyshev1BandPass.h"


void Chebyshev1BandPass::Setup( Float32 centerFreq, Float32 normWidth, Float32 rippleDb )
{
	m_n=NPairs;
	Float32 angularWidth=2*M_PI*normWidth;
	m_wc2=2*M_PI*centerFreq-(angularWidth/2);
	m_wc =m_wc2+angularWidth;
	SetupCommon( rippleDb );
}


int Chebyshev1BandPass::CountPoles( void )
{
	return NPairs*2;
}


int Chebyshev1BandPass::CountZeroes( void )
{
	return NPairs*2;
}


Complex    Chebyshev1BandPass::GetPole( int i )
{
	return GetBandPassPole( i );
}


Complex    Chebyshev1BandPass::GetZero( int i )
{
	return GetBandPassZero( i );
}


void Chebyshev1BandPass::BrentHint( Float32 *w0, Float32 *w1 )
{
	Float32 d=1e-4*(m_wc-m_wc2)/2;
	*w0=m_wc2+d;
	*w1=m_wc-d;
}

/*
 // Unfortunately, this doesn't work at the frequency extremes
 // Maybe we can inverse pre-warp the center point to make sure
 // it stays put after bilinear and bandpass transformation.
 template<int poles, int channels>
 CalcT Cheby1BandPass<poles, channels>::PassbandHint( void )
 {
 return (m_wc+m_wc2)/2;
 }
 */