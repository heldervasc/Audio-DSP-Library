/*
 *  TrapezoidWindow.h
 *  PU_Library
 *
 *  Created by Helder Vasconcelos on 10/10/15.
 *  Copyright 2010 AuGear. All rights reserved.
 *
 */

#ifndef TRAPEZOIDWINDOW_H
#define TRAPEZOIDWINDOW_H	

#include "Window.h"


class TrapezoidWindow  : public  Window {
	
	
public:
	
	
	TrapezoidWindow();
	TrapezoidWindow(UInt32 NSamples,double Fade);
	
	virtual void FillBuffer();	
	
	//< Fade in/out as ratio of window length. 0 <= fade <= 0.5
	double Fade;
	
};

#endif

