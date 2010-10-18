/************************************************************************
 
 Product: Portable Audio Dsp Library 
 Version: V0.0.1
 File: FFT.cpp
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

#include "FFT.h"

#include <stdio.h>

FFT::FFT(Float32 SampleFrequency){


	this->SampleFrequency=SampleFrequency;
	

}

FFT::~FFT(){
	
	

}

int FFT::GetDFT(Complex *x,long nSamples,FFT_Direction dir){


    long bin, k;
	
	double arg, sign = -1.; /* sign = -1 -> FFT, 1 -> iFFT */
	
	
	
	
	for (bin = 0; bin <= nSamples/2; bin++) {
		
		results[bin].re = (results[bin].re = 0.);
		
		for (k = 0; k < nSamples; k++) {
			
			arg = 2.*(Float32)bin*M_PI*(Float32)k / (Float32)nSamples;
			
			results[bin].re += x[k].re * sign * sin(arg);
			
			results[bin].img += x[k].re * cos(arg);
			
		}
		
	}
	
	return 0;

}
int FFT::AllocateFTBuffer(long nSamples){
	
	this->nSamples=nSamples;

	results=(Complex *)malloc(nSamples*sizeof(Complex));
	
	if (results){
	
		return 0;
	}else 
		return -1;

}

void FFT::FreeFTBuffer(){

	
	if (results){
		
		free(results);
	}


}

int FFT::SetSampleFrequency(Float32 SampleFrequency){

	this->SampleFrequency=SampleFrequency;
	
	return 0;
}
Float32 FFT::GetSampleFrequency(){

	return SampleFrequency;

}



Float32 FFT::GetFrequency(long n){

	if (n<=nSamples/2){
	
		return (Float32)n * SampleFrequency / (Float32)nSamples;
		
	}else {
		return (Float32)0;
	}


}

 Float32 FFT::GetMagnitude(long n){

	if (n<=nSamples/2){
		
		return  20. * log10( 2. * sqrt( results[n].re  * results[n].re  +results[n].img * results[n].img) / (float)nSamples);
	}else {
		return (Float32)0;
	}


}
Float32 FFT::GetPhase(long n){


	if (n<=nSamples/2){
		
		return 180.*atan2(results[n].re , results[n].img) / M_PI - 90.;
		
	}else {
		return (Float32)0;
	}



}


	
//////////////////////////////////
//	Cooley-Tukey FFT algorithm 
/////////////////////////////////////
//
// Complex* out = (complex*) malloc(sizeof(struct complex_t) * N);
// Complex* scratch = (complex*) malloc(sizeof(struct complex_t) * N);
// Complex* twiddles = FFT_get_twiddle_factors(N);
// FFT_calculate(x, N, out, scratch, twiddles);
// free(twiddles);
// free(scratch);
//
void FFT::CT_FFT(Complex *x,long nSamples){


	
	Complex * scratch = (Complex *) malloc(sizeof(Complex) * nSamples);
    Complex * twiddles = FFT_get_twiddle_factors(nSamples);
	
	
	int k, m, n;
    int skip;
    bool evenIteration = nSamples & 0x55555555;
    Complex* E;
    Complex* Xp,* Xp2,  * Xstart;
	
	if (nSamples==1){
	
	
		results[0]=x[0];
		return ;
	
	}

	
	E=x;
	
	for (n=1;n<nSamples;n*=2){
		
		
		Xstart = evenIteration? scratch : results;
        skip = nSamples/(2 * n);
        /* each of D and E is of length n, and each element of each D and E is
		 separated by 2*skip. The Es begin at E[0] to E[skip - 1] and the Ds
		 begin at E[skip] to E[2*skip - 1] */
        Xp = Xstart;
        Xp2 = Xstart + nSamples/2;
        for(k = 0; k != n; k++) {
        	float tim = twiddles[k * skip].img;
        	float tre = twiddles[k * skip].re;
            for (m = 0; m != skip; ++m) {
            	Complex* D = E + skip;
            	/* twiddle *D to get dre and dim */
            	float dre = D->re * tre - D->img * tim;
            	float dim = D->re * tim + D->img * tre;
                Xp->re = E->re + dre;
                Xp->img = E->img + dim;
                Xp2->re = E->re - dre;
                Xp2->img = E->img - dim;
                ++Xp;
                ++Xp2;
                ++E;
            }
            E += skip;
        }
        E = Xstart;
        evenIteration = !evenIteration;
	
	
	
	
	}
	
	
	free(twiddles);
    free(scratch);
	
}


