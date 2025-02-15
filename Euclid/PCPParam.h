// PCPParam.h: interface for the PCPParam class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PCPPARAM_H__2BA63541_D6E7_11D5_A253_EA9F635781A3__INCLUDED_)
#define AFX_PCPPARAM_H__2BA63541_D6E7_11D5_A253_EA9F635781A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class PCPParam  
{
public:
	long mod;
	int des_deg;
	BOOL endian, irred;
	CProgressCtrl *progress;
	CEdit *output;
	void set(long m, int d, BOOL e, CEdit *edit, CProgressCtrl *pr, BOOL irr);
	PCPParam();
	virtual ~PCPParam();

};

#endif // !defined(AFX_PCPPARAM_H__2BA63541_D6E7_11D5_A253_EA9F635781A3__INCLUDED_)
