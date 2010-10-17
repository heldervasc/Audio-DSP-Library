/*
 *  Complex.cpp
 *  Equalizer
 *
 *  Created by Helder Vasconcelos on 10/10/01.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "Complex.h"

#include <math.h>



Complex::Complex(){
	
	this->re=0;
	this->img=0;
	
	
}

Complex::Complex( Float32 re,Float32 img=0 ){
	
	this->re=re;
	this->img=img;
	
}


Complex::~Complex(){
	
	
	
}


Float32 Complex::GetPolarMagnitude(){
	
	
	return sqrt(pow (re,2)+pow (img,2));
}


Float32 Complex::GetPolarAngle(){
	
	if (re==0&&img==0) {
		return 0;
	}else {
		
		return atan(img/re);
		
	}
	
	
}


void Complex::SetValueFromPolar(Float32 mag,Float32 ang){
	
	
	re=mag*cos((double)ang);
	img=mag*sin((double)ang);
	
}


void Complex::SetValueFromCart(Float32 re,Float32 img){
	
	this->re=re;
	this->img=img;
	
	
}

Complex		Complex::operator+    ( Complex v ){
	
	
	
	return Complex(this->re+v.re,this->img+v.img);
	
}


Complex		Complex::operator-    ( Complex v ){
	
	
	return Complex(this->re - v.re, this->img - v.img);	
	
}


Complex		Complex::operator*    ( Complex v ){
	
	
	return Complex(this->re*v.re - this->img*v.img,
					  this->re*v.img + this->img*v.re);	
	
	
}



//abs(x)
Float32			Complex::Norm(){
	
	
	return this->re*this->re + this->img*this->img;
	
}

//|x|
Complex		Complex::Conjugate(){
	
	
	return Complex(this->re, -this->img);
	
}


Complex	Complex::operator/    ( Complex v ){
	
	
	
	
	return (*this)*v.Conjugate()/v.Norm();
	
	
}



Complex &    Complex::operator+=    ( Complex v ){
	
	
	
	this->re=this->re+v.re;
	this->img=this->img+v.img;
	
	return (*this);
}


Complex &    Complex::operator-=    ( Complex v ){
	
	this->re=this->re-v.re;
	this->img=this->img-v.img;
	
	return (*this);
}


Complex &    Complex::operator*=    ( Complex v ){
	
	this->re=(this->re*v.re-this->img*v.img);
	this->img=(this->re*v.img+this->re*v.img+this->img*v.re);
	
	return (*this);
}


Complex &    Complex::operator/=    ( Complex v ){
	
	
	
	*this=(*this)*v.Conjugate()/v.Norm();
	
	return (*this);
}



bool			Complex::operator== (Complex v ){
	
	
	if ((this->re==v.re)&&(this->img==v.img)) {
		
		return true;
	}else {
		return false;
	}
	
	
}
Complex &    Complex::operator+=    ( Float32 v){
	
	
	
	this->re=this->re+v;
	this->img=this->img+v;
	
	return (*this);
}


Complex &    Complex::operator-=    ( Float32 v){
	
	this->re=this->re-v;
	this->img=this->img-v;
	
	return (*this);
}


Complex &    Complex::operator*=    ( Float32 v ){
	
	Complex temp(v,0);

	*this=(*this) * temp;
	//this->re=(this->re*v.re-this->img*v.img);
	//this->img=(this->re*v.img+this->re*v.img+this->img*v.re);
	
	return (*this);
}


Complex &    Complex::operator/=    ( Float32 v){
	
	Complex temp(v,0);
	
	*this=(*this)/v;
	
	return (*this);
}

Complex Complex::operator+(Float32  rhs) {	
	
    
	return Complex(this->re + rhs, this->img);
	
	
}
Complex Complex::operator-(Float32  rhs) {
    
	return Complex(this->re - rhs, this->img);
	
}
Complex Complex::operator*(Float32  rhs) {
    
	return Complex(this->re * rhs, this->img * rhs);
	
}

Complex Complex::operator/(Float32  rhs) {
    
	return  Complex(this->re/rhs, this->img/rhs);
	
}

Complex Complex::operator- (void){


	return Complex(-this->re,-this->img);

}

Complex Complex::Sqrt( Complex &c )
{
	Float32 a=sqrt(c.GetPolarMagnitude());
	Float32 b=0.5*c.GetPolarAngle();
	return Polar( a,b );
}


Complex Complex::Polar(Float32 &m,  Float32 &a )
{
	return Complex( m*cos(a), m*sin(a) );
}



