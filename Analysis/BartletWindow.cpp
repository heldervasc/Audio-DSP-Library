/*
 *  BartletWindow.cpp
 *  PU_Library
 *
 *  Created by Helder Vasconcelos on 10/10/15.
 *  Copyright 2010 AuGear. All rights reserved.
 *
 */

#include "BartletWindow.h"


void BartletWindow::FillBuffer() {
	

	int i;
	
	for (i = 0; i <this->NSamples; i++) {
	
		
		if (i<=NSamples/2){
		
			this->buffer[i]=2*i/NSamples;
		}else {
			this->buffer[i]=1-2*i/NSamples;
		}

	}
	
	
}

