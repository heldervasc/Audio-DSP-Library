/*
 *  BlackManWindow.h
 *  PU_Library
 *
 *  Created by Helder Vasconcelos on 10/10/15.
 *  Copyright 2010 AuGear. All rights reserved.
 *
 */

#ifndef BLACKMANWINDOW_H
#define BLACKMANWINDOW_H	

#include "Window.h"


class BlackManWindow : public  Window{
	
	
public:

	BlackManWindow(UInt32 NSamples):Window(BLACKMAN_WINDOW,NSamples){}
	BlackManWindow():Window(BLACKMAN_WINDOW,2048){}
	void FillBuffer();	
	
	
	
	
};

#endif

