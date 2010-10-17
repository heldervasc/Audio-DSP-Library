/*
 *  PoleFilter.h
 *  Library
 *
 *  Created by Helder Vasconcelos on 10/10/13.
 *  Copyright 2010 Parallel Universe. All rights reserved.
 *
 */


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




template<class TFunction>
Float32 BrentMinimizeCalc(
						  TFunction& f,    // [in] objective function to minimize
						  Float32 leftEnd,    // [in] smaller value of bracketing interval
						  Float32 rightEnd,    // [in] larger value of bracketing interval
						  Float32 epsilon,    // [in] stopping tolerance
						  Float32& minLoc    // [out] location of minimum
						  )
{
	Float32 d, e, m, p, q, r, tol, t2, u, v, w, fu, fv, fw, fx;
	static const Float32 c = 0.5*(3.0 - ::sqrt(5.0));
	static const Float32 SQRT_DBL_EPSILON = ::sqrt(DBL_EPSILON);
	
	Float32& a = leftEnd; Float32& b = rightEnd; Float32& x = minLoc;
	
	v = w = x = a + c*(b - a); d = e = 0.0;
	fv = fw = fx = f(x);
	int counter = 0;
loop:
	counter++;
	m = 0.5*(a + b);
	tol = SQRT_DBL_EPSILON*::fabs(x) + epsilon; t2 = 2.0*tol;
	// Check stopping criteria
	if (::fabs(x - m) > t2 - 0.5*(b - a))
	{
		p = q = r = 0.0;
		if (::fabs(e) > tol)
		{
			// fit parabola
			r = (x - w)*(fx - fv);
			q = (x - v)*(fx - fw);
			p = (x - v)*q - (x - w)*r;
			q = 2.0*(q - r);
			(q > 0.0) ? p = -p : q = -q;
			r = e; e = d;
		}
		if (::fabs(p) < ::fabs(0.5*q*r) && p < q*(a - x) && p < q*(b - x))
		{
			// A parabolic interpolation step
			d = p/q;
			u = x + d;
			// f must not be evaluated too close to a or b
			if (u - a < t2 || b - u < t2)
				d = (x < m) ? tol : -tol;
		}
		else
		{
			// A golden section step
			e = (x < m) ? b : a;
			e -= x;
			d = c*e;
		}
		// f must not be evaluated too close to x
		if (::fabs(d) >= tol)
			u = x + d;
		else if (d > 0.0)
			u = x + tol;
		else
			u = x - tol;
		fu = f(u);
		// Update a, b, v, w, and x
		if (fu <= fx)
		{
			(u < x) ? b = x : a = x;
			v = w; fv = fw; 
			w = x; fw = fx; 
			x = u; fx = fu;
		}
		else
		{
			(u < x) ? a = u : b = u;
			if (fu <= fw || w == x)
			{
				v = w; fv = fw; 
				w = u; fw = fu;
			}
			else if (fu <= fv || v == x || v == w)
			{
				v = u; fv = fu;
			}
		}
		goto loop;  // Yes, the dreaded goto statement. But the code
		// here is faithful to Brent's orginal pseudocode.
	}
	return  fx;
}



#endif

