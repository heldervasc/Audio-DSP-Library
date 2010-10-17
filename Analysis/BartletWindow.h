/*
 *  BartletWindow.h
 *  PU_Library
 *
 *  Created by Helder Vasconcelos on 10/10/15.
 *  Copyright 2010 AuGear. All rights reserved.
 *
 */

#ifndef BARTLETWINDOW_H
#define BARTLETWINDOW_H	

#include "Window.h"


//Bartlett Triangular


class BartletWindow : public  Window {
	
	
public:
	
	BartletWindow(UInt32 NSamples):Window(BARTLET_WINDOW,NSamples){}
	BartletWindow():Window(BARTLET_WINDOW,2048){}
	void FillBuffer();	
	
	
	
	
};

#endif

