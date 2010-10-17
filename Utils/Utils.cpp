/*
 *  Utils.cpp
 *  Equalizer
 *
 *  Created by Helder Vasconcelos on 10/09/29.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */




#include "Utils.h"


Float32  fastacosh( Float32 val ){


return log( val+sqrt(val*val-1) );

}




void fastestsincos( Float32 r, Float32 *sn, Float32 *cs ){

	const Float32 c=0.70710678118654752440; // sqrt(2)/2
	
	Float32 v=(2-4*c)*r*r+c;
	if(r<M_PI_2)
	{
		*sn=v+r; 
		*cs=v-r;
	}
	else
	{
		*sn=r+v; 
		*cs=r-v;
	}



}

//Low precision sine/cosine (~14x faster)
void fastersincos( Float32 x,Float32 *sn, Float32 *cs ){

	//always wrap input angle to -PI..PI
	if        (x < -M_PI) x += 2*M_PI;
	else if (x >  M_PI) x -= 2*M_PI;
	//compute sine
	if (x < 0)    *sn = 1.27323954 * x + 0.405284735 * x * x;
	else        *sn = 1.27323954 * x - 0.405284735 * x * x;
	//compute cosine: sin(x + PI/2) = cos(x)
	x += M_PI_2;
	if (x > M_PI ) x -= 2*M_PI;
	if (x < 0)    *cs = 1.27323954 * x + 0.405284735 * x * x;
	else        *cs = 1.27323954 * x - 0.405284735 * x * x;



}

//High precision sine/cosine (~8x faster)
void fastsincos( Float32 x,Float32 *sn, Float32 *cs ){


	Float32 s, c;
	//always wrap input angle to -PI..PI
	if (x < -M_PI) x += 2*M_PI;
	else if (x >  M_PI) x -= 2*M_PI;
	//compute sine
	if (x < 0)
	{
		s = 1.27323954 * x + .405284735 * x * x;
		if (s < 0)    s = .225 * (s * -s - s) + s;
		else        s = .225 * (s *  s - s) + s;
	}
	else
	{
		s = 1.27323954 * x - 0.405284735 * x * x;
		if (s < 0)    s = .225 * (s * -s - s) + s;
		else        s = .225 * (s *  s - s) + s;
	}
	*sn=s;
	//compute cosine: sin(x + PI/2) = cos(x)
	x += M_PI_2;
	if (x > M_PI ) x -= 2*M_PI;
	if (x < 0)
	{
		c = 1.27323954 * x + 0.405284735 * x * x;
		if (c < 0)    c = .225 * (c * -c - c) + c;
		else        c = .225 * (c *  c - c) + c;
	}
	else
	{
		c = 1.27323954 * x - 0.405284735 * x * x;
		if (c < 0)    c = .225 * (c * -c - c) + c;
		else        c = .225 * (c *  c - c) + c;
	}
	*cs=c;

}




Float32 fastsqrt1(Float32 x ){
	
	
	union
	{
		int i;
		Float32 x;
	} u;
	u.x = x;
	u.i = (1<<29) + (u.i >> 1) - (1<<22); 
	
	// One Babylonian Step
	u.x = 0.5f * (u.x + x/u.x);
	
	return u.x;


}


Float32 fastsqrt2(Float32 x ){

	Float32 v=fastsqrt1( x );
	v = 0.5f * (v + x/v); // One Babylonian step
	return v;


}


Float32 fastsqrt3(Float32 x ){

	Float32 v=fastsqrt1( x );
	v =           v + x/v;
	v = 0.25f* v + x/v; // Two Babylonian steps
	return v;



}

