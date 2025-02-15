// Euclid_return.h: interface for the Euclid_return class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EUCLID_RETURN_H__CC7155E1_ABA9_11D5_A253_9295C9AC94A3__INCLUDED_)
#define AFX_EUCLID_RETURN_H__CC7155E1_ABA9_11D5_A253_9295C9AC94A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/* Класс реализующий алгоритм Евклида для многчленов над полем.
 * Поступают в конструктор два многочлена над полем по ссылке.
 * В поступающие указатели кладутся расчитанные многочлены, 
 * доступные по переменным класса A, B, Nod.
 */

class Euclid_return  
{
public:
	Euclid_return(Polynomial &f, Polynomial &g);
	Polynomial *A, *B, *Nod;
	virtual ~Euclid_return();

};

#endif // !defined(AFX_EUCLID_RETURN_H__CC7155E1_ABA9_11D5_A253_9295C9AC94A3__INCLUDED_)
