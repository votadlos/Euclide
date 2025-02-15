// PCIParam.cpp: implementation of the PCIParam class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Euclid.h"
#include "PCIParam.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
PCIParam::PCIParam(){
}
PCIParam::set(int ell, long modd, CEdit *e, BOOL endian,CProgressCtrl *pr){
	this->progress = pr;
	this->el = ell;
	this->m_Endian = endian;
	this->m_EditPolyMod = e;
	this->mod = modd;
}

PCIParam::~PCIParam(){
}
