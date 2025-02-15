// Period.h: interface for the Period class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PERIOD_H__C3EB2401_AF41_11D5_A253_8BB1987990A3__INCLUDED_)
#define AFX_PERIOD_H__C3EB2401_AF41_11D5_A253_8BB1987990A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <time.h>

class Period  
{
public:
	Period(time_t oldt=0, time_t newt=time(NULL));
	CString toString();
	virtual ~Period();
public:
	long hr,mn,sec;

};

#endif // !defined(AFX_PERIOD_H__C3EB2401_AF41_11D5_A253_8BB1987990A3__INCLUDED_)
