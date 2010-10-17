/*
 *  Filter.cpp
 *  Library
 *
 *  Created by Helder Vasconcelos on 10/10/07.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "CascadeFilter.h"
#include <cmath>
#include <cfloat>
#include <assert.h>
#include <memory.h>
#include <stdlib.h>

CascadeFilter::CascadeFilter(UInt32 Stages ,UInt32 Channels){
	
	m_nchan=Channels;
	m_nstage=Stages;
	m_stagep=(Stage*)malloc(m_nstage*sizeof(Stage));
	m_histp=(Hist*)malloc(m_nchan*m_nchan*sizeof(Hist));
	Clear();
	
}

CascadeFilter::CascadeFilter(){
	
	m_nchan=2;
	m_nstage=2;
	m_stagep=(Stage*) malloc(m_nstage *sizeof(Stage));
	m_histp=(Hist*)malloc(m_nchan*m_nstage*sizeof(Hist));
	Clear();
	
}


CascadeFilter::~CascadeFilter(){
	
	
	free(m_stagep);
	free(m_histp);
	
}




void CascadeFilter::ProcessI( UInt32 frames, Float32 *dest, int skip){

	
	if( m_nchan==2 )
		ProcessISSEStereo( frames, dest, skip );
	else{
	
		while( frames-- )
        {
            Hist *h=m_histp;
            for( int j=m_nchan;j;j-- )
            {
                Float32 in=Float32(*dest);
                Stage *s=m_stagep;
				
                for( int i=m_nstage;i;i--,h++,s++ )
                {
                    Float32 out;
                    out=s->b[0]*in + s->b[1]*h->v[0] + s->b[2]*h->v[1] + s->a[1]*h->v[2] + s->a[2]*h->v[3];
                    h->v[1]=h->v[0]; 
					h->v[0]=in;
                    h->v[3]=h->v[2]; 
					h->v[2]=out;
					
                    in=out;
                }
                *dest++=Float32(in);
            }
            dest+=skip;
        }
	
	
	}


}

void CascadeFilter::ProcessII( UInt32 frames,Float32 *dest, int skip){

	
	while( frames-- )
	{
		Hist *h=m_histp;
		for( int j=m_nchan;j;j-- )
		{
			Float32 in=Float32(*dest);
			Stage *s=m_stagep;
			for( int i=m_nstage;i;i--,h++,s++ )
			{
				Float32 d2=h->v[2]=h->v[1];
				Float32 d1=h->v[1]=h->v[0];
				Float32 d0=h->v[0]=
				in+s->a[1]*d1 + s->a[2]*d2;
				in=s->b[0]*d0 + s->b[1]*d1 + s->b[2]*d2;
			}
			*dest++=Float32(in);
		}
		dest+=skip;
	}
	

}

void CascadeFilter::Process( UInt32 frames , Float32  *dest, int skip ){

	
	ProcessI( frames, dest, skip );

}

Complex  CascadeFilter::Response( Float32 w ){

	Complex ch(1,0);
	
	Complex cbot(1,0);
	
	Complex czn1;
	Complex czn2;
	
	czn1.SetValueFromPolar(1., -w);
	czn2.SetValueFromPolar(1., -2*w);
		
	Stage *s=m_stagep;
	
	for( int i=m_nstage;i;i-- )
	{
		
		Complex ct( s->b[0],0 );
		Complex cb( 1 ,0);
		
		//ct=addmul( ct,  s.b[1], czn1 );
		//cb=addmul( cb, -s.a[1], czn1 );
		//ct=addmul( ct,  s.b[2], czn2 );
		//cb=addmul( cb, -s.a[2], czn2 );
		
		ct*=s->b[1];
		ct+=czn1;
		cb*=-s->a[1];
		cb+=czn1;
		ct*=s->b[2];
		ct+=czn2;
		cb*=-s->a[2];
		cb+=czn2;
		ch*=ct;
		cbot*=cb;
		s++;
	}
	
	return ch/cbot;
	
}

void CascadeFilter::Clear( void ){
	
	memset( m_histp, 0, m_nstage*m_nchan*sizeof(m_histp[0]) );
	

}
void  CascadeFilter::GetStages(Stage **stagesptr){

	*stagesptr=this->m_stagep;

}

/*Stage* CascadeFilter::GetStages(){

	
	return (Stage*)m_stagep;
}*/

