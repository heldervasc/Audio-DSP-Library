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

