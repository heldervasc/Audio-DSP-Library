/*
 *  HanningWindow.h
 *  PU_Library
 *
 *  Created by Helder Vasconcelos on 10/10/15.
 *  Copyright 2010 AuGear. All rights reserved.
 *
 */

#ifndef HANNINGWINDOW_H
#define HANNINGWINDOW_H	

#include "Window.h"


class HanningWindow : public  Window{
	
	
public:
	
	HanningWindow(UInt32 NSamples):Window(HANNING_WINDOW,NSamples){}
	HanningWindow():Window(HANNING_WINDOW,2048){}
	
	void FillBuffer();	
	
	
	
	
};

#endif

