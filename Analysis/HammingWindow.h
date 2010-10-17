/*
 *  HammingWindow.h
 *  PU_Library
 *
 *  Created by Helder Vasconcelos on 10/10/15.
 *  Copyright 2010 AuGear. All rights reserved.
 *
 */

#ifndef HAMMINGWINDOW_H
#define HAMMINGWINDOW_H	

#include "Window.h"


class HammingWindow : public  Window{
	
	
public:
	
	HammingWindow(UInt32 NSamples):Window(HAMMING_WINDOW,NSamples){}
	HammingWindow():Window(HAMMING_WINDOW,2048){}
	void FillBuffer();	
	
	
	
	
};

#endif

