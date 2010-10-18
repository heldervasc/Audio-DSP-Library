/************************************************************************
 
 Product: Portable Audio Dsp Library 
 Version: V0.0.1
 File: HanningWindow.cpp
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

#include "PoleFilter.h"
#include "Complex.h"
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include <stdio.h>
#include <string.h>
#include "CascadeFilter.h"
#include <limits>


//const Complex Dsp::infinity(std::numeric_limits<CalcT>::infinity());

PoleFilter::PoleFilter(UInt32 Order,UInt32 Nchan):CascadeFilter(UInt32((Order+1)/2),Nchan){

	this->NOrder=Order;
	this->NChannels=Nchan;

	int len=(Nchan*((Order+1)/2));
	m_hist=malloc(len*sizeof(Complex));
	memset(m_hist,0,len);
}


// Return the number of available poles.
int  PoleFilter::CountPoles( void ){


	return this->NPoles;


}

// Return the number of available zeros.
int PoleFilter::CountZeros( void ){


	return this->Nzeros;

}

// Set the number of available poles up to max.
void PoleFilter::SetPoles( int n ){

	this->NPoles=n;


}

// Set the number of available zeros up to max.
void PoleFilter::SetZeros( int n ){


	this->Nzeros=n;

}

// Retrieve the zero-based i-th pole.
Complex PoleFilter::GetPole( int i ){

	Complex temp(PolesPtr[i].re,PolesPtr[i].img);
	return temp;

}

// Retrieve the zero-based i-th zero.
Complex PoleFilter::GetZero( int i ){

	Complex temp=(ZerosPtr[i].re,ZerosPtr[i].img);
	return temp;



}

// Direct access to the set of all poles.
void PoleFilter::GetPoles(Complex **poles ){


	*poles=PolesPtr;
}

// Direct access to the set of all Zeros.
void PoleFilter::GetZeros(Complex **zeros ){


	*zeros=ZerosPtr;

}

void PoleFilter::Realize( CascadeFilter *cascade ){

	// Calculate number of second order sections required.
	{
		int s1=(CountPoles()+1)/2;
		int s2=(CountZeros()+1)/2;
		assert( s1==s2 ); // I am not sure if it works otherwise
		cascade->SetStageCount( s1>s2?s1:s2 );
	}
	
	cascade->Reset();
	
	int n;
	
	// Poles
	
	n=0;
	for( int i=0;i<CountPoles();i++ )
	{
		Complex c=GetPole(i);
		if( abs(c.img)<1e-6 )
			c=Complex( c.re, 0 );
		if( c.img==0 )
			BuildA( cascade, c.re, 0, &n );
		else if( c.img>0 )
			BuildA( cascade, 2*c.re, -c.Norm(), &n );
	}
	
	// Zeros
	
	n=0;
	for( int i=0;i<CountZeros();i++ )
	{
		Complex c=GetZero(i);
		if( abs(c.img)<1e-6 )
			c=Complex( c.re, 0 );
		if( c.img==0 )
			BuildB( cascade, -c.re, 1, 0, &n );
		else if( c.img>0 )
			BuildB( cascade, c.Norm(), -2*c.re, 1, &n );
	}
	
	// Normalization
	Complex c2=cascade->Response( w );
	
	cascade->Scale( gain / c2.Norm() );
	
	
}

void PoleFilter::BuildA( CascadeFilter *cascade, Float32 x1, Float32 x2, int *na ){
	
	if( x2!=0 )
	{
		CascadeFilter::Stage *temp;
		GetStages(&temp);
		
		CascadeFilter::Stage *s=temp+cascade->GetStageCount()-1-*na;
		assert( s->a[1]==0 && s->a[2]==0 );
		s->a[1]=x1;
		s->a[2]=x2;
		(*na)++;
	}
	else
	{
		// combine
		CascadeFilter::Stage *temp;
		GetStages(&temp);
		
		CascadeFilter::Stage *s=temp;
		s->a[2]=-s->a[1]*x1;
		s->a[1]+=x1;
		if( s->a[2]!=0 )
		{
			int n=cascade->GetStageCount()-1-*na;
			if( n>0 )
			{
				CascadeFilter::Stage *f=temp+n;
				f->a[1]=s->a[1];
				f->a[2]=s->a[2];
				s->a[1]=0;
				s->a[2]=0;
				(*na)++;
			}
		}
	}
	
	
}

void PoleFilter::BuildB( CascadeFilter *cascade, Float32 x0, Float32 x1, Float32 x2, int *nb ){
	
	
	if( x2!=0 )
	{
		
		CascadeFilter::Stage *temp;
		GetStages(&temp);
		CascadeFilter::Stage *s=temp+cascade->GetStageCount()-1-*nb;
		s->b[0]=x0;
		s->b[1]=x1;
		s->b[2]=x2;
		(*nb)++;
	}
	else
	{
		// combine
		// (b0 + z b1)(x0 + z x1) = (b0 x0 + (b1 x0+b0 x1) z + b1 x1 z^2)
		
		CascadeFilter::Stage *temp;
		GetStages(&temp);
		CascadeFilter::Stage *s=temp;
		s->b[2]=s->b[1]*x1;
		s->b[1]=s->b[1]*x0+s->b[0]*x1;
		s->b[0]*=x0;
		if( s->b[2]!=0 )
		{
			int n=cascade->GetStageCount()-1-*nb;
			if( n>0 )
			{
				CascadeFilter::Stage *f=temp+n;
				f->b[0]=s->b[0];
				f->b[1]=s->b[1];
				f->b[2]=s->b[2];
				s->b[0]=1;
				s->b[1]=0;
				s->b[2]=0;
				(*nb)++;
			}
		}
	}
	
	
}



void PoleFilter::GetNormalization(Float32 &w,Float32 &gain){
	
	w=this->w;
	gain=this->gain;


}


/*Transformations */
const Complex infinity(std::numeric_limits<Float32>::infinity());

