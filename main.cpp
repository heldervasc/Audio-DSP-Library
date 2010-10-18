/************************************************************************

Copyright (c) 2010 Hélder Vasconcelos

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

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
