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


void Chebyshev1Filter::Design(){



	//int n=spec.;
	
	//SetPoles( n );
	//SetZeros( n );
	
	
	Float32 eps=sqrt( 1/exp( -this->passRippleDb*0.1*kLn10 )-1 );
	Float32 v0=asinh(1/eps)/this->NOrder;
	
	for( int i=0;i<this->NOrder;i++ )
	{
		int k=2*i+1-this->NOrder;
		Float32 a=-sinh(v0)*cos(k*M_PI/(2*this->NOrder));
		Float32 b= cosh(v0)*sin(k*M_PI/(2*this->NOrder));
		PolesPtr[i]=Complex( a, b );
		ZerosPtr[i]=infinity;
	}
	
	w=0;
	gain=(this->NOrder&1)?1:pow( 10, -this->passRippleDb/20.0 );
	
	
	
	
	
}
