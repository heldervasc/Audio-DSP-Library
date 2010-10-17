/*
 *  Window.cpp
 *  PU_Library
 *
 *  Created by Helder Vasconcelos on 10/10/14.
 *  Copyright 2010 AuGear. All rights reserved.
 *
 */

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




