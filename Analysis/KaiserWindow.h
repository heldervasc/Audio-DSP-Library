/*
 *  KaiserWindow.h
 *  PU_Library
 *
 *  Created by Helder Vasconcelos on 10/10/15.
 *  Copyright 2010 AuGear. All rights reserved.
 *
 */

#ifndef KAISERWINDOW_H
#define KAISERWINDOW_H	

#include "Window.h"


class KaiserWindow : public  Window  {
	
	
public:
	
	KaiserWindow();
	
	KaiserWindow(UInt32 NSamples,double Beta);
	
	void FillBuffer();	
	
	void SetBeta(double Beta);

	double GetBeta();	
	

	
private:
	
	double BesselFunctionI0(double x);
	
	double mBesselIOofBeta;
	
	double Beta;
};




#endif
