/************************************************************************
 
 Product: Portable Audio Dsp Library 
 Version: V0.0.1
 File: Chebyshev1Filter.cpp
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

#include "Chebyshev1Filter.h"



void Chebyshev1Filter::Setup( Float32 cutoffFreq, Float32 rippleDb )
{
	m_n=nPoles;
	m_wc=2*M_PI*cutoffFreq;
	SetupCommon( rippleDb );
}


void Chebyshev1Filter::SetupCommon( Float32 rippleDb )
{
	m_eps=::sqrt( 1/::exp( -rippleDb*0.1*kLn10 )-1 );
	Prepare();
	// This moves the bottom of the ripples to 0dB gain
	//CascadeStages::Normalize( pow( 10, rippleDb/20.0 ) );
}


int    Chebyshev1Filter::CountPoles( void )
{
	return nPoles;
}


int Chebyshev1Filter::CountZeroes( void )
{
	return nPoles;
}


Complex Chebyshev1Filter::GetPole( int i )
{
	return BilinearTransform( GetSPole( i, m_wc ) )*m_sgn;
}


Complex Chebyshev1Filter::GetZero( int i )
{
	return Complex( -m_sgn );
}


Complex Chebyshev1Filter::GetSPole( int i, Float32 wc )
{
	int n        = m_n;
	Float32 ni    = 1.0/n;
	Float32 alpha    = 1/m_eps+::sqrt(1+1/(m_eps*m_eps));
	Float32 pn    = pow( alpha,  ni );
	Float32 nn    = pow( alpha, -ni );
	Float32 a        = 0.5*( pn - nn );
	Float32 b        = 0.5*( pn + nn );
	Float32 theta = M_PI_2 + (2*i+1) * M_PI/(2*n);
	
	Complex c(0);
	c.SetValueFromPolar(tan( 0.5*(m_sgn==-1?(M_PI-wc):wc) ), theta);
	return Complex( a*c.re, b*c.img );
}
