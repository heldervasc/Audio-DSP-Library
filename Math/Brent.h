/*
 *  Brent.h
 *  PU_Library
 *
 *  Created by Helder Vasconcelos on 10/10/16.
 *  Copyright 2010 AuGear. All rights reserved.
 *
 */

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