void CascadeFilter::ProcessISSEStageStereo(UInt32 frames, Float32 *dest, Stage *s, Hist *h, int skip ){

		assert( m_nchan==2 );
	Float32 a1=s->a[1];
	Float32 a2=s->a[2];
	Float32 b0=s->b[0];
	Float32 b1=s->b[1];
	Float32 b2=s->b[2];
	while( frames-- )
	{
		Float32 in, out;
		
		in=Float32(*dest);
		out=b0*in+b1*h[0].v[0]+b2*h[0].v[1] +a1*h[0].v[2]+a2*h[0].v[3];
		h[0].v[1]=h[0].v[0]; h[0].v[0]=in;
		h[0].v[3]=h[0].v[2]; h[0].v[2]=out;
		in=out;
		*dest++=Float32(in);
		
		in=Float32(*dest);
		out=b0*in+b1*h[1].v[0]+b2*h[1].v[1] +a1*h[1].v[2]+a2*h[1].v[3];
		h[1].v[1]=h[1].v[0]; h[1].v[0]=in;
		h[1].v[3]=h[1].v[2]; h[1].v[2]=out;
		in=out;
		*dest++=Float32(in);
		
		dest+=skip;
	}
	

}

void CascadeFilter::ProcessISSEStereo( UInt32 frames, Float32 *dest, int skip ){


	assert( m_nchan==2 );
	Stage *s=m_stagep;
	Hist *h=m_histp;
	for( int i=m_nstage;i;i--,h+=2,s++ )
	{
		ProcessISSEStageStereo( frames, dest, s, h, skip );
	}

}

void CascadeFilter::Reset( void ){
		
	
	Stage *s=m_stagep;
	for( int i=m_nstage;i;i--,s++ ){
	
		s->a[0]=0;
		s->a[1]=0;
		s->a[2]=0;
		s->b[0]=0;
		s->b[1]=0;
		s->b[2]=0;
	
	}

}

void CascadeFilter::Scale( Float32 scale ){


	Stage *s=m_stagep;
	for( int i=m_nstage;i;i--,s++ ){
		
		
		s->b[0]*=scale;
		s->b[1]*=scale;
		s->b[2]*=scale;
		
	}
	
	
	
}

/*void CascadeFilter::SetAStage( Float32 x1, Float32 x2 ){


	Stage *s=m_stagep;
	for( int i=m_nstage;i;i-- )
	{
		if( s->a[1]==0 && s->a[2]==0 )
		{
			s->a[1]=x1;
			s->a[2]=x2;
			s=0;
			break;
		}
		if( s->a[2]==0 && x2==0 )
		{
			s->a[2]=-s->a[1]*x1;
			s->a[1]+=x1;
			s=0;
			break;
		}
		s++;
	}
	assert( s==0 );
	
	
	
}

void CascadeFilter::SetBStage( Float32 x0, Float32 x1, Float32 x2 ){

	
	Stage *s=m_stagep;
	for( int i=m_nstage;i;i-- )
	{
		if( s->b[1]==0 && s->b[2]==0 )
		{
			s->b[0]=x0;
			s->b[1]=x1;
			s->b[2]=x2;
			s=0;
			break;
		}
		if( s->b[2]==0 && x2==0 )
		{
			// (b0 + z b1)(x0 + z x1) = (b0 x0 + (b1 x0+b0 x1) z + b1 x1 z^2)
			s->b[2]=s->b[1]*x1;
			s->b[1]=s->b[1]*x0+s->b[0]*x1;
			s->b[0]*=x0;
			s=0;
			break;
		}
		s++;
	}
	assert( s==0 );

}

*/

void CascadeFilter::SetStage( Float32 a1, Float32 a2, Float32 b0, Float32 b1, Float32 b2 ){

	
	assert( m_nstage==1 );
	Stage *s=&m_stagep[0];
	s->a[1]=a1; s->a[2]=a2;
	s->b[0]=b0; s->b[1]=b1; s->b[2]=b2;


}



Float32 CascadeFilter::ResponseFunctor::operator()( Float32 w )
{
	Complex temp;
	
	temp=m_filter->Response( w );
	
	return - sqrt(temp.re*temp.re+temp.img*temp.img);
}

CascadeFilter::ResponseFunctor::ResponseFunctor( CascadeFilter *filter )
{
	m_filter=filter;
}