Complex* FFT::FFT_get_twiddle_factors(int N) {
	
    Complex* twiddles = (Complex*) malloc(sizeof(struct Complex) * N);
    int k;
    for (k = 0; k != N; ++k) {
        
		//twiddles[k] = complex_from_polar(1.0, );
		
		twiddles[k].re =cos(-2.0*M_PI*k/N);
		twiddles[k].img=sin(-2.0*M_PI*k/N);
    }
    return twiddles;
}




// Source: 
// Sorensen et al: Real-Valued Fast Fourier Transform Algorithms,
// IEEE Trans. ASSP, ASSP-35, No. 6, June 1987

void FFT::RealSplitRadixFFT(Float32 *data,int n){


	long i,j,k,i5,i6,i7,i8,i0,id,i1,i2,i3,i4,n2,n4,n8;
	double t1,t2,t3,t4,t5,t6,a3,ss1,ss3,cc1,cc3,a,e,sqrt2;
	
	sqrt2=sqrt(2.0);
	n4=n-1;
	
	//data shuffling
	for (i=0,j=0,n2=n/2; i<n4 ; i++){
		if (i<j){
			t1=data[j];
			data[j]=data[i];
			data[i]=t1;
		}
		k=n2;
		while (k<=j){
			j-=k;
			k>>=1;	
		}
		j+=k;
	}
	
	/*----------------------*/
	
	//length two butterflies	
	i0=0;
	id=4;
	do{
		for (; i0<n4; i0+=id){ 
			i1=i0+1;
			t1=data[i0];
			data[i0]=t1+data[i1];
			data[i1]=t1-data[i1];
		}
		id<<=1;
		i0=id-2;
		id<<=1;
    } while ( i0<n4 );
	
	/*----------------------*/
	//L shaped butterflies
	n2=2;
	for(k=n;k>2;k>>=1){  
		n2<<=1;
		n4=n2>>2;
		n8=n2>>3;
		e = 2*M_PI/(n2);
		i1=0;
		id=n2<<1;
		do{ 
			for (; i1<n; i1+=id){
				i2=i1+n4;
				i3=i2+n4;
				i4=i3+n4;
				t1=data[i4]+data[i3];
				data[i4]-=data[i3];
				data[i3]=data[i1]-t1;
				data[i1]+=t1;
				if (n4!=1){
					i0=i1+n8;
					i2+=n8;
					i3+=n8;
					i4+=n8;
					t1=(data[i3]+data[i4])/sqrt2;
					t2=(data[i3]-data[i4])/sqrt2;
					data[i4]=data[i2]-t1;
					data[i3]=-data[i2]-t1;
					data[i2]=data[i0]-t2;
					data[i0]+=t2;
				}
			}
			id<<=1;
			i1=id-n2;
			id<<=1;
		} while ( i1<n );
		a=e;
		for (j=2; j<=n8; j++){  
			a3=3*a;
			cc1=cos(a);
			ss1=sin(a);
			cc3=cos(a3);
			ss3=sin(a3);
			a=j*e;
			i=0;
			id=n2<<1;
			do{
				for (; i<n; i+=id){  
					i1=i+j-1;
					i2=i1+n4;
					i3=i2+n4;
					i4=i3+n4;
					i5=i+n4-j+1;
					i6=i5+n4;
					i7=i6+n4;
					i8=i7+n4;
					t1=data[i3]*cc1+data[i7]*ss1;
					t2=data[i7]*cc1-data[i3]*ss1;
					t3=data[i4]*cc3+data[i8]*ss3;
					t4=data[i8]*cc3-data[i4]*ss3;
					t5=t1+t3;
					t6=t2+t4;
					t3=t1-t3;
					t4=t2-t4;
					t2=data[i6]+t6;
					data[i3]=t6-data[i6];
					data[i8]=t2;
					t2=data[i2]-t3;
					data[i7]=-data[i2]-t3;
					data[i4]=t2;
					t1=data[i1]+t5;
					data[i6]=data[i1]-t5;
					data[i1]=t1;
					t1=data[i5]+t4;
					data[i5]-=t4;
					data[i2]=t1;
				}
				id<<=1;
				i=id-n2;
				id<<=1;
			} while(i<n);
		}
	}
	
	//division with array length
	//for(i=0;i<n;i++) data[i]/=n;
	
	
	/*for(i=0;i<n;i++){
	
		printf("Result before %i = %f \n",i,x[i]);
	}*/
	
	results[0].re=data[0];
	results[0].img=0;
	results[n/2].re=data[n/2];
	results[n/2].img=0;
	
	for(i=1;i<n/2;i++){
	
		results[i].re=data[i];
		results[i].img=data[n-i];
	}
	
	/*for(i=0;i<=n/2;i++){
	
		printf("ResultAfter %i = re= %f img= %f \n",i,results[i].re,results[i].img);
	
	}*/
	

}

