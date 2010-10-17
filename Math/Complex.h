/*
 *  Complex.h
 *  Equalizer
 *
 *  Created by Helder Vasconcelos on 10/10/01.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */
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

