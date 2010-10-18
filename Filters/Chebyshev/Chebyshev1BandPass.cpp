/************************************************************************
 
 Product: Portable Audio Dsp Library 
 Version: V0.0.1
 File: Chebyshev1BandPass.cpp
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