/*
 *  WindowedSincHighPass.h
 *  PU_Library
 *
 *  Created by Helder Vasconcelos on 10/10/14.
 *  Copyright 2010 AuGear. All rights reserved.
 *
 */

#ifndef WINDOWEDSHIGHPASS_H
#define WINDOWEDSHIGHPASS_H

#include "WindowedSincFilter.h"



class WindowedSincHighPass : public WindowedSincFilter{
	
	
public:
	
	WindowedSincHighPass():WindowedSincFilter(2){}
	WindowedSincHighPass(int channels):WindowedSincFilter(channels){}
	
	virtual void Process( UInt32 frames , Float32 *dest, int skip=0 );
	
	
};
#endif

