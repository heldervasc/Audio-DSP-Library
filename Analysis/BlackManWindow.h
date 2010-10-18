/*********************************************************
//
// Module: Audio DSP Library
// Version: V0.1
// File: BlackManWindow.h
// Creation date: 2010/10/18
// Author: Hélder Vasconcelos
// Description:
//
*******************************************************************/

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