/////////////////////////////////////////////////////////
// Sorensen in-place inverse split-radix FFT for real values
// data: array of doubles:
// re(0),re(1),re(2),...,re(size/2),im(size/2-1),...,im(1)
// 
// output:
// re(0),re(1),re(2),...,re(size-1)
// NOT normalized by array length
//
// Source: 
// Sorensen et al: Real-Valued Fast Fourier Transform Algorithms,
// IEEE Trans. ASSP, ASSP-35, No. 6, June 1987


void FFT::IRealSplitRadixFFT(Float32 *y,int n){


	
	
	Float32 *data=(Float32 *)malloc(n*sizeof(Float32));
	
	data[0]=results[0].re;
	data[n/2]=results[n/2].re;
	
	/*int h=0;
	for (h=0; h<=n/2; h++) {
		printf("Result Before %i = re= %f img= %f \n",h,results[h].re,results[h].img);

	}*/
	
	for (int i=1;i<n/2;i++){
	
		data[i]=results[i].re;		
		data[n/2+i]=results[n/2-i].img;
	
	}
	
	/*for (h=0; h<n; h++){
		printf("Result After %i = val %f \n",h,data[h]);
	
	}*/

	long i,j,k,i5,i6,i7,i8,i0,id,i1,i2,i3,i4,n2,n4,n8,n1;
	double t1,t2,t3,t4,t5,a3,ss1,ss3,cc1,cc3,a,e,sqrt2;
	
	sqrt2=sqrt(2.0);
	
	n1=n-1;
	n2=n<<1;
	for(k=n;k>2;k>>=1){  
		id=n2;
		n2>>=1;
		n4=n2>>2;
		n8=n2>>3;
		e = 2*M_PI/(n2);
		i1=0;
		do{ 
			for (; i1<n; i1+=id){
				i2=i1+n4;
				i3=i2+n4;
				i4=i3+n4;
				t1=data[i1]-data[i3];
				data[i1]+=data[i3];
				data[i2]*=2;
				data[i3]=t1-2*data[i4];
				data[i4]=t1+2*data[i4];
				if (n4!=1){
					i0=i1+n8;
					i2+=n8;
					i3+=n8;
					i4+=n8;
					t1=(data[i2]-data[i0])/sqrt2;
					t2=(data[i4]+data[i3])/sqrt2;
					data[i0]+=data[i2];
					data[i2]=data[i4]-data[i3];
					data[i3]=2*(-t2-t1);
					data[i4]=2*(-t2+t1);
				}
			}
			id<<=1;
			i1=id-n2;
			id<<=1;
		} while ( i1<n1 );
		a=e;
		for (j=2; j<=n8; j++){  
			a3=3*a;
			cc1=cos(a);
			ss1=sin(a);
			cc3=cos(a3);
			ss3=sin(a3);
			a=j*e;
			i=0;
			id=n2<<1;
			do{
				for (; i<n; i+=id){  
					i1=i+j-1;
					i2=i1+n4;
					i3=i2+n4;
					i4=i3+n4;
					i5=i+n4-j+1;
					i6=i5+n4;
					i7=i6+n4;
					i8=i7+n4;
					t1=data[i1]-data[i6];
					data[i1]+=data[i6];
					t2=data[i5]-data[i2];
					data[i5]+=data[i2];
					t3=data[i8]+data[i3];
					data[i6]=data[i8]-data[i3];
					t4=data[i4]+data[i7];
					data[i2]=data[i4]-data[i7];
					t5=t1-t4;
					t1+=t4;
					t4=t2-t3;
					t2+=t3;
					data[i3]=t5*cc1+t4*ss1;
					data[i7]=-t4*cc1+t5*ss1;
					data[i4]=t1*cc3-t2*ss3;
					data[i8]=t2*cc3+t1*ss3;
				}
				id<<=1;
				i=id-n2;
				id<<=1;
			} while(i<n1);
		}
	}	
	
	/*----------------------*/
	i0=0;
	id=4;
	do{
		for (; i0<n1; i0+=id){ 
			i1=i0+1;
			t1=data[i0];
			data[i0]=t1+data[i1];
			data[i1]=t1-data[i1];
		}
		id<<=1;
		i0=id-2;
		id<<=1;
    } while ( i0<n1 );
	
	/*----------------------*/
	
	//data shuffling
	for (i=0,j=0,n2=n/2; i<n1 ; i++){
		if (i<j){
			t1=data[j];
			data[j]=data[i];
			data[i]=t1;
		}
		k=n2;
		while (k<=j){
			j-=k;
			k>>=1;	
		}
		j+=k;
	}	





	free(data);




}




