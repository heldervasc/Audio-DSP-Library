/************************************************************************
 
 Product: Portable Audio Dsp Library 
 Version: V0.0.1
 File: Brent.h
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

//--------------------------------------------------------------------------
//
//    Numerical Analysis
//
//--------------------------------------------------------------------------

// Implementation of Brent's Method provided by
// John D. Cook (http://www.johndcook.com/)

// The return value of Minimize is the minimum of the function f.
// The location where f takes its minimum is returned in the variable minLoc.
// Notation and implementation based on Chapter 5 of Richard Brent's book
// "Algorithms for Minimization Without Derivatives".


#ifndef BRENTMINIMIZE_H
#define BRENTMINIMIZE_H	 
#include "Utils.h"
#include <float.h>

/*template<class TFunction>
class BrentMinimize{
	
	public :
	static Float32 BrentMinimizeCalc(
						  TFunction& f,    // [in] objective function to minimize
						  Float32 leftEnd,    // [in] smaller value of bracketing interval
						  Float32 rightEnd,    // [in] larger value of bracketing interval
						  Float32 epsilon,    // [in] stopping tolerance
						  Float32& minLoc    // [out] location of minimum
						  );
	
	
};*/


#endif
