/************************************************************************

Copyright (c) 2010 Hélder Vasconcelos

    This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License along with this library; if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA 

****************************************************************************/

#include <iostream>

#include "FFT.h"
#include "WavReader.h"
#include "Complex.h"
#include "Window.h"
#include "HammingWindow.h"
#include "WindowedSincLowPass.h"
#include "KaiserWindow.h"

#define NSamples 16384

int main (int argc, char * const argv[]) {
   
	char * filename="/Users/heldervasconcelos/Desktop/re_axis/presets/Samples/kicks/tunekick3.wav";
	
	WavReader * wavfile=new WavReader(filename);
	
	FFT * ffttest=new  FFT(wavfile->GetSampleRate());
	
	float * buffer=(float *)malloc(NSamples*sizeof(Float32));
	
	memset(buffer, 0, NSamples*sizeof(Float32));
	
	//wavfile->Read(buffer,16800);
	wavfile->Read(buffer,NSamples);
	
	
	
	ffttest->AllocateFTBuffer(NSamples);
	
	printf("Calculating .....\n");
	
	clock_t start;
	
	clock_t elapsed;
	
	
	//HammingWindow *das= new HammingWindow(5000);
	//WindowedSincLowPass *  myobj=new WindowedSincLowPass(2); 

	//ffttest->RealSplitRadixFFT(buffer, NSamples);

	
	
	Complex *x=(Complex *)malloc(NSamples*sizeof(Complex));
	
	int i;
	for (i=0; i<NSamples; i++) {
		
		x[i].re=(float)buffer[i];
		x[i].img=0;
	}
	
	
		start = clock();
	
	//ffttest->GetDFT(x, NSamples, DIRECT_DIRECTION);
		//ffttest->RealSplitRadixFFT(buffer, NSamples);
		
		//ffttest->CT_FFT(x, NSamples);
		
		elapsed = clock() - start;
	
	//	printf("Time = %ld cycles\n", (long)elapsed);
	
	ffttest->CT_FFT(x, 16384);
	
	//ffttest->RealSplitRadixFFT(buffer, NSamples);
	
	//ffttest->IRealSplitRadixFFT(buffer, NSamples);
	
	
	
		
	for (long i=1;i<(NSamples/2);i+=1){
	
			
		printf("Frequency = %f| Amplitude = %f | Phase= %f \n",ffttest->GetFrequency(i),ffttest->GetMagnitude(i),ffttest->GetPhase(i));
		
		
	}
		
	delete wavfile;
	delete ffttest;
	free(buffer);
	
	double temp10=21.3;
	int valor=50;
	
	KaiserWindow *dasd= new KaiserWindow(5000,0.5);
	
	dasd->FillBuffer();
	//dasd->FillBuffer();
	
	
	
	
	
	
	   
    return 0;
}
