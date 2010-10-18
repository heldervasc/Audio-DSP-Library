/************************************************************************
 
 Product: Portable Audio Dsp Library 
 Version: V0.0.1
 File: Chebyshev1LowPass.cpp
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

#ifndef CHEBYSHEVLOWPASS_H
#define CHEBYSHEVLOWPASS_H

#include "Chebyshev1Filter.h"

// Low Pass Chebyshev Type I filter

class ChebyShev1LowPass : public Chebyshev1Filter
{
public:
	ChebyShev1LowPass(UInt32 NPoles,UInt32 NChannels):Chebyshev1Filter(NPoles,NChannels){
		
		m_sgn=1;
        m_hint=hintPassband;
		this->NPoles=NPoles;
		
	}
	ChebyShev1LowPass():Chebyshev1Filter(4,2){

		m_sgn=1;
		m_hint=hintPassband;
		this->NPoles=4;
		
	}
	
	void    Setup            ( Float32 cutoffFreq, Float32 rippleDb );
	
protected:
	Float32    PassbandHint    ( void );
	UInt32 NPoles;
};


#endif



