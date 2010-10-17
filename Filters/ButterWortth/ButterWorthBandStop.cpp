/*
 *  ButterWorthBandStop.cpp
 *  PU_Library
 *
 *  Created by Helder Vasconcelos on 10/10/16.
 *  Copyright 2010 AuGear. All rights reserved.
 *
 */

#include "ButterWorthBandStop.h"


void ButterBandStop::Setup( Float32 centerFreq, Float32 normWidth )
{
	m_n=NPairs;
	Float32 angularWidth=2*M_PI*normWidth;
	m_wc2=2*M_PI*centerFreq-(angularWidth/2);
	m_wc =m_wc2+angularWidth;
	Prepare();
}


int ButterBandStop::CountPoles( void )
{
	return NPairs*2;
}


int ButterBandStop::CountZeroes( void )
{
	return NPairs*2;
}


Complex ButterBandStop::GetPole( int i )
{
	return GetBandStopPole( i );
}


Complex ButterBandStop::GetZero( int i )
{
	return GetBandStopZero( i );
}


Float32 ButterBandStop::PassbandHint( void )
{
	if( (m_wc+m_wc2)/2<M_PI_2 )
		return M_PI;
	else
		return 0;
}

