// Euclid.h : main header file for the EUCLID application
//

#if !defined(AFX_EUCLID_H__9B9A4205_8530_11D5_A253_80542EFCACA3__INCLUDED_)
#define AFX_EUCLID_H__9B9A4205_8530_11D5_A253_80542EFCACA3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "Polynomial.h"     //polynomials

/////////////////////////////////////////////////////////////////////////////
// CEuclidApp:
// See Euclid.cpp for the implementation of this class
//

#define MIN(a,b) ((a)<=(b) ? (a) : (b))
#define MAX(a,b) ((a)>=(b) ? (a) : (b))
#define ABS(a)   ((a)<0   ? -(a) : (a))
#define SIGSTOP 25


//////////////////////////////////////////////////////////////
class CEuclidApp : public CWinApp
{
public:
	CEuclidApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEuclidApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEuclidApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EUCLID_H__9B9A4205_8530_11D5_A253_80542EFCACA3__INCLUDED_)
