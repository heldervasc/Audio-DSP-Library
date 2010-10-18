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

#ifndef POLEFILTER_H
#define POLEFILTER_H

#include "CascadeFilter.h"

#include <float.h>


class PoleFilter : public CascadeFilter
{

public:
	
	
	PoleFilter(UInt32 Order,UInt32 Nchan);
		
	
	// Return the number of available poles.
	int        CountPoles            ( void );
	
	// Return the number of available zeros.
	int        CountZeros            ( void );	
	
	// Set the number of available poles up to max.
	void SetPoles( int n );
	
	// Set the number of available zeros up to max.
	void SetZeros( int n );
	
	// Retrieve the zero-based i-th pole.
	Complex    GetPole                ( int i );
	
	//tes

	// Retrieve the zero-based i-th zero.
	Complex    GetZero                ( int i );
		
	// Direct access to the set of all poles.
	 void GetPoles(Complex **poles );
	
	// Direct access to the set of all Zeros.
	void GetZeros(Complex **zeros );
	
	void Realize( CascadeFilter *cascade );
	
	void GetNormalization(Float32 &w,Float32 &gain);
	

	//	Filter Transformations 
	
	void LowPassTransf(void);
	
	void HighPassTransf(void);
	
	void BandPassTransf(void);
	
	Complex BandPassTransformPoles(int i,Complex);
	
	void BandStopTransf(void);
	
	Complex BandStopTransformPoles(int i,Complex);
	
	virtual void Design()=0;
	
	
	
protected:
	
	// Helpers for Realize().
	
	void BuildA( CascadeFilter *cascade, Float32 x1, Float32 x2, int *na );
	
	void BuildB( CascadeFilter *cascade, Float32 x0, Float32 x1, Float32 x2, int *nb );
	
	
	//Normalization Parameters
	Float32 w;		// angular frequency
	Float32 gain;		// target gain
	

	UInt32 NPoles;
	UInt32 Nzeros;
	UInt32 NChannels;
	UInt32 NOrder;
	
	Complex * PolesPtr;
	Complex * ZerosPtr;
	
	Float32    m_wc;
	Float32    m_wc2;
	
	
	Hist *m_hist;
	
	
	
	
	/**********************
	 
			Filter Parameters
	 */
	
	 Float32 cutoffFreq;		// Normalized Cutoff Frequency 
	 Float32 passRippleDb;		// Passband ripple in Db
	 Float32 stopBandDb;		// Minimum stopband attenuation in Db

	 Float32 centerFreq;		//Normalized CenterFreq Cutoff
	 Float32 normWidth;			// Normalized With 
	 Float32 gainDb;			// gain or cut in Db
	 Float32 rollOff;			// for elliptics
	 
	 
	
	
	
	
};


#endif

