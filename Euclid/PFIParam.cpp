// PFIParam.cpp: implementation of the PFIParam class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Euclid.h"
#include "PFIParam.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
PFIParam::PFIParam(){
}
PFIParam::set(long m, CEdit *e, BOOL endian,CProgressCtrl *pr){
	this->progress = pr;
	this->mod = m;
	this->m_Endian = endian;
	this->m_EditPolyMod = e;
}

PFIParam::~PFIParam(){
}
