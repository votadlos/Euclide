// Period.cpp: implementation of the Period class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Euclid.h"
#include "Period.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
Period::Period(time_t oldt, time_t newt){
	long seconds = newt-oldt;
	this->hr = (long) seconds/3600;
	seconds -= this->hr*3600;
	this->mn = (long) seconds/60;
	seconds -= this->mn*60;
	this->sec = (long) seconds;
}
///////////////////////////////////////////////////////////////
CString Period::toString(){
	char str[10];
	sprintf(str,"%dh %dm %ds",hr,mn,sec);
	CString ret(str);
	return ret;
}
///////////////////////////////////////////////////////////////
Period::~Period(){
}
