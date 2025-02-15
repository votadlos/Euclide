//Класс - вектор из 2-х элементов
#include "stdafx.h"
#include "Vect2.h"
#include <iostream.h>

//*************************************************
Vect2::Vect2(long vv1, long vv2){
	v1 = vv1;
	v2 = vv2;
}
//*************************************************
Vect2::Vect2(){
	v1 = 0;
	v2 = 0;
}
//*************************************************
Vect2 Vect2::rize(long a){
	Vect2 tmp;
	tmp.v1 = a*this->v1;
	tmp.v2 = a*this->v2;
	return tmp;
}
//*************************************************
Vect2 Vect2::sum(Vect2 nvect){
	Vect2 tmp;
	tmp.v1 = this->v1 + nvect.v1;
	tmp.v2 = this->v2 + nvect.v2;
	return tmp;
}
//*************************************************
Vect2 Vect2::minus(Vect2 nvect){
	Vect2 tmp;
	tmp.v1 = this->v1 - nvect.v1;
	tmp.v2 = this->v2 - nvect.v2;
	return tmp;
}
//*************************************************
void Vect2::show(long a1, long a2, long nodd){
	cout<<"NOD = "<<nodd<<" = "<<v1<<"*"<<a1<<" + "<<v2<<"*"<<a2<<"\n";
}
//*************************************************
void Vect2::show(){
	cout<<"v1 = "<<v1<<"; v2 = "<<v2<<endl;
}
//*************************************************
void Vect2::set(long a1, long a2){
	this->v1 = a1;
	this->v2 = a2;
}
//*************************************************
void Vect2::set(Vect2 v){
	this->v1 = v.v1;
	this->v2 = v.v2;
}
//*************************************************
Vect2::~Vect2(){
}
