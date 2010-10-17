/*
 *  ButterWorthHighPass.h
 *  PU_Library
 *
 *  Created by Helder Vasconcelos on 10/10/16.
 *  Copyright 2010 AuGear. All rights reserved.
 *
 */
#ifndef BUTTERWHIGHPASS_H
#define BUTTERWHIGHPASS_H


#include "ButterWorthFilter.h"

class ButterHighPass : public ButterWorthFilter
{
public:
	
	
	ButterHighPass(UInt32 NPoles,UInt32 NChannels):ButterWorthFilter(NPoles,NChannels){ }
	ButterHighPass():ButterWorthFilter(int (4+1/2),2){}
	
	Complex GetZero( int i );
	
protected:
	Float32    PassbandHint    ( void );
};


#endif


