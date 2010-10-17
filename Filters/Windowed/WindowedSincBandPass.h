/*
 *  WindowedSincBandPass.h
 *  PU_Library
 *
 *  Created by Helder Vasconcelos on 10/10/14.
 *  Copyright 2010 AuGear. All rights reserved.
 *
 */

#ifndef WINDOWEDSBANDPASS_H
#define WINDOWEDSBANDPASS_H

#include "WindowedSincFilter.h"



class WindowedSincBandPass : public WindowedSincFilter {
	
	
public:
		virtual void Process( UInt32 frames , Float32 *dest, int skip=0 );
		
		WindowedSincBandPass():WindowedSincFilter(2){}
		WindowedSincBandPass(int channels):WindowedSincFilter(channels){}
	
};
#endif
