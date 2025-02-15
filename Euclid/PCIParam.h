// PCIParam.h: interface for the PCIParam class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PCIPARAM_H__41884921_D6AB_11D5_A253_CC9945B181A3__INCLUDED_)
#define AFX_PCIPARAM_H__41884921_D6AB_11D5_A253_CC9945B181A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class PCIParam 
//параметры потока process_check_irred() 
{
public:
	int el;
	long mod;
	CProgressCtrl *progress;
	CEdit *m_EditPolyMod;
	BOOL m_Endian;
	PCIParam();
	set(int el, long mod, CEdit *e, BOOL endian,CProgressCtrl *pr);
	virtual ~PCIParam();

};

#endif // !defined(AFX_PCIPARAM_H__41884921_D6AB_11D5_A253_CC9945B181A3__INCLUDED_)
