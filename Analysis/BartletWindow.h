/*********************************************************
//
// Module: Audio DSP Library
// Version: V0.1
// File: BartletWindow.h
// Creation date: 2010/10/18
// Author: Hélder Vasconcelos 
// Description: 
//
*******************************************************************/

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

