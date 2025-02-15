// Div_poly.h: interface for the Div_poly class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIV_POLY_H__E80F1841_94C1_11D5_A253_F19178BB15A3__INCLUDED_)
#define AFX_DIV_POLY_H__E80F1841_94C1_11D5_A253_F19178BB15A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Field.h"

class Div_poly  
{
public:
	Div_poly(int,int,long);
	Field *Quot, *Rem;
	int Quot_deg, Rem_deg;
	long Mod;
	CString remToString(BOOL endian = FALSE);
	CString quotToString(BOOL endian = FALSE);
	virtual ~Div_poly();

};

#endif // !defined(AFX_DIV_POLY_H__E80F1841_94C1_11D5_A253_F19178BB15A3__INCLUDED_)
