// PCPParam.cpp: implementation of the PCPParam class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Euclid.h"
#include "PCPParam.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PCPParam::PCPParam(){
}
void PCPParam::set(long m, int d, BOOL e, CEdit *edit, CProgressCtrl *pr, BOOL irr){
	this->mod = m;
	this->progress = pr;
	this->endian = e;
	this->des_deg = d;
	this->output = edit;
	this->irred = irr;
}
PCPParam::~PCPParam()
{

}
