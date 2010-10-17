/*
 *  ButterWorthLowPass.cpp
 *  PU_Library
 *
 *  Created by Helder Vasconcelos on 10/10/16.
 *  Copyright 2010 AuGear. All rights reserved.
 *
 */

#include "ButterWorthLowPass.h"


Complex ButterLowPass::GetZero( int i )
{
	return Complex( -1 );
}


Float32 ButterLowPass::PassbandHint( void )
{
	return 0;
}






