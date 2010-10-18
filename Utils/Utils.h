/************************************************************************
 
 Product: Portable Audio Dsp Library 
 Version: V0.0.1
 File: Utils.h
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


#ifndef UTILS_H
#define UTILS_H	   



typedef float Float32;
typedef unsigned int UInt32;

#ifndef M_LN2
#define M_LN2	   0.69314718055994530942
#endif

#ifndef M_PI
#define M_PI		3.14159265358979323846
#endif

#ifndef M_PI_2
#define M_PI_2		1.57079632679489661923
#endif

const Float32 kLn2    =0.693147180559945309417;
const Float32 kLn10    =2.30258509299404568402;


#include  <math.h>




Float32  fastacosh( Float32 val );

// Three approximations for both sine and cosine at a given angle.
// The faster the routine, the larger the error.

// Tuned for maximum pole stability. r must be in the range 0..pi
// This one breaks down considerably at the higher angles. It is
// included only for educational purposes.

void fastestsincos( Float32 r, Float32 *sn, Float32 *cs );


//Low precision sine/cosine (~14x faster)
// Lower precision than ::fastsincos() but still decent
void fastersincos( Float32 x,Float32 *sn, Float32 *cs );


// Slower than ::fastersincos() but still faster than
// sin(), and with the best accuracy of these routines.

//High precision sine/cosine (~8x faster)
void fastsincos( Float32 x,Float32 *sn, Float32 *cs );



//fastsqrt1     : 1/5
//fastsqrt2   : 1/2
//fastsqrt3 : 2/3

// Faster approximations to sqrt()
//    From http://ilab.usc.edu/wiki/index.php/Fast_Square_Root
//    The faster the routine, the more error in the approximation.

// Log Base 2 Approximation
// 5 times faster than sqrt(

Float32 fastsqrt1(Float32 x );


// Log Base 2 Approximation with one extra Babylonian Step
// 2 times faster than sqrt()

Float32 fastsqrt2(Float32 x );

// Log Base 2 Approximation with two extra Babylonian Steps
// 50% faster than sqrt()

Float32 fastsqrt3(Float32 x );



#ifdef BYTE_ORDER
// In gcc compiler detect the byte order automatically
#if BYTE_ORDER == BIG_ENDIAN
// big-endian platform.
#define _BIG_ENDIAN_
#endif
#endif

#ifdef _BIG_ENDIAN_
// big-endian CPU, swap bytes in 16 & 32 bit words

// helper-function to swap byte-order of 32bit integer
static inline void _swap32(unsigned int &dwData)
{
	dwData = ((dwData >> 24) & 0x000000FF) | 
	((dwData >> 8)  & 0x0000FF00) | 
	((dwData << 8)  & 0x00FF0000) | 
	((dwData << 24) & 0xFF000000);
}   

// helper-function to swap byte-order of 16bit integer
static inline void _swap16(unsigned short &wData)
{
	wData = ((wData >> 8) & 0x00FF) | 
	((wData << 8) & 0xFF00);
}

// helper-function to swap byte-order of buffer of 16bit integers
static inline void _swap16Buffer(unsigned short *pData, unsigned int dwNumWords)
{
	unsigned long i;
	
	for (i = 0; i < dwNumWords; i ++)
	{
		_swap16(pData[i]);
	}
}

#else   // BIG_ENDIAN
// little-endian CPU, WAV file is ok as such

// dummy helper-function
static inline void _swap32(unsigned int &dwData)
{
	// do nothing
}   

// dummy helper-function
static inline void _swap16(unsigned short &wData)
{
	// do nothing
}

// dummy helper-function
static inline void _swap16Buffer(unsigned short *pData, unsigned int dwNumBytes)
{
	// do nothing
}

#endif  // BIG_ENDIAN



#endif

