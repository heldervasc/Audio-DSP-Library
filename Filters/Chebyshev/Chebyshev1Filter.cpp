/*
 *  Chebyshev1.cpp
 *  PU_Library
 *
 *  Created by Helder Vasconcelos on 10/10/16.
 *  Copyright 2010 AuGear. All rights reserved.
 *
 */

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
