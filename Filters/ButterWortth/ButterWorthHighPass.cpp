/*
 *  ButterWorthHighPass.cpp
 *  PU_Library
 *
 *  Created by Helder Vasconcelos on 10/10/16.
 *  Copyright 2010 AuGear. All rights reserved.
 *
 */

#include "ButterWorthHighPass.h"


Complex ButterHighPass::GetZero( int i )
{
	return Complex( 1 );
}


Float32 ButterHighPass::PassbandHint( void )
{
	return M_PI;
}