void PoleFilter::LowPassTransf(void){

	
	Float32 w=2*M_PI*cutoffFreq;
	// prewarp
	
	Float32 k=tan(w*0.5); 
	
	//Poles Processing
	
	for( int i=0;i<NPoles;i++ )
	{
		Complex r=GetPole(i);
		Complex c(0);
		
		if( r==infinity )
		{
			c=Complex( -1, 0 );
		}
		else
		{
			// frequency transform
			c=r*k;
			// bilinear low-pass xform
			c=(c+1)/(-c+1.);
		}
		this->PolesPtr[i]=c;
	}
	
	
	//Zeros Processing
	
	for( int i=0;i<Nzeros;i++ )
	{
		Complex r=GetZero(i);
		Complex c(0);
		
		if( r==infinity )
		{
			c=Complex( -1, 0 );
		}
		else
		{
			// frequency transform
			c=r*k;
			// bilinear low-pass xform
			c=(c+1)/(-c+1.);
		}
		this->ZerosPtr[i]=c;
	}
	
	
	
	
}


void PoleFilter::HighPassTransf(void){

	
	Float32 w=2*M_PI*cutoffFreq;
	Float32 k=1./tan(w*0.5); // prewarp
	
	//Poles Processing
	
	for( int i=0;i<NPoles;i++ )
	{
		 Complex r=GetPole(i);
		
		Complex c(0);
		
		if( r==infinity )
		{
			c=Complex( 1, 0 );
		}
		else
		{
			// frequency transform
			c=r*k;
			// bilinear high-pass xform
			c=-(c+1.)/(-c+1.);
		}
	}
	
	
	//Zeros Processing

	for( int i=0;i<Nzeros;i++ )
	{
		Complex r=GetZero(i);
		
		Complex c(0);
		
		if( r==infinity )
		{
			c=Complex( 1, 0 );
		}
		else
		{
			// frequency transform
			c=r*k;
			// bilinear high-pass xform
			c=-(c+1.)/(-c+1.);
		}
	}
	
	
	
	w=M_PI-w;
	gain=gain;
	
}


void PoleFilter::BandPassTransf(void){


	Float32 angularWidth=2*M_PI*normWidth;
	m_wc2=2*M_PI*centerFreq-(angularWidth/2);
	m_wc =m_wc2+angularWidth;
	if( m_wc2<1e-8 )
		m_wc2=1e-8;
	if( m_wc >M_PI-1e-8 )
		m_wc =M_PI-1e-8;
	
	
	
	//Poles Processing 
	int n=NPoles;
	
	Complex *temp=malloc(n*sizeof(Complex));
	memcpy(temp,PolesPtr,n*sizeof(Complex));
	
	free(PolesPtr);
	NPoles=2*n;
	PolesPtr=malloc(2*n*sizeof(Complex));
	
	for( int i=0;i<n;i++ )
	{
		int j=2*i;
		Complex c=temp[i];
		if( c==infinity )
		{
			PolesPtr[j]=Complex( -1, 0 );
			PolesPtr[j+1]=Complex( 1, 0 );
		}
		else
		{
			// bilinear transform
			c=(c+1.)/(-c+1.); 
			PolesPtr[j]=BandPassTransformPoles( j, c );
			PolesPtr[j+1]=BandPassTransformPoles( j+1, c );
		}
	}
	
	//Zeros Procesing
	n=Nzeros;
	
	Complex *temp2=malloc(n*sizeof(Complex));
	memcpy(temp2,ZerosPtr,n*sizeof(Complex));
	
	free(ZerosPtr);
	Nzeros=2*n;
	ZerosPtr=malloc(2*n*sizeof(Complex));
	
	for( int i=0;i<n;i++ )
	{
		int j=2*i;
		Complex c=temp2[i];
		if( c==infinity )
		{
			ZerosPtr[j]=Complex( -1, 0 );
			ZerosPtr[j+1]=Complex( 1, 0 );
		}
		else
		{
			// bilinear transform
			c=(c+1.)/(-c+1.); 
			ZerosPtr[j]=BandPassTransformPoles( j, c );
			ZerosPtr[j+1]=BandPassTransformPoles( j+1, c );
		}
	}
	
	free(temp);
	free(temp2);
	
	if( w==0 ) // hack
	{
		Float32 angularWidth=2*M_PI*normWidth;
		Float32 wc2=2*M_PI*centerFreq-(angularWidth/2);
		Float32 wc =wc2+angularWidth;
		if( wc2<1e-8 )
			wc2=1e-8;
		if( wc >M_PI-1e-8 )
			wc =M_PI-1e-8;
		
		wc+=w;
		wc2+=w;
		w=2*atan(sqrt(tan(wc*0.5)*tan(wc2*0.5)));
	}
	else
	{
		// yes this is a giant hack to make shelves work
		w=((centerFreq)<0.25)?M_PI:0;
	}
	gain=gain;
}

