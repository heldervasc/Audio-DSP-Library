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

#ifndef BIQUADFILTER_H
#define BIQUADFILTER_H

#include "CascadeFilter.h"
#include "Utils.h"

/****************************************************************************

    Biquad Second Order IIR Filters
   
	y[n] = (b0/a0)*x[n] + (b1/a0)*x[n-1] + (b2/a0)*x[n-2] - (a1/a0)*y[n-1] - (a2/a0)*y[n-2] 
	
 
	H(z) = (b0/a0) * 1 + (b1/b0)*z^-1 + (b2/b0)*z^-2 /   1 + (a1/a0)*z^-1 + (a2/a0)*z^-2
 
 
	Fs (the sampling frequency)
 
	f0 ("wherever it's happenin', man."  Center Frequency or
	Corner Frequency, or shelf midpoint frequency, depending
	on which filter type.  The "significant frequency".)
 
	dBgain (used only for peaking and shelving filters)
 
	Q (the EE kind of definition, except for peakingEQ in which A*Q is
	the classic EE Q.  That adjustment in definition was made so that
	a boost of N dB followed by a cut of N dB for identical Q and
	f0/Fs results in a precisely flat unity gain filter or "wire".)
 
	_or_ BW, the bandwidth in octaves (between -3 dB frequencies for BPF
	and notch or between midpoint (dBgain/2) gain frequencies for
	peaking EQ)
 
	_or_ S, a "shelf slope" parameter (for shelving EQ only).  When S = 1,
	the shelf slope is as steep as it can be and remain monotonically
	increasing or decreasing gain with frequency.  The shelf slope, in
	dB/octave, remains proportional to S for all other values for a
	fixed f0/Fs and dBgain.
 
	A  = sqrt( 10^(dBgain/20) )
	   =       10^(dBgain/40)  
 
	w0 = 2*pi*f0/Fs
 
	alpha = sin(w0)/(2*Q)                                       (case: Q)
	
	= sin(w0)*sinh( ln(2)/2 * BW * w0/sin(w0) )           (case: BW)
	
	= sin(w0)/2 * sqrt( (A + 1/A)*(1/S - 1) + 2 )         (case: S)
 
	
	FYI: The relationship between bandwidth and Q is
	1/Q = 2*sinh(ln(2)/2*BW*w0/sin(w0))     (digital filter w BLT)
	or   1/Q = 2*sinh(ln(2)/2*BW)             (analog filter prototype)
 
	The relationship between shelf slope and Q is
	1/Q = sqrt((A + 1/A)*(1/S - 1) + 2)
 
	2*sqrt(A)*alpha  =  sin(w0) * sqrt( (A^2 + 1)*(1/S - 1) + 2*A )
	is a handy intermediate variable for shelving EQ filters.
 
	Source:
	http://www.musicdsp.org/files/Audio-EQ-Cookbook.txt
	

****************************************************************************/




class BiquadFilter : public CascadeFilter
{
	
	
public:
 	
	BiquadFilter(UInt32 Nchan):CascadeFilter(1,Nchan){}
	BiquadFilter():CascadeFilter(1,2){}


	
protected:
	//void Setup( const Float32 a[3], const Float32 b[3] );
};




#endif
