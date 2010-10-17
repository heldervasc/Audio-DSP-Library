/*
 *  RectangularWindow.h
 *  PU_Library
 *
 *  Created by Helder Vasconcelos on 10/10/15.
 *  Copyright 2010 AuGear. All rights reserved.
 *
 */

#ifndef RECTANGULARWINDOW_H
#define RECTANGULARWINDOW_H	

#include "Window.h"


class RectangularWindow : public  Window{
	
	
public:
	
	RectangularWindow(UInt32 NSamples):Window(RECTANGULAR_WINDOW,NSamples){}
	RectangularWindow():Window(RECTANGULAR_WINDOW,2048){}
	void FillBuffer();	
	
	
	
	
};

#endif