Complex PoleFilter::BandPassTransformPoles(int i,Complex c){


	Float32 a=  cos((m_wc+m_wc2)*0.5)/cos((m_wc-m_wc2)*0.5);
	Float32 b=1/tan((m_wc-m_wc2)*0.5);
	Complex c2(0);
//	c2=addmul( c2, 4*(b*b*(a*a-1)+1), c );
	c2+=4*(b*b*(a*a-1)+1);
	c2*=c;
	
	c2+=8*(b*b*(a*a-1)-1);
	c2*=c;
	c2+=4*(b*b*(a*a-1)+1);
	c2= c2.Sqrt(c2);
	if ((i & 1) == 0)
		c2=-c2;
	//c2=addmul( c2, 2*a*b, c );
	c2+=2*a*b;
	c2*=c;
	
	c2+=2*a*b;
	Complex c3(0);
	//c3=addmul( c3, 2*(b-1), c );
	c3+= 2*(b-1);
	c3*=c;
	
	c3+=2*(1+b);
	return c2/c3;
	
	
	
}

void PoleFilter::BandStopTransf(void){

	
	//Poles Processing 
	
	
	Float32 angularWidth=2*M_PI*normWidth;
	m_wc2=2*M_PI*centerFreq-(angularWidth/2);
	m_wc =m_wc2+angularWidth;
	if( m_wc2<1e-8 )
		m_wc2=1e-8;
	if( m_wc >M_PI-1e-8 )
		m_wc =M_PI-1e-8;
	
	int n=NPoles;
	
	Complex *temp=malloc(n*sizeof(Complex));
	memcpy(temp,PolesPtr,n*sizeof(Complex));
	
	free(PolesPtr);
	NPoles=2*n;
	PolesPtr=malloc(2*n*sizeof(Complex));
	
	for( int i=0;i<n;i++ )
	{
		Complex c=temp[i];
		
		if( c==infinity )
		{
			c=Complex( -1, 0 );
		}
		else
		{
			// bilinear transform
			c=(c+1.)/(-c+1); 
		}
		int j=2*i;
		PolesPtr[j]=BandStopTransformPoles( j, c );
		PolesPtr[j+1]=BandStopTransformPoles( j+1, c );
	}
	
	
	//Zeros Processing 
	n=Nzeros;
	
	Complex *temp2=malloc(n*sizeof(Complex));
	memcpy(temp,ZerosPtr,n*sizeof(Complex));
	
	free(ZerosPtr);
	Nzeros=2*n;
	ZerosPtr=malloc(2*n*sizeof(Complex));
	
	for( int i=0;i<n;i++ )
	{
		Complex c=temp2[i];
		
		if( c==infinity )
		{
			c=Complex( -1, 0 );
		}
		else
		{
			// bilinear transform
			c=(c+1.)/(-c+1); 
		}
		int j=2*i;
		ZerosPtr[j]=BandStopTransformPoles( j, c );
		ZerosPtr[j+1]=BandStopTransformPoles( j+1, c );
	}

	free(temp);
	free(temp2);
	
	w=((centerFreq)<0.25)?M_PI:0;
	gain=gain;
	
}


Complex PoleFilter::BandStopTransformPoles(int i,Complex c){
	
	Float32 a=cos((m_wc+m_wc2)*.5) /cos((m_wc-m_wc2)*.5);
	Float32 b=tan((m_wc-m_wc2)*.5);
	Complex c2(0);
	//	c2=addmul( c2, 4*(b*b+a*a-1), c );
	c+=4*(b*b+a*a-1);
	c*=c;
	
	c2+=8*(b*b-a*a+1);
	c2*=c;
	c2+=4*(a*a+b*b-1);
	c2=c2.Sqrt(c2);
	c2*=((i&1)==0)?.5:-.5;
	c2+=a;
	//c2=addmul( c2, -a, c );
	c2+=-a;
	c*=c;
	Complex c3( b+1 );
	//c3=addmul( c3, b-1, c );
	
	c3+=b-1;
	c3*=c;
	
	
	return c2/c3;
	
	
}


