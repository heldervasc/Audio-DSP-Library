/*
 *  WindowedSincLowPass.h
 *  PU_Library
 *
 *  Created by Helder Vasconcelos on 10/10/14.
 *  Copyright 2010 AuGear. All rights reserved.
 *
 */


#ifndef WINDOWEDSLOWPASS_H
#define WINDOWEDSLOWPASS_H

#include "WindowedSincFilter.h"


class WindowedSincLowPass : public WindowedSincFilter {
	

public:
	
	
	WindowedSincLowPass():WindowedSincFilter(2){}
	WindowedSincLowPass(int channels):WindowedSincFilter(channels){}
	
    virtual void Process( UInt32 frames , Float32 *dest, int skip=0 );

	
};




#endif
