// Vect2.h: interface for the Vect2 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VECT2_H__622D3C87_1FAE_11D5_A252_A92AEB378C88__INCLUDED_)
#define AFX_VECT2_H__622D3C87_1FAE_11D5_A252_A92AEB378C88__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Vect2  
{
public:
	long v1;
	long v2;
public:
	Vect2(long, long);
	Vect2();
	Vect2 rize(long);
	void show(long,long,long);
	void show();
	void set(long,long);
	void set(Vect2);
	Vect2 sum(Vect2);
	Vect2 minus(Vect2);
	virtual ~Vect2();
};

#endif // !defined(AFX_VECT2_H__622D3C87_1FAE_11D5_A252_A92AEB378C88__INCLUDED_)
