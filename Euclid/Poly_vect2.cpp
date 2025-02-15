// Poly_vect2.cpp: implementation of the Poly_vect2 class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Euclid.h"
#include "Poly_vect2.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
Poly_vect2::Poly_vect2(Polynomial *v11, Polynomial *v22){
	if (v11) V1 = new Polynomial(*v11);
	else V1 = NULL;
	if (v22) V2 = new Polynomial(*v22);
	else V2 = NULL;
}
//////////////////////////////////////////////////////////////////////
Poly_vect2 &Poly_vect2::plus(Poly_vect2 &a){
	Polynomial &v1 = *(this->V1) + *(a.V1);
	Polynomial &v2 = *(this->V2) + *(a.V2);
	Poly_vect2 *tmp = new Poly_vect2(&v1,&v2);
	return *tmp;
}
//////////////////////////////////////////////////////////////////////
Poly_vect2 &Poly_vect2::minus(Poly_vect2 &a){
	Polynomial &v1 = *(this->V1) - *(a.V1);
	Polynomial &v2 = *(this->V2) - *(a.V2);
	Poly_vect2 *tmp = new Poly_vect2(&v1,&v2);
	return *tmp;
}
//////////////////////////////////////////////////////////////////////
Poly_vect2 &Poly_vect2::rize(Polynomial &a){
	Polynomial &v1 = *(this->V1) * a;
	Polynomial &v2 = *(this->V2) * a;
	Poly_vect2 *tmp = new Poly_vect2(&v1,&v2);
	return *tmp;
}
//////////////////////////////////////////////////////////////////////
void Poly_vect2::set(Poly_vect2 &a){
	delete V1;
	delete V2;
	V1 = new Polynomial(*(a.V1));
	V2 = new Polynomial(*(a.V2));
}
//////////////////////////////////////////////////////////////////////
void Poly_vect2::set(Polynomial *v11, Polynomial *v22){
	delete V1;
	delete V2;
	V1 = new Polynomial(*v11);
	V2 = new Polynomial(*v22);
}
//////////////////////////////////////////////////////////////////////
Poly_vect2::~Poly_vect2()
{
	delete V1;
	delete V2;
}
