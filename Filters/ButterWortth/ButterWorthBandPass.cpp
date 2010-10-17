/*
 *  ButterWorthBandPass.cpp
 *  PU_Library
 *
 *  Created by Helder Vasconcelos on 10/10/16.
 *  Copyright 2010 AuGear. All rights reserved.
 *
 */

#include "ButterWorthBandPass.h"


void ButterBandPass::Setup( Float32 centerFreq, Float32 normWidth )
{
	m_n=NPairs;
	Float32 angularWidth=2*M_PI*normWidth;
	m_wc2=2*M_PI*centerFreq-(angularWidth/2);
	m_wc =m_wc2+angularWidth;
	Prepare();
}


int ButterBandPass::CountPoles( void )
{
	return NPairs*2;
}


int ButterBandPass::CountZeroes( void )
{
	return NPairs*2;
}


Complex ButterBandPass::GetPole( int i )
{
	return GetBandPassPole( i );
}


Complex ButterBandPass::GetZero( int i )
{
	return GetBandPassZero( i );
}


Float32 ButterBandPass::PassbandHint( void )
{
	return (m_wc+m_wc2)/2;
}


