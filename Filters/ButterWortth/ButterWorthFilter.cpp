/*
 *  ButterWorth.cpp
 *  PU_Library
 *
 *  Created by Helder Vasconcelos on 10/10/16.
 *  Copyright 2010 AuGear. All rights reserved.
 *
 */

#include "ButterWorthFilter.h"


#include <complex>
using namespace std;

void ButterWorthFilter::Setup( Float32 cutoffFreq )
{
	m_n=this->nPoles;
	m_wc=2*M_PI*cutoffFreq;
	Prepare();
}


int ButterWorthFilter::CountPoles( void )
{
	return nPoles;
}


int ButterWorthFilter::CountZeroes( void )
{
	return nPoles;
}


Complex ButterWorthFilter::GetPole( int i )
{
	return BilinearTransform( GetSPole( i, m_wc ) );
}


Complex ButterWorthFilter::GetSPole( int i, Float32 wc )
{
	
//	Complex temp(,);
	Complex c(0);
	c.SetValueFromPolar(tan(wc*0.5),M_PI_2+(2*i+1)*M_PI/(2*m_n));
	return c;
}
