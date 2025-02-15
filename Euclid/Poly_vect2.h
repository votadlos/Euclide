// Poly_vect2.h: interface for the Poly_vect2 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POLY_VECT2_H__CE59EEC0_AC27_11D5_B90C_005004ED3E06__INCLUDED_)
#define AFX_POLY_VECT2_H__CE59EEC0_AC27_11D5_B90C_005004ED3E06__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Polynomial.h"

/* Вспомогательный класс (вектор из двух элементов) для реализации алгоритма 
 * Евклида с многочленами. Этим вектором представляется остаток от деления,
 * выраженный через исходные числа.
 */

class Poly_vect2  
{
public:
	Polynomial *V1;
	Polynomial *V2;
public:
	Poly_vect2(Polynomial *v11 = NULL, Polynomial *v22 = NULL);
	void set(Polynomial *, Polynomial *);
	void set(Poly_vect2 &);
	Poly_vect2 &minus(Poly_vect2 &);
	Poly_vect2 &rize(Polynomial &);
	Poly_vect2 &plus(Poly_vect2 &);
	virtual ~Poly_vect2();
};

#endif // !defined(AFX_POLY_VECT2_H__CE59EEC0_AC27_11D5_B90C_005004ED3E06__INCLUDED_)
