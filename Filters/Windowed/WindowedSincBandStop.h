/*
 *  WindowedSincBandStop.h
 *  PU_Library
 *
 *  Created by Helder Vasconcelos on 10/10/14.
 *  Copyright 2010 AuGear. All rights reserved.
 *
 */

#ifndef WINDOWEDSBANDSTOP_H
#define WINDOWEDSBANDSTOP_H

#include "WindowedSincFilter.h"


class WindowedSincBandStop : public WindowedSincFilter {
	

public:
	
		virtual void Process( UInt32 frames , Float32 *dest, int skip=0 );
		
		WindowedSincBandStop():WindowedSincFilter(2){}
		
		WindowedSincBandStop(int channels):WindowedSincFilter(channels){}
	
};

#endif

