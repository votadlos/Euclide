// PFIParam.h: interface for the PFIParam class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PFIPARAM_H__41884922_D6AB_11D5_A253_CC9945B181A3__INCLUDED_)
#define AFX_PFIPARAM_H__41884922_D6AB_11D5_A253_CC9945B181A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class PFIParam  
{
public:
	long mod;
	CEdit *m_EditPolyMod;
	CProgressCtrl *progress;
	BOOL m_Endian;
	PFIParam();
	set(long mod, CEdit *e, BOOL endian,CProgressCtrl *pr);
	virtual ~PFIParam();

};

#endif // !defined(AFX_PFIPARAM_H__41884922_D6AB_11D5_A253_CC9945B181A3__INCLUDED_)
