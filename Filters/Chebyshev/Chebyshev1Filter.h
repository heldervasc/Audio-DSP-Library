/************************************************************************
 
 Product: Portable Audio Dsp Library 
 Version: V0.0.1
 File: Chebyshev1Filter.h
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

#ifndef CHEBYSHEVFILTER_H
#define CHEBYSHEVFILTER_H

#include "PoleFilter.h"

class Chebyshev1Filter : public PoleFilter
{
public:
	
	Chebyshev1Filter(UInt32 NPoles,UInt32 NChannels):PoleFilter(int (NPoles+1/2),NChannels){
		
		nPoles=UInt32 (NPoles+1/2);
		m_hint=hintBrent;
		
	}
	Chebyshev1Filter():PoleFilter(int (4+1/2),2){
		
		m_hint=hintBrent;
		nPoles=UInt32(4+1/2);
		
	}
	
	// cutoffFreq = freq / sampleRate
	
	virtual    void    Setup            ( Float32 cutoffFreq, Float32 rippleDb );
	
	virtual int        CountPoles        ( void );
	virtual int        CountZeroes        ( void );
	virtual Complex    GetPole            ( int i );
	virtual Complex    GetZero            ( int i );
	
protected:
	void            SetupCommon        ( Float32 rippleDb );
	virtual    Complex GetSPole        ( int i, Float32 wc );
	
protected:
	Float32    m_sgn;
	Float32    m_eps;
	UInt32 nPoles;
};


#endif

