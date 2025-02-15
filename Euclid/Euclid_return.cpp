// Euclid_return.cpp: implementation of the Euclid_return class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Euclid.h"
#include "Poly_vect2.h"
#include "Euclid_return.h"
#include "EuclidDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
/* Вычисление алгоритма Евклида осуществляется в конструкторе, куда поступают
 * все необходимые указатели: A, B, Nod. Осуществляется разложение 
 * A*f + B*g = Nod.
 * Алгоритм работает так:
 * 1. f - g*Q1 = R1 = [1 -Q1] - вектор в единицах f и g т.е. 
 * R1 = [f g]*[1 -Q1]. При этом f = [1 0], g = [0 1]
 * . . . . . . . . . . . . .
 * i. R(i) = R(i-2) - R(i-1)*Q(i), а так как любой R(i) можно представить с 
 * помощью векторов, то все вычисления сводятся к работе с векторами. 
 * Вектора представляются классом Poly_vect2.
 */
Euclid_return::Euclid_return(Polynomial &f, Polynomial &g)
{
	Poly_vect2 n1, n2, tmp;
	Polynomial R, Q, TMP;
	long mod = f.Coeff[0].Module;
	int change;
	char one_ch[] = "1 ";
	char nul_ch[] = "0 ";
	Polynomial *one = new Polynomial(one_ch,2,mod);
	Polynomial *nul = new Polynomial(nul_ch,2,mod);
	
	n1.set(one,nul); n2.set(nul,one);	
	
	//сохранение входных данных чтобы не испортить их
	Polynomial N1 = f;//первое частное
	Polynomial N2 = g;//первый остаток
	//степень f (N1) всегда больше иначе, 
	//поменять местами f (N1) и g (N2)
	change = 0;
	if (N1.Deg<N2.Deg){
		TMP = N1; N1 = N2; N2 = TMP;
		change = 1;
	}
	
	while((N2.Coeff[0].Data != 0)||(N2.Deg > 0)){
		Div_poly &dp = N1.div(N2);//получение частного и остатка
		R.set(dp.Rem_deg, dp.Rem);
		Q.set(dp.Quot_deg, dp.Quot);
		N1 = N2;//теперь в делимом бывший остаток
		N2 = R;//остаток, частное в Q
		
		Poly_vect2 &t1 = n2.rize(Q);
		Poly_vect2 &t2 = n1.minus(t1);
		tmp.set(t2);//n1 = n1 - a*n2 == n3
		n1.set(n2); n2.set(tmp);//n1 = n2; n2 = n3		
	}
	//в n1 лежат коэфф разложения a и b
	//в N1 лежит НОД
	Nod = new Polynomial(N1.Deg, N1.Coeff);
	if (change){
		A = new Polynomial(n1.V2->Deg, n1.V2->Coeff);
		B = new Polynomial(n1.V1->Deg, n1.V1->Coeff);
	}
	else{
		A = new Polynomial(n1.V1->Deg, n1.V1->Coeff);
		B = new Polynomial(n1.V2->Deg, n1.V2->Coeff);
	}

	Nod->del_fict_coeff();
	A->del_fict_coeff();
	B->del_fict_coeff();

	delete one;
	delete nul;
}
///////////////////////////////////////////////////////////////////////
Euclid_return::~Euclid_return()
{
	delete  A;
	delete  B;
	delete  Nod;
}
