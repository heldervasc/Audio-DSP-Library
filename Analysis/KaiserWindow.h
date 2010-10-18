/************************************************************************
 
 Product: Portable Audio Dsp Library 
 Version: V0.0.1
 File: KaiserWindow.h
 Creation date: 2010/08/10
 Author: Hélder Vasconcelos helder.vasc@e-2points.com 
 Description: Class Tester
 
 
 Copyright (c) 2010 Hélder Vasconcelos
 
 This library is free software; you can redistribute it and/or modify 
 it under the terms of the GNU Lesser General Public License as published by 
 the Free Software Foundation; either version 2.1 of the License, or 
 (at your option) any later version.
 
 This library is distributed in the hope that it will be useful, 
 but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
 or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License 
 for more details.
 
 You should have received a copy of the GNU Lesser General Public License 
 along with this library; if not, write to the Free Software Foundation, Inc., 
 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA 
 
 ****************************************************************************/

#ifndef KAISERWINDOW_H
#define KAISERWINDOW_H	

#include "Window.h"


class KaiserWindow : public  Window  {
	
	
public:
	
	KaiserWindow();
	
	KaiserWindow(UInt32 NSamples,double Beta);
	
	void FillBuffer();	
	
	void SetBeta(double Beta);

	double GetBeta();	
	

	
private:
	
	double BesselFunctionI0(double x);
	
	double mBesselIOofBeta;
	
	double Beta;
};




#endif
