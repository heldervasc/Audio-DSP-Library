/************************************************************************
 
 Product: Portable Audio Dsp Library 
 Version: V0.0.1
 File: Complex.h
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

#ifndef COMPLEX_H
#define COMPLEX_H	 

#include <math.h>

typedef float Float32;


class Complex {


private:

	
	
	
	
public :

	Float32 re;
	Float32 img;
	
	
	Complex();
	Complex( Float32 re,Float32 img=0);
	~Complex();
	
	
	Float32 GetPolarMagnitude();
	Float32 GetPolarAngle();

	void SetValueFromPolar(Float32 mag,Float32 ang);
	void SetValueFromCart(Float32 re,Float32 img);
	
	//abs(x)
	Float32			Norm();
	
	//|x|
	Complex		Conjugate();
	
	Complex      operator-	 (void);
	Complex		operator+    ( Complex v );
	Complex		operator-    ( Complex v );
	Complex		operator*    ( Complex v );
	Complex		operator/    ( Complex v );
	
	Complex &    operator+=    ( Complex v );
	Complex &    operator-=    ( Complex v );
	Complex &    operator*=    ( Complex v );
	Complex &    operator/=    ( Complex v );
	
	Complex &    operator+=    ( Float32 v );
	Complex &    operator-=    ( Float32 v );
	Complex &    operator*=    ( Float32 v );
	Complex &    operator/=    ( Float32 v );
	
	Complex operator+(Float32 rhs);
	Complex operator-(Float32 rhs);
	Complex operator*(Float32 rhs);
	Complex operator/(Float32 rhs);

	
	Complex Sqrt( Complex &c );
	Complex Polar(Float32 &m,Float32 &a );

	bool			operator== (Complex v );
	

};

#endif 

