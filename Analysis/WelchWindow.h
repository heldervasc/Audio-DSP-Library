/*
 *  WelchWindow.h
 *  PU_Library
 *
 *  Created by Helder Vasconcelos on 10/10/15.
 *  Copyright 2010 AuGear. All rights reserved.
 *
 */

#ifndef WELCHWINDOW_H
#define WELCHWINDOW_H	

#include "Window.h"

/*
 SRC=http://github.com/jamoma/JamomaDSP/blob/master/extensions/WindowFunctionLib/WelchWindow.h
 */


class WelchWindow : public Window {
		
	
public:
	
	WelchWindow(UInt32 NSamples):Window(WELCH_WINDOW,NSamples){}

	WelchWindow():Window(WELCH_WINDOW,2048){}
	
	void FillBuffer();	
	
	
	
	
};

#endif
