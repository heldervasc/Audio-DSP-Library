/************************************************************************
 
 Product: Portable Audio Dsp Library 
 Version: V0.0.1
 File: Window.cpp
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

#include "Window.h"

#include <stdio.h>
#include <stdlib.h>



Window::Window(WindowType wtype,UInt32 NSamples){
	
	
	this->type=wtype;
	this->NSamples=NSamples;
	buffer=malloc(NSamples*sizeof(double));
		
}

Window::Window(){
	
	
	this->type=HAMMING_WINDOW;
	this->NSamples=2048;
	buffer=malloc(NSamples*sizeof(double));
	
	
}

Window::~Window(){
	
	free(buffer);
	
}


void Window::Mult(Float32 *data,Float32 *out){
	
	int i;
	for (i=0;i<NSamples; i++) {
		
		out[i]=(Float32)buffer[i]*data[i];
	}
	
}


void Window::Div(Float32 *data,Float32 *out){
	
	int i;
	for (i=0;i<NSamples; i++) {
		
		out[i]=(Float32)buffer[i]/data[i];
	}
	
}


void Window::Sub(Float32 *data,Float32 *out){
	int i;
	for (i=0;i<NSamples; i++) {
		
		out[i]=(Float32)buffer[i]-data[i];
	}
	
}


void Window::Add(Float32 *data,Float32 *out){
	
	int i;
	for (i=0;i<NSamples; i++) {
		
		out[i]=(Float32)buffer[i]+data[i];
	}
	
	
}


void Window::Mult(double *data,double *out){
	
	int i;
	for (i=0;i<NSamples; i++) {
		
		out[i]=buffer[i]*data[i];
	}
	
}


void Window::Div(double *data,double *out){
	
	int i;
	for (i=0;i<NSamples; i++) {
		
		out[i]=buffer[i]/data[i];
	}
	
}


void Window::Sub(double *data,double *out){
	
	int i;
	for (i=0;i<NSamples; i++) {
		
		out[i]=buffer[i]-data[i];
	}
	
}



void Window::Add(double *data,double *out){
	
	
	int i;
	for (i=0;i<NSamples; i++) {
		
		out[i]=buffer[i]+data[i];
	}
	
}


WindowType Window::GetType(){
	
	return this->type;
}


double Window::GetValue(unsigned int i){
	
	if (i>0&&i<NSamples){
		
		return buffer[i];
	}else {
		return 0;
	}
	
	
}


UInt32 Window::GetNSamples(){
	
	return this->NSamples;
	
}




