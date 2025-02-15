// Div_poly.cpp: implementation of the Div_poly class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Euclid.h"
#include "Div_poly.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

////////////////////////////
// Construction/Destruction
////////////////////////////

Div_poly::Div_poly(int q_deg, int r_deg, long mod){
	Quot_deg = q_deg;
	Rem_deg  = r_deg;
	if (q_deg > 0) Quot = new Field[q_deg+1];
	else Quot = new Field;
	if (r_deg > 0) Rem =  new Field[r_deg+1];
	else Rem  = new Field;
	Mod = mod;
	int i;
	for(i=0; i<=q_deg; i++)
		Quot[i].setModule(mod);
	for(i=0; i<=r_deg; i++)
		Rem[i].setModule(mod);
}
////////////////////////////////////////////////////////
CString Div_poly::remToString(BOOL endian){
	CString ret("");
	if(endian){
		for(int i=Rem_deg; i>=0; i--){
			ret += Rem[i].toString();
			ret += " ";
		}
	}else{
		for(int i=0; i<=Rem_deg; i++){
			ret += Rem[i].toString();
			ret += " ";
		}
	}
	return ret;
}
////////////////////////////////////////////////////////
CString Div_poly::quotToString(BOOL endian){
	CString ret("");
	if(endian){
		for(int i=Quot_deg; i>=0; i--){
			ret += Quot[i].toString();
			ret += " ";
		}
	}else{
		for(int i=0; i<=Quot_deg; i++){
			ret += Quot[i].toString();
			ret += " ";
		}
	}
	return ret;
}
////////////////////////////////////////////////////////
Div_poly::~Div_poly(){
	if (Quot_deg > 0) delete [] Quot;
	else delete Quot;
	if (Rem_deg > 0) delete [] Rem;
	else delete Rem;
}

